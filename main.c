/*
 * main.c
 *
 *  Created on: 5 nov. 2017
 *      Author: Kenneth
 */

#include "gpio.h"

int main(int argc, char **argv)
{
	int i = 0;

	gpio_initialize();

	while(1)
	{
		if(i == 0)
		{
			gpio_set(2);
		}
		else
		{
			gpio_clear(2);
		}
		i = !i;
	}
}
