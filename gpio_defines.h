/*
 * gpio_defines.h
 *
 *  Created on: 1 nov. 2017
 *      Author: Kenneth
 */

#ifndef GPIO_DEFINES_H_
#define GPIO_DEFINES_H_

#define GPIO_BASE_ADDRESS 0x20200000

// function select registers
#define ALT_FUNC_SELECT_0 	(GPIO_BASE_ADDRESS + 0)	// 0x20200000
#define ALT_FUNC_SELECT_1 	(GPIO_BASE_ADDRESS + 1)	// 0x20200004
#define ALT_FUNC_SELECT_2	(GPIO_BASE_ADDRESS + 2)	// 0x20200008
#define ALT_FUNC_SELECT_3	(GPIO_BASE_ADDRESS + 3)	// 0x2020000C
#define ALT_FUNC_SELECT_4	(GPIO_BASE_ADDRESS + 4)	// 0x20200010
#define ALT_FUNC_SELECT_5	(GPIO_BASE_ADDRESS + 5)	// 0x20200014

// function select functions (can have different meanings depending on which register/io is used)
#define FSEL_INPUT		0
#define FSEL_OUTPUT		1
#define FSEL_ALT_0		4
#define FSEL_ALT_1		5
#define FSEL_ALT_2		6
#define FSEL_ALT_3		7
#define FSEL_ALT_4		3
#define FSEL_ALT_5		2

// select an gpio
#define GPIO_PIN(x)	ALT_FUNC_SELECT_##(x/10)

#endif /* GPIO_DEFINES_H_ */
