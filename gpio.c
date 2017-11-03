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

// gpio register handling
// still had an issue with pin numbering, if I only testing PIN1 it did not work!
#define GPIO_SET_FUNC(pin, func)		*(gpio + (pin/10)) = ( *(gpio + (pin/10)) & ~(7 << ((pin%10)*3)) )  | (func << ((pin%10)*3))
#define GPIO_SET(pin)					*(gpio + REG_OFFSET_GPIO_SET + (pin/32)) |= (1 << (pin%31))
#define GPIO_CLEAR(pin)					*(gpio + REG_OFFSET_GPIO_CLEAR + (pin/32)) |= (1 << (pin%31))
#define GPIO_READ(pin)					(*(gpio + REG_OFFSET_GPIO_READ + (pin/32)) &= (1 << (pin%31))) >> (pin%31)
#define GPIO_EVENT(pin)					*(gpio + REG_OFFSET_GPIO_EVENT + (pin/32)) &= (1 << (pin%31))
#define GPIO_REDGE_EN(pin, enable)		*(gpio + REG_OFFSET_GPIO_REDGE_EN + (pin/32)) &= ( ~(1 << (pin%31)) | (enable << ((pin%31))) )
#define GPIO_FEDGE_EN(pin, enable)		*(gpio + REG_OFFSET_GPIO_FEDGE_EN + (pin/32)) &= ( ~(1 << (pin%31)) | (enable << ((pin%31))) )
#define GPIO_HLEV_EN(pin, enable)		*(gpio + REG_OFFSET_GPIO_HLEV_EN + (pin/32)) &= ( ~(1 << (pin%31)) | (enable << ((pin%31))) )
#define GPIO_LLEV_EN(pin, enable)		*(gpio + REG_OFFSET_GPIO_LLEV_EN + (pin/32)) &= ( ~(1 << (pin%31)) | (enable << ((pin%31))) )
#define GPIO_AREDGE_EN(pin, enable)		*(gpio + REG_OFFSET_GPIO_AREDGE_EN + (pin/32)) &= ( ~(1 << (pin%31)) | (enable << ((pin%31))) )
#define GPIO_AFEDGE_EN(pin, enable)		*(gpio + REG_OFFSET_GPIO_AFEDGE_EN + (pin/32)) &= ( ~(1 << (pin%31)) | (enable << ((pin%31))) )
// see BCM2835 spec to see how to use this, it's probably better to set multiple pins in one command --> TODO
#define GPIO_PULL_CNTRL(pin, up)		*(gpio + REG_OFFSET_GPIO_PULL_CNTRL) = up
#define GPIO_PULL_CLK(pin)				*(gpio + REG_OFFSET_GPIO_EN_CLK + (pin/32)) |= (1 << pin%31)

int main(int argc, char **argv)
{
	int fd, i;
	static unsigned char k = 0;

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

	// Initialize io registers to outputs
	for (i = 0; i < 30; i++)
	{
		GPIO_SET_FUNC(i, FSEL_OUTPUT);
	}


	// print function register
	printf("Function select address: %d\n", gpio);	// was 0x76F8A000, other time: 76F96000
	printf("Function select reg: %d\n", (uint32_t)*gpio);
	fflush(stdout);

	// do something forever
	while(1)
	{
		printf("k is: %d\n", k);
		for (i = 0; i < 30; i++)
		{
			if ((i+k)%2)
			{
				GPIO_SET(i);
				printf("SET i = %d\n", i);
			}
			else
			{
				GPIO_CLEAR(i);
				printf("CLEAR i = %d\n", i);
			}
			k = !k;
			printf("GPIO pin %d: %s\n", i, (GPIO_READ(i))?"ON":"OFF");
		}
		fflush(stdout);
		sleep(5);
	}
}

