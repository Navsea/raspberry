/*
 * network_client.c
 *
 *  Created on: 10 nov. 2017
 *      Author: Kenneth
 */
#include <sys/socket.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "poll.h"
#include "network.h"

char setup_client(char * ip_address, uint32_t port )
{
	int32_t client_socket;
	struct sockaddr_in remote_address;
	char request[] = "GIVE";//"GET / HTTP/1.1\r\n\n";
	char response[255][256] = {0};
	struct pollfd client_socket_poll;

	client_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

	printf("Selected ip address: %s\n", ip_address);
	printf("Selected port: %d\n", port);

	if ( client_socket < 0 )
	{
		printf("Opening socket failed: %s\n", strerror(errno));
		return NETWORK_FAIL;
	}
	else
	{
		printf("Opening socket succeeded\n");
	}

	// Set IPv4 as protocol
	remote_address.sin_family = AF_INET;

	// first argument is ip address in string format
	if (!inet_pton(AF_INET, ip_address, &remote_address.sin_addr))
	{
		printf("Invalid IP address\n");
		return NETWORK_FAIL;
	}
	else
	{
		printf("Successfully registered IP address\n");
	}
	// second argument is port nr, first convert to integer, than to the correct network byte order
	remote_address.sin_port = htons(port);

	connect(client_socket, (struct sockaddr *) &remote_address, sizeof(remote_address));

	send(client_socket, request, sizeof(request), 0);

	client_socket_poll.fd = client_socket;
	client_socket_poll.events = POLLIN;

	while (1)
	{
		switch(poll(&client_socket_poll, 1, 0))
		{
		case 0:
			//printf("poll has timed out\n");
			break;
		case -1:
			printf(" A poll error has occurred: %s\n", strerror(errno));
			break;
		default:
			// POLLIN event will be kept SET if the other has closed connector (EOF), detected by POLLHUP (not sure)&& !(client_socket_poll.revents & POLLHUP)
			if ( client_socket_poll.revents & POLLIN && !(client_socket_poll.revents & POLLHUP) )
			{
				//If no messages are available at the socket, the receive calls wait
			    //  for a message to arrive, unless the socket is nonblocking (see
			    //   fcntl(2)), in which case the value -1 is returned and the external
			    //   variable errno is set to EAGAIN or EWOULDBLOCK.
				while(recv(client_socket, response, sizeof(response), 0)>0);
				printf("client received server response: %s\n", response);
			}
		}
	}
}
