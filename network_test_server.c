/*
 * network_test_server.c
 *
 *  Created on: 10 nov. 2017
 *      Author: Kenneth
 */

#include <unistd.h>
#include <stdio.h>
#include "network.h"

#define CLIENT_TIMEOUT	5000

int main(int argc, char *argv[] )
{
	struct pollfd server_socket_poll;
	int32_t client_socket = 0;
	uint16_t client_send_timeout = CLIENT_TIMEOUT;
	char receive_data[128];
	char send_data[128] = "HERE'S WHAT YOU WANT!\n";

	set_server_socket_poll(argv[1], 80, &server_socket_poll);

	while( !client_socket )
	{
		get_server_client(&server_socket_poll, &client_socket);
		memset(&receive_data, sizeof(receive_data));
	}

	while(client_socket)
	{
		if ( !alarm(client_send_timeout) )
		{
			printf("Trying to get client data\n");
			if(get_client_data(client_socket, receive_data, sizeof(receive_data)))
			{
				printf("Client data: %s\n", receive_data);
				client_send_timeout = CLIENT_TIMEOUT;
			}
		}
		else
		{
			close(client_socket);
			client_send_timeout = CLIENT_TIMEOUT;
		}
	}

	if ( strcmp(buffer, "GIVE") )
	{
		printf("Client data command detected", receive_data);
		send(client_socket, send_data, sizeof(send_data), 0);
	}

	return 0;
}
