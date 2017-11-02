/*
 * time.c
 *
 *  Created on: 2 nov. 2017
 *      Author: Kenneth
 */
#include <sys/time.h>

void main(int argc, char **argv)
{
	time_t the_time;
	printf("The time is: %s", ctime(time(0)));
}
