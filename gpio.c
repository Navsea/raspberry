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

static volatile unsigned int *gpio;

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
#define GPIO_PULL_CNTRL(pull)			*(gpio + REG_OFFSET_GPIO_PULL_CNTRL) = pull
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
	printf("The pagesize is: %x\n", getpagesize());
	gpio = (uint32_t*)mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE_ADDRESS);

	if ( ((int32_t)gpio) <  0)
	{
		printf("mmap failed: %s\n", strerror(errno));
		return -1;
	}

	// Initialize io registers to outputs
	for (i = 0; i < 30; i++)
	{
		GPIO_SET_FUNC(i, FSEL_INPUT);
	}

	// Set pull downs
	GPIO_PULL_CNTRL(PULL_DOWN);
	printf("Set pull cntrl reg, have to wait 150 cycles\n");
	sleep(1);
	*(gpio + REG_OFFSET_GPIO_EN_CLK + (pin/32)) = (0xFFFFFFFF);
	printf("Set pull clock reg, have to wait 150 cycles\n");
	sleep(1);
	GPIO_PULL_CNTRL(PULL_NONE);
	*(gpio + REG_OFFSET_GPIO_EN_CLK + (pin/32)) = (0);

	// print function register
	printf("gpio function select 0 address: %x\n", gpio);	// 76FF3000
	printf("gpio function select 0 reg: %x\n", *gpio);

	printf("gpio function select 1 address: %x\n", gpio+1);	// 76FF3000
	printf("gpio function select 1 reg: %x\n", *(gpio+1));

	printf("gpio function select 2 address: %x\n", gpio+2);	// 76FF3000
	printf("gpio function select 2 reg: %x\n", *(gpio+2));

	printf("gpio function select 3 address: %x\n", gpio+3);	// 76FF3000
	printf("gpio function select 3 reg: %x\n", *(gpio+3));

	printf("gpio function select 4 address: %x\n", gpio+4);	// 76FF3000
	printf("gpio function select 4 reg: %x\n", *(gpio+4));

	printf("gpio function select 5 address: %x\n", gpio+5);	// 76FF3000
	printf("gpio function select 5 reg: %x\n", *(gpio+5));

	// print set register
	printf("gpio set address: %x\n", (gpio+REG_OFFSET_GPIO_SET));	// 76FF301C
	printf("gpio set reg: %x\n", *(gpio+REG_OFFSET_GPIO_SET));

	// print clear register
	printf("gpio clear address: %x\n", (gpio+REG_OFFSET_GPIO_CLEAR));	// 76FF3028
	printf("gpio clear reg: %x\n", *(gpio+REG_OFFSET_GPIO_CLEAR));

	// print read register
	printf("gpio read address: %x\n", (gpio+REG_OFFSET_GPIO_READ));		// 76FF3034
	printf("gpio read reg: %x\n", *(gpio+REG_OFFSET_GPIO_READ));

	// print event register
	printf("gpio event address: %x\n", (gpio+REG_OFFSET_GPIO_EVENT));	// 76FF3040
	printf("pgio event reg: %x\n", *(gpio+REG_OFFSET_GPIO_EVENT));

	fflush(stdout);

	// do something forever
	while(1)
	{
		static int k = 1;

		printf("GPIO pin %d: %s\n", 2, (GPIO_READ(2))?"ON":"OFF");


		// Check the entire IO reg
		printf("The whole read reg: %x\n", ((uint32_t)*(gpio + REG_OFFSET_GPIO_READ)));		//2ffaebef 10051410

		sleep(1);
	}
}

