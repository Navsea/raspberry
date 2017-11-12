/*
 * network_test_server.c
 *
 *  Created on: 10 nov. 2017
 *      Author: Kenneth
 */

#include <unistd.h>
#include "network.h"

#define CLIENT_TIMEOUT	5000

int main(int argc, char *argv[] )
{
	struct pollfd server_socket_poll;
	int32_t client_socket = 0;
	uint16_t client_send_timeout = CLIENT_TIMEOUT;
	char buffer[128];

	set_server_socket_poll(argv[1], 80, &server_socket_poll);

	while( !client_socket )
	{
		get_server_client(&server_socket_poll, &client_socket);
	}

	while(client_socket)
	{
		if ( !alarm(client_send_timeout) )
		{
			if(get_client_data(client_socket, buffer, sizeof(buffer)))
			{
				printf("%s", buffer);
				client_send_timeout = CLIENT_TIMEOUT;
			}
		}
		else
		{
			close(client_socket);
			client_send_timeout = CLIENT_TIMEOUT;
		}
	}

	return 0;
}
