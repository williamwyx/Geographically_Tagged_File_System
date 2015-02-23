#ifndef _GPS_H_
#define _GPS_H_

struct gps_location {
	double latitude;
	double longitude;
	float accuracy;
};

struct ilocation_t {
	__le64 i_latitude;
	__le64 i_longitude;
	__le32 i_accuracy;
	__le32 i_coord_age;
};

extern struct ilocation_t ilocation;
extern s64 daemon_time;
extern rwlock_t lock;

#endif
