/*
 * gpio.c
 *
 *  Created on: 31 okt. 2017
 *      Author: Kenneth De Leener
 */
#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <sys/mman.h>
#include <stdlib.h>
#include "gpio_clean.h"

// The physical address of the first gpio register
#define GPIO_BASE_ADDRESS (0x3F200000)

// function select register
#define REG_OFFSET_ALT_FUNC				0		// 0x3F200000
	// function select functions (can have different meanings depending on which register/io is used)
	#define FSEL_INPUT		0
	#define FSEL_OUTPUT		1
	#define FSEL_ALT_0		4
	#define FSEL_ALT_1		5
	#define FSEL_ALT_2		6
	#define FSEL_ALT_3		7
	#define FSEL_ALT_4		3
	#define FSEL_ALT_5		2

// output state registers
#define REG_OFFSET_GPIO_SET	 			7		// 0x3F20001C
#define REG_OFFSET_GPIO_CLEAR			10		// 0x3F200028

// input state registers
#define REG_OFFSET_GPIO_READ			13		// 0x3F200034

// event state registers
#define REG_OFFSET_GPIO_EVENT			16		// 0x3F200040

// edge detection enable register offsets (event reg will be set when detected)
#define REG_OFFSET_GPIO_REDGE_EN		19		// 0x3F20004C
#define REG_OFFSET_GPIO_FEDGE_EN		22		// 0x3F200058

// level detection enable register offsets (event reg will be set when detected)
#define REG_OFFSET_GPIO_HLEV_EN			25		// 0x3F200064
#define REG_OFFSET_GPIO_LLEV_EN			28		// 0x3F200070

// asynchronous edge detection register offsets (event reg will be set when detected)
#define REG_OFFSET_GPIO_AREDGE_EN		31		// 0x3F20007C
#define REG_OFFSET_GPIO_AFEDGE_EN		34		// 0x3F200088

// pull up/down enable register offsets
#define REG_OFFSET_GPIO_PULL_CNTRL		37		// 0x3F200094
	#define PULL_NONE					0
	#define PULL_DOWN					1
	#define PULL_UP						2
#define REG_OFFSET_GPIO_EN_CLK			38		// 0x3F20009C

// global reference to the first of the gpio registers
static volatile uint32_t *s_gpio_pu32;

// indicating whether or not initialization is done
static unsigned char s_initialized_u8;

signed char gpio_initialize(void )
{
	FILE * ls_device_mem_pfile;

	// obtain handle to physical memory
	if ( (ls_device_mem_pfile = fopen("/dev/mem", "r+")) == NULL )
	{
		printf("Unable to open /dev/mem: %s\n", strerror(errno));
		return GPIO_FAILURE;
	}

	s_gpio_pu32 = (uint32_t*)mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, ls_device_mem_pfile, GPIO_BASE_ADDRESS);

	if ( s_gpio_pu32 == MAP_FAILED )
	{
		printf("mmap failed: %s\n", strerror(errno));
		return GPIO_FAILURE;
	}
	else
	{
		printf("mmap success");
		s_initialized_u8 = 1;
		return GPIO_SUCCESS;
	}
}

signed char gpio_set_function(unsigned char pin, fsel function)
{
	if ( s_initialized_u8 )
	{
		*(s_gpio_pu32 + (pin/10)) = ( *(s_gpio_pu32 + (pin/10)) & ~(7 << ((pin%10)*3)) )  | (function << ((pin%10)*3));
		return GPIO_SUCCESS;
	}
	else
	{
		return GPIO_FAILURE;
	}
}

signed char gpio_set(unsigned char pin)
{
	if ( s_initialized_u8 )
	{
		*(s_gpio_pu32 + REG_OFFSET_GPIO_SET + (pin/32)) |= (1 << (pin%31));
		return GPIO_SUCCESS;
	}
	else
	{
		return GPIO_FAILURE;
	}
}

signed char gpio_clear(unsigned char pin)
{
	if ( s_initialized_u8 )
	{
		*(s_gpio_pu32 + REG_OFFSET_GPIO_CLEAR + (pin/32)) |= (1 << (pin%31))
		return GPIO_SUCCESS;
	}
	else
	{
		return GPIO_FAILURE;
	}
}

