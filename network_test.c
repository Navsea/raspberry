/*
 * network_test.c
 *
 *  Created on: 10 nov. 2017
 *      Author: Kenneth
 */

#include "network.h"

void main(int argc, char *argv[] )
{
	setup_server(argv[1], 80);
	setup_client(argv[1], 80);
}
