/*
 * gpio_defines.h
 *
 *  Created on: 1 nov. 2017
 *      Author: Kenneth
 */

#ifndef GPIO_DEFINES_H_
#define GPIO_DEFINES_H_

#define GPIO_BASE_ADDRESS (0x3F200000)

// function select registers
#define ALT_FUNC_REG_OFFSET				0		// 0x3F200000

// output state registers
#define OUTPUT_SET_STATE_REG_OFFSET	 	7		// 0x3F20001C
#define OUTPUT_CLEAR_STATE_REG_OFFSET	10		// 0x3F200028

// function select functions (can have different meanings depending on which register/io is used)
#define FSEL_INPUT		0
#define FSEL_OUTPUT		1
#define FSEL_ALT_0		4
#define FSEL_ALT_1		5
#define FSEL_ALT_2		6
#define FSEL_ALT_3		7
#define FSEL_ALT_4		3
#define FSEL_ALT_5		2

#endif /* GPIO_DEFINES_H_ */
