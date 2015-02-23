#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/namei.h>
#include <linux/jiffies.h>
#include <linux/gps.h>
#include <linux/capability.h>
#include <linux/uaccess.h>

struct ilocation_t ilocation;
s64 daemon_time;
DEFINE_RWLOCK(lock);

SYSCALL_DEFINE1(set_gps_location, struct gps_location __user *, loc)
{
	struct gps_location gps_loc;
	struct timespec ts;

	if (current_uid() != 0)
		return -EACCES;
	if (!loc)
		return -EINVAL;

	if (copy_from_user(&gps_loc, loc, sizeof(struct gps_location)))
		return -EFAULT;
	write_lock(&lock);
	ilocation.i_latitude = *(__le64 *) &gps_loc.latitude;
	ilocation.i_longitude = *(__le64 *) &gps_loc.longitude;
	ilocation.i_accuracy = *(__le32 *) &gps_loc.accuracy;
	ilocation.i_coord_age = 0;
	getnstimeofday(&ts);
	daemon_time = (s64) ts.tv_sec;
	write_unlock(&lock);
	return 0;
}

SYSCALL_DEFINE2(get_gps_location, const char __user *, pathname,
		struct gps_location __user *, loc)
{
	struct path path;
	struct inode *inode;
	int result;
	struct gps_location l;

	result = user_path(pathname, &path);
	if (result < 0)
		return -EINVAL;
	inode = path.dentry->d_inode;
	if (!(S_IRUSR & inode->i_mode)) {
		path_put(&path);
		return -ENODEV;
	}
	if (!inode->i_op->get_gps_location) {
		pr_err("get_gps_location unimplemented for fs!\n");
		path_put(&path);
		return -ENODEV;
	}
	result = inode->i_op->get_gps_location(inode, &l);
	path_put(&path);
	if (copy_to_user(loc, &l, sizeof(struct gps_location)))
		return -EFAULT;

	return result;
}
