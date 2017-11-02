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
	printf("The time is: %s", ctime(&time(0)));
}
