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
#include "network.h"

char setup_client(char * ip_address, uint32_t port )
{
	int32_t client_socket;
	struct sockaddr_in remote_address;
	char request[] = "GET / HTTP/1.1\r\n\n";
	char response[4096] = {0};

	client_socket = socket(AF_INET, SOCK_STREAM, 0);

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
	recv(client_socket, response, sizeof(response), 0);

	printf("Response: %s", response);
	close(client_socket);

	return NETWORK_SUCCESS;
}
