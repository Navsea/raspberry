/*
 * network_server.h
 *
 *  Created on: 10 nov. 2017
 *      Author: Kenneth
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <stdint.h>

#define NETWORK_SUCCESS		1
#define NETWORK_FAIL		0

char setup_server(char * ip_address, uint32_t port );

#endif /* NETWORK_H_ */
