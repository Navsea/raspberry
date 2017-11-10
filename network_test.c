/*
 * network_test.c
 *
 *  Created on: 10 nov. 2017
 *      Author: Kenneth
 */

#include "network.h"
#include <stdint.h>

void main(int argc, char *argv[] )
{
	setup_client(argv[1], 80);
}
