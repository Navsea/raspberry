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

// returns server socket poll and sets it to listen
struct pollfd* get_server_socket_poll(char * ip_address, uint16_t port );
// checks for client connections
int32_t  get_server_client(int32_t server_socket);
// get the data from the client socket and store it in buffer
void get_client_data(int32_t client_socket, char *buffer);

#endif /* NETWORK_H_ */
