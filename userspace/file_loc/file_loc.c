#include <stdlib.h>
#include <stdio.h>
#include "file_loc.h"



void usage(void)
{
	printf("Must provide a path to the file\n");
	exit(EXIT_FAILURE);
}
int main(int argc, char **argv)
{

	char *path;
	int coor_age;
	struct gps_location *loc;

	if (argc != 2)
		usage();

	path = argv[1];
	loc = malloc(sizeof(struct gps_location));
	coor_age = get_gps_location(path, loc);
	printf("GPS coordinate:\n%lf, %lf\n", loc->latitude, loc->longitude);
	printf("Accuracy:\n%fm\n", loc->accuracy);
	printf("Coordinate age:\n%d\n", coor_age);
	printf("Google map URL:\nhttps://www.google.com/maps/@%lf,%lf\n",
	       loc->latitude, loc->longitude);
	free(loc);
	return 0;
}
