/*
 * time.c
 *
 *  Created on: 2 nov. 2017
 *      Author: Kenneth
 */
#include <sys/time.h>
#include <stdio.h>

void main(int argc, char **argv)
{
	time_t the_time;
	the_time = time(0);
	printf("The time is: %s", ctime(&the_time));
}
