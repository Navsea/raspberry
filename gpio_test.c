/*
 * main.c
 *
 *  Created on: 5 nov. 2017
 *      Author: Kenneth
 */

#include <stdio.h>
#include "gpio.h"

int main(int argc, char **argv)
{
	int i = 0;

	gpio_initialize();
	gpio_set_function(2, FSEL_OUTPUT);	// should toggle
	gpio_set_function(3, FSEL_INPUT);	// should read whatever is connected
	gpio_set_function(4, FSEL_INPUT);	// should detect rising edges
	gpio_set_function(5, FSEL_INPUT);	// should detect falling edges
	gpio_set_function(6, FSEL_INPUT);	// should detect high level
	gpio_set_function(7, FSEL_INPUT);	// should detect low level
	gpio_set_function(8, FSEL_INPUT);	// should detect async rising edges
	gpio_set_function(9, FSEL_INPUT);	// should detect async falling edges
	gpio_set_function(10, FSEL_INPUT);	// should have a pull up
	gpio_set_function(11, FSEL_INPUT);	// should have a pull down

	gpio_rising_edge_en(4, 1);			// enabling rising edge detection on pin 4
	gpio_falling_edge_en(5, 1);			// enabling falling edge detection on pin 5
	gpio_high_level_en(6, 1);			// enabling high level detection on pin 6
	gpio_low_level_en(7,1);				// enabling low level detection on pin 7
	gpio_async_rising_edge_en(8, 1);	// enabling async rising edge detection on pin 8
	gpio_async_falling_edge_en(9, 1);	// enabling async falling edge detection on pin 9

	gpio_pull_up_down_set(PULL_UP);		// preparing to set up a pull up resistor
	usleep(150);
	gpio_pull_up_down_clk(10);			// clocking data into pin 10
	usleep(150);

	// not sure if this is necessary when you will use it again, when they describe how to use it they say to do so
	gpio_pull_up_down_set(PULL_NONE);
	gpio_pull_up_down_clk(0);

	gpio_pull_up_down_set(PULL_DOWN);	// preparing to set up a pull up resistor
	usleep(150);
	gpio_pull_up_down_clk(11);			// clocking data into pin 10
	usleep(150);

	gpio_pull_up_down_set(PULL_NONE);
	gpio_pull_up_down_clk(0);

	while(1)
	{
		// This toggles gpio 2
		if(i == 0)
		{
			gpio_set(2);
		}
		else
		{
			gpio_clear(2);
		}

		for(i = 2; i < 12; i++)
		{
			printf("gpio %d: %d\n", i, gpio_read(2));
		}

		printf("gpio 4 rising edge: %d\n", gpio_event(4));
		printf("gpio 5 falling edge: %d\n", gpio_event(5));
		printf("gpio 6 high level: %d\n", gpio_event(6));
		printf("gpio 7 low level: %d\n", gpio_event(7));
		printf("gpio 8 async rising edge: %d\n", gpio_event(8));
		printf("gpio 9 async falling edge: %d\n", gpio_event(9));
		printf("gpio 10 should be high (pull up)");
		printf("gpio 11 should be high (pull down)");

		i = !i;
		sleep(2);
	}
}
