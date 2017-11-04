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
#include <string.h>
#include <fcntl.h>

static const char one_wire_path[] = "/sys/bus/w1/devices";

#define MAX_SENSORS	5

int main(int argc, char **argv)
{
	DIR *one_wire_dir;
	struct dirent *dirent;
	char dev_name[MAX_SENSORS][12];
	static uint8_t ls_sensor_index;
	FILE *fd[MAX_SENSORS] = {NULL};
	char dev_path[128];
	uint8_t i = 0;
	char dev_buffer[256];
	char * temp_data;
	ssize_t l_num_bytes;

	if ((one_wire_dir = opendir(one_wire_path)) < 0)
	{
		printf("Unable to open %s: %s\n", one_wire_path, strerror(errno));
		return -1;
	}
	else
	{
		printf("Opened %s\n", one_wire_path);
	}

	// find all the sensors one the one wire bus, max 3 (. and .. will aslo be matches)
	while( ((dirent = readdir(one_wire_dir) ) != NULL) && (ls_sensor_index < 5) )
	{
		printf("found an entry: %s\n", dirent->d_name);
		// found a directory entry for "28-", which are the temp sensors of maxim
		if ( (dirent->d_type == DT_LNK) && strstr(dirent->d_name, "28-") )
		{
			printf("Found a maxim entry: %s\n", dirent->d_name);
			strcpy(dev_name[ls_sensor_index], dirent->d_name);
			ls_sensor_index++;
		}
	}

	// All sensors have been found, close the directory
	closedir(one_wire_dir);

	printf("Closed directory\n");

	for(i = 0; i<ls_sensor_index; i++)
	{
		sprintf(dev_path, "%s/%s/w1_slave", one_wire_path, dev_name[i]);
		printf("full path of device: %s\n", dev_path);

		if ((fd[i] = fopen(dev_path, "r")) < 0)
		{
			printf("Unable to open sensor: %s\n \
					Reason: %s\n", one_wire_path, strerror(errno));
		}
		else
		{
			printf("Successfully opened sensor path\n");
		}
	}
	while(1)
	{
		while( fgets(dev_buffer, 256, fd[0]) != NULL )
		{
			if((temp_data = strstr(dev_buffer, "t=")) != NULL)
			{
				temp_data += 2;
			}
			printf("device 0 temp: %s\n", temp_data);
			rewind(fd[0]);
		}
		printf("Done\n");
		sleep(5);
	}

	/*
	// Open up the files for the sensor
	for(i = 0; i<ls_sensor_index; i++)
	{
		sprintf(dev_path, "%s/%s/w1_slave", one_wire_path, dev_name[i]);
		printf("full path of device: %s\n", dev_path);

		if ((fd[i] = open(dev_path, O_RDONLY)) < 0)
		{
			printf("Unable to open sensor: %s\n \
					Reason: %s\n", one_wire_path, strerror(errno));
		}
		else
		{
			printf("Successfully opened sensor path\n");
		}
	}
	while(1)
	{
		while( (l_num_bytes = read(fd[0], dev_buffer, 256)) > 0 )
		{
			strncpy(temp_data, strstr(dev_buffer, "t=")+2, 5);
			printf("device 0 bytes: %d\n"\
					"device 0 temp: %s\n", l_num_bytes, temp_data);
			lseek(fd, 0, SEEK_SET);
		}
		printf("Done\n");
		sleep(5);
	}
	*/
}

