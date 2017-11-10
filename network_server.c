/*
 * network_server.c
 *
 *  Created on: 10 nov. 2017
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

char setup_server(char * ip_address, uint32_t port )
{
	int32_t server_socket, client_socket;
	struct sockaddr_in server_address;
	struct pollfd network_socket_poll;
	char buffer[256];
	char html_header[] = "HTTP/1.1 200 OK\r\n\n";
	FILE * html_data;
	char html_response[4096] = {0};

	// open the html page
	html_data = fopen("index.html", "r");
	while(fgets(html_response, sizeof(html_response), html_data));

	strcat(html_response, html_header);

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

	memset(&network_socket_poll, 0, sizeof(network_socket_poll));
	network_socket_poll.fd = server_socket;
	network_socket_poll.events = POLLIN;	// check for data to read

	while(1)
	{
		switch( poll(&network_socket_poll, 1, 0) )
		{
		case 0:
			//printf("poll has timed out\n");
			break;
		case -1:
			printf(" A poll error has occurred: %s\n", strerror(errno));
			break;
		default:
			if (network_socket_poll.revents & POLLIN)
			{
				client_socket = accept(server_socket, 0, 0);
				recv(client_socket, &buffer, sizeof(buffer), 0);
				printf("received: %s\n", buffer);
				// found command
				if ( !strcmp(buffer, "GIVE")  )
				{
					send(client_socket, html_response, sizeof(html_response), 0);
				}
				else
				{
					printf("Result of strcmp: %d\n", strcmp(buffer, "GIVE"));
				}
			}
			return 0;
		break;
		}
	}
}

