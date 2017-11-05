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
	gpio_set_function(2, FSEL_OUTPUT);
	gpio_set_function(3, FSEL_INPUT);

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

		// this reads the output gpio2 and input gpio3
		printf("gpio 2: %d", gpio_read(2));
		printf("gpio 3: %d", gpio_read(3));

		i = !i;
		sleep(2);
	}
}
