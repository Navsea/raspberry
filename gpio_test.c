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

	//gpio_rising_edge_en(4, 1);			// enabling rising edge detection on pin 4

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

		printf("gpio 2: %d\n", gpio_read(2));
		printf("gpio 3: %d\n", gpio_read(3));
		printf("gpio 4: %d\n", gpio_read(4));
		//printf("gpio 4 rising edge: %d\n", gpio_event(4));

		i = !i;
		sleep(2);
	}
}
