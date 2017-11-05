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

	while(1)
	{
		if(i == 0)
		{
			printf("Gpio 2 set result: %d", gpio_set(2));

		}
		else
		{
			printf("Gpio 2 clear result: %d", gpio_clear(2));
		}
		i = !i;
		sleep(2);
	}
}
