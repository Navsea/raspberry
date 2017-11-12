/*
 * network_server_new.c
 *
 *  Created on: 12 nov. 2017
 *      Author: Kenneth
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/poll.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "network.h"

// returns server socket poll and sets it to listen
uint8_t set_server_socket_poll(char * ip_address, uint16_t port, struct pollfd *server_socket_poll )
{
	int32_t server_socket;
	struct sockaddr_in server_address;

	server_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

	if ( server_socket < 0 )
	{
		printf("Opening socket failed: %s\n", strerror(errno));
		return NETWORK_FAIL;
	}
	else
	{
		printf("Opening socket succeeded\n");
	}

	// Set IPv4 as protocol
	server_address.sin_family = AF_INET;

	// first argument is ip address in string format
	if (!inet_pton(AF_INET, ip_address, &server_address.sin_addr))
	{
		printf("Invalid IP address\n");
		return NETWORK_FAIL;
	}
	else
	{
		printf("Successfully registered IP address\n");
	}
	// second argument is port nr, first convert to integer, than to the correct network byte order
	server_address.sin_port = htons(port);

	if ( (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address))) < 0 )
	{
		printf("Failed to bind server address to socket: %s\n", strerror(errno));
		return NETWORK_FAIL;
	}
	else
	{
		printf("Successfully binded server address to socket\n");
	}

	if (listen(server_socket, 1) < 0)
	{
		printf("Failed to set socket to listen: %s\n", strerror(errno));
		return NETWORK_FAIL;
	}
	else
	{
		printf("succeeded to set socket to listen\n");
	}

	memset(server_socket_poll, 0, sizeof(*server_socket_poll));
	(*server_socket_poll).fd = server_socket;
	(*server_socket_poll).events = POLLIN;	// check for data to read

	return NETWORK_SUCCESS;
}

// checks for client connections and returns file descriptor to client socket
int32_t  get_server_client(struct pollfd * server_socket_poll)
{
	int32_t client_socket = 0;

	switch( poll(server_socket_poll, 1, 0) )
	{
	case 0:
		//printf("poll has timed out\n");
		break;
	case -1:
		printf(" A poll error has occurred: %s\n", strerror(errno));
		break;
	default:
		if ((*server_socket_poll).revents & POLLIN)
		{
			client_socket = accept(server_socket_poll->fd, 0, 0);
			return client_socket;
		}
	break;
	}

	return 0;
}

// get the data from the client socket and store it in buffer
// can only get one line!
int8_t get_client_data(int32_t client_socket, char *buffer, uint16_t size)
{
	int8_t received_bytes;
	switch( received_bytes = (int8_t)recv(client_socket, buffer, size) )
	{
	case -1:	// no data available, errno is set to EAGAIN EWOULDBLOCK
		break;
	case 0:		// EOF reached
		break;
	default:	// store in buffer;
		break;
	}

	return received_bytes;
}