signed char gpio_read(unsigned char pin)
{
	if ( s_initialized_u8 )
	{
		return ((*(s_gpio_pu32 + REG_OFFSET_GPIO_READ + (pin/32)) &= (1 << (pin%31))) >> (pin%31));
	}
	else
	{
		return GPIO_FAILURE;
	}
}

signed char gpio_event(unsigned char pin)
{
	if ( s_initialized_u8 )
	{
		return ((*(s_gpio_pu32 + REG_OFFSET_GPIO_EVENT + (pin/32)) &= (1 << (pin%31))) >> (pin%31));
	}
	else
	{
		return GPIO_FAILURE;
	}
}

signed char gpio_rising_edge_en(unsigned char pin, unsigned char enable)
{
	if ( s_initialized_u8 )
	{
		*(s_gpio_pu32 + REG_OFFSET_GPIO_REDGE_EN + (pin/32)) &= ( ~(1 << (pin%31)) | (enable << ((pin%31))) );
		return GPIO_SUCCESS;
	}
	else
	{
		return GPIO_FAILURE;
	}
}

signed char gpio_falling_edge_en(unsigned char pin, unsigned char enable)
{
	if ( s_initialized_u8 )
	{
		*(s_gpio_pu32 + REG_OFFSET_GPIO_FEDGE_EN + (pin/32)) &= ( ~(1 << (pin%31)) | (enable << ((pin%31))) );
		return GPIO_SUCCESS;
	}
	else
	{
		return GPIO_FAILURE;
	}
}

signed char gpio_high_level_en(unsigned char pin, unsigned char enable)
{
	if ( s_initialized_u8 )
	{
		*(s_gpio_pu32 + REG_OFFSET_GPIO_HLEV_EN + (pin/32)) &= ( ~(1 << (pin%31)) | (enable << ((pin%31))) );
		return GPIO_SUCCESS;
	}
	else
	{
		return GPIO_FAILURE;
	}
}

signed char gpio_low_level_en(unsigned char pin, unsigned char enable)
{
	if ( s_initialized_u8 )
	{
		*(s_gpio_pu32 + REG_OFFSET_GPIO_LLEV_EN + (pin/32)) &= ( ~(1 << (pin%31)) | (enable << ((pin%31))) );
		return GPIO_SUCCESS;
	}
	else
	{
		return GPIO_FAILURE;
	}
}

signed char gpio_async_rising_edge_en(unsigned char pin, unsigned char enable)
{
	if ( s_initialized_u8 )
	{
		*(s_gpio_pu32 + REG_OFFSET_GPIO_AREDGE_EN + (pin/32)) &= ( ~(1 << (pin%31)) | (enable << ((pin%31))) );
		return GPIO_SUCCESS;
	}
	else
	{
		return GPIO_FAILURE;
	}
}

signed char gpio_async_falling_edge_en(unsigned char pin, unsigned char enable)
{
	if ( s_initialized_u8 )
	{
		*(s_gpio_pu32 + REG_OFFSET_GPIO_AFEDGE_EN + (pin/32)) &= ( ~(1 << (pin%31)) | (enable << ((pin%31))) );
		return GPIO_SUCCESS;
	}
	else
	{
		return GPIO_FAILURE;
	}
}

signed char gpio_pull_up_down_set(gpio_pull pud)
{
	if ( s_initialized_u8 )
	{
		*(s_gpio_pu32 + REG_OFFSET_GPIO_PULL_CNTRL) = pud;
		return GPIO_SUCCESS;
	}
	else
	{
		return GPIO_FAILURE;
	}
}

signed char gpio_pull_up_down_clk(unsigned char pin)
{
	if ( s_initialized_u8 )
	{
		*(s_gpio_pu32 + REG_OFFSET_GPIO_EN_CLK + (pin/32)) |= (1 << pin%31)
		return GPIO_SUCCESS;
	}
	else
	{
		return GPIO_FAILURE;
	}
}
