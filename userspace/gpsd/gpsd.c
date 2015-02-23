#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "gpsd.h"
#define GPSD_DAEMON_LOG "/data/misc/gpsd.log"

void daemon_mode(void)
{
	pid_t pid = fork();
	pid_t sid;

	if (pid > 0)
		exit(EXIT_SUCCESS);

	else if (pid < 0) {
		perror("Fail fork");
		exit(EXIT_FAILURE);
	}
	sid = setsid();
	if (sid < 0) {
		perror("Fail to setsid");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid > 0)
		exit(EXIT_SUCCESS);

	else if (pid < 0) {
		perror("Fail fork");
		exit(EXIT_FAILURE);
	}
	chdir("/data/misc/");
	sid = setsid();
	umask(0);

	close(0);
	close(1);
	close(2);
}

void poll_data(void)
{
	struct gps_location this_data;
	time_t curr_time;
	FILE *gpsd_log = fopen(GPSD_DAEMON_LOG, "a+");

	do {
		FILE *gps_data = fopen(GPS_LOCATION_FILE, "r");

		fscanf(gps_data, "%lf %lf %f",
		       &this_data.latitude,
		       &this_data.longitude,
		       &this_data.accuracy);
		curr_time = time(NULL);
		fprintf(gpsd_log, "BEGIN_RECORD[%s]\t", ctime(&curr_time));
		fprintf(gpsd_log, "%f\t", this_data.latitude);
		fprintf(gpsd_log, "%f\t", this_data.longitude);
		fprintf(gpsd_log, "%f\n", this_data.accuracy);
		if (set_gps_location(&this_data))
			fprintf(gpsd_log, "Call to set_gps_location failed\n");
		fflush(gpsd_log);
		usleep(1000000);
		fclose(gps_data);
	} while (1);

	fclose(gpsd_log);
}

int main(int argc, char *argv[])
{
	daemon_mode();
	poll_data();
	return 0;
}

