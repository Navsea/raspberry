/*
 * gpio_clean.h
 *
 *  Created on: 5 nov. 2017
 *      Author: Kenneth
 */

#ifndef GPIO_CLEAN_H_
#define GPIO_CLEAN_H_

typedef enum fsel
{
	FSEL_INPUT 	= 0,
	FSEL_OUTPUT = 1,
	FSEL_ALT_0	= 4,
	FSEL_ALT_1	= 5,
	FSEL_ALT_2	= 6,
	FSEL_ALT_3	= 7,
	FSEL_ALT_4	= 3,
	FSEL_ALT_5	= 2
} fsel;

typedef enum gpio_pull
{
	PULL_NONE	= 0,
	PULL_DOWN	= 1,
	PULL_UP		= 2
} gpio_pull;

#define GPIO_SUCCESS	1
#define GPIO_FAILURE	-1

// map the phsyical memory into the virtual memory for us to use
signed char gpio_initialize(void );
signed char gpio_set_function(unsigned char pin, fsel function);
signed char gpio_set(unsigned char pin);
signed char gpio_clear(unsigned char pin);
signed char gpio_read(unsigned char pin);
signed char gpio_event(unsigned char pin);
signed char gpio_rising_edge_en(unsigned char pin, unsigned char enable);
signed char gpio_falling_edge_en(unsigned char pin, unsigned char enable);
signed char gpio_high_level_en(unsigned char pin, unsigned char enable);
signed char gpio_low_level_en(unsigned char pin, unsigned char enable);
signed char gpio_async_rising_edge_en(unsigned char pin, unsigned char enable);
signed char gpio_async_falling_edge_en(unsigned char pin, unsigned char enable);
signed char gpio_pull_up_down_set(gpio_pull pud);
signed char gpio_pull_up_down_clk(unsigned char pin);

#endif /* GPIO_CLEAN_H_ */
