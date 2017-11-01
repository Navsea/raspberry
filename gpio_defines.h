/*
 * gpio_defines.h
 *
 *  Created on: 1 nov. 2017
 *      Author: Kenneth
 */

#ifndef GPIO_DEFINES_H_
#define GPIO_DEFINES_H_

#define GPIO_BASE_ADDRESS 0x3F200000

// function select registers
#define ALT_FUNC_BASE_ADDRESS		(GPIO_BASE_ADDRESS)
	#define ALT_FUNC_SELECT_0 		(ALT_FUNC_BASE_ADDRESS + 0)	// 0x3F200000
	#define ALT_FUNC_SELECT_1 		(ALT_FUNC_BASE_ADDRESS + 1)	// 0x3F200004
	#define ALT_FUNC_SELECT_2		(ALT_FUNC_BASE_ADDRESS + 2)	// 0x3F200008
	#define ALT_FUNC_SELECT_3		(ALT_FUNC_BASE_ADDRESS + 3)	// 0x3F20000C
	#define ALT_FUNC_SELECT_4		(ALT_FUNC_BASE_ADDRESS + 4)	// 0x3F200010
	#define ALT_FUNC_SELECT_5		(ALT_FUNC_BASE_ADDRESS + 5)	// 0x3F200014

// output state registers
#define OUTPUT_STATE_BASE_ADDRESS	(GPIO_BASE_ADDRESS + 7)		// 0x3F20001C

// function select functions (can have different meanings depending on which register/io is used)
#define FSEL_INPUT		0
#define FSEL_OUTPUT		1
#define FSEL_ALT_0		4
#define FSEL_ALT_1		5
#define FSEL_ALT_2		6
#define FSEL_ALT_3		7
#define FSEL_ALT_4		3
#define FSEL_ALT_5		2

// set gpio pin alternate function
#define GPIO_SET_FUNC(pin, func)		*(GPIO_BASE_ADDRESS + (pin/10)) |= (func << (pin%10)*3)
#define GPIO_SET_STATE(pin, state)		*(OUTPUT_STATE_BASE_ADDRESS + (pin/32)) |= (state << pin%31)

#endif /* GPIO_DEFINES_H_ */
