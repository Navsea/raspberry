/*
 * gpio_defines.h
 *
 *  Created on: 1 nov. 2017
 *      Author: Kenneth
 */

#ifndef GPIO_DEFINES_H_
#define GPIO_DEFINES_H_

#define GPIO_BASE_ADDRESS (0x3F200000)


/* This section states the offset for the corresponding register when using 32 bit pointers (offset 1 is 4 bytes further than base) */
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
#define REG_OFFSET_GPIO_EN_CLK			38		// 0x3F20009C

#endif /* GPIO_DEFINES_H_ */
