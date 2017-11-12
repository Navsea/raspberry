/*
 * network_server.h
 *
 *  Created on: 10 nov. 2017
 *      Author: Kenneth
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <stdint.h>
#include <sys/poll.h>

#define NETWORK_SUCCESS		1
#define NETWORK_FAIL		0

// returns server socket poll and sets it to listen
uint8_t set_server_socket_poll(char * ip_address, uint16_t port, struct pollfd *server_socket_poll );
// checks for client connections
int32_t  get_server_client(struct pollfd *server_socket_poll);
// get the data from the client socket and store it in buffer
int8_t get_client_data(int32_t client_socket, char *buffer, uint8_t size);

#endif /* NETWORK_H_ */
