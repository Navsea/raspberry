/*
 * gpio.c
 *
 *  Created on: 31 okt. 2017
 *      Author: Kenneth
 */
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include "gpio_defines.h"

static volatile uint32_t *gpio;

int main(int argc, char **argv)
{
	int fd;

	GPIO_SET_ALT(0, FSEL_INPUT);
	GPIO_SET_ALT(1, FSEL_OUTPUT);
	GPIO_SET_STATE(1, 1);

	/*
	// Obtain handle to physical memory
	if ( (fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0 )
	{
		printf("Unable to open /dev/mem: %s\n", strerror(errno));
		return -1;
	}

	// map physical memory to virtual memory
	gpio = (uint32_t)mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE_ADDRESS);

	if ( ((int32_t)gpio) <  0)
	{
		printf("mmap failed: %s\n", strerror(errno));
		return -1;
	}

	// do something forever
	while(1)
	{

	}
	*/
}

