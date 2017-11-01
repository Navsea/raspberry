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
#include <sys/mman.h>
#include "gpio_defines.h"

static volatile uint32_t *gpio;

// set gpio pin alternate function
#define GPIO_SET_FUNC(pin, func)		*(gpio + (pin/10)) |= (func << ((pin%10)*3))
#define GPIO_SET_STATE(pin)				*(gpio + OUTPUT_SET_STATE_REG_OFFSET + (pin/32)) |= (1 << (pin%31))
#define GPIO_CLEAR_STATE(pin)			*(gpio + OUTPUT_CLEAR_STATE_REG_OFFSET + (pin/32)) |= (1 << (pin%31))

int main(int argc, char **argv)
{
	int fd;

	// obtain handle to physical memory
	if ( (fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0 )
	{
		printf("Unable to open /dev/mem: %s\n", strerror(errno));
		return -1;
	}

	// map physical memory to virtual memory
	gpio = (uint32_t*)mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE_ADDRESS);

	if ( ((int32_t)gpio) <  0)
	{
		printf("mmap failed: %s\n", strerror(errno));
		return -1;
	}

	// Initialize io registers
	GPIO_SET_FUNC(0, FSEL_INPUT);
	GPIO_SET_FUNC(1, FSEL_OUTPUT);

	// do something forever
	while(1)
	{
		GPIO_SET_STATE(1);
		sleep(1);
		GPIO_CLEAR_STATE(1);
		sleep(1);
		printf("completed cycle");
	}
}

