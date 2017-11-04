/*
 * temp.c
 *
 *  Created on: 4 nov. 2017
 *      Author: Kenneth
 */
#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <dirent.h>

static const char one_wire_path[] = "/sys/bus/w1/devices";

#define MAX_SENSORS	5

int main(int argc, char **argv)
{
	DIR *one_wire_dir;
	struct dirent *dirent;
	char dev_name[MAX_SENSORS][12];
	static uint8_t ls_sensor_index;
	int fd[MAX_SENSORS] = 0;
	char dev_path[128];
	uint8_t i = 0;
	char dev_buffer[256];
	char temp_data[6];

	if ((one_wire_dir = opendir(one_wire_path)) < 0)
	{
		printf("Unable to open %s: %s\n", one_wire_path, strerror(errno));
		return -1;
	}
	// find all the sensors one the one wire bus, max 5
	while( ((dirent = readdir(one_wire_dir) ) != NULL) && (ls_sensor_index < 5) )
	{
		// found a directory entry for "28-", which are the temp sensors of maxim
		if ( (dirent->d_type == DT_LNK) && strstr(dirent->d_name, "28-") )
		{
			strcpy(dev_name[ls_curr_sensor], dirent->d_name);
			ls_sensor_index++;
		}
	}

	// All sensors have been found, close the directory
	closedir(one_wire_dir);

	// Open up the files for the sensor
	for(i = 0; i<(ls_sensor_index+1); i++)
	{
		sprintf(dev_path, "%s/%s/w1_slave", one_wire_path, dev_name[i]);
		printf("full path of device: %s", dev_path);

		if ((fd[i] = open(dev_path, O_RDONLY)) < 0)
		{
			printf("Unable to open sensor: %s\n \
					Reason: %s\n", one_wire_path, strerror(errno));
		}
	}

	while(1)
	{
		while( read(fd[0], dev_buffer, 256) > 0 )
		{
			strncpy(temp_data, strstr(dev_buffer, "t=")+2, 5);
			printf("device 0: %s", temp_data);
		}
		sleep(5);
	}

}
