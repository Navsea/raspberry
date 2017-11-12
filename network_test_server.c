/*
 * network_test_server.c
 *
 *  Created on: 10 nov. 2017
 *      Author: Kenneth
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "network.h"

#define CLIENT_TIMEOUT	5000

static int32_t client_socket = 0;

int main(int argc, char *argv[] )
{
	struct pollfd server_socket_poll;
	char receive_data[128];
	char send_data[256][128] = {0};
	FILE * web_page_fd = 0;

	web_page_fd = fopen("index.html", "r");

	while( fgets(send_data, sizeof(send_data), web_page_fd) );
	printf("html file:\n%s", send_data);

	set_server_socket_poll(argv[1], 80, &server_socket_poll);

	while( !client_socket )
	{
		get_server_client(&server_socket_poll, &client_socket);
		memset(&receive_data, 0, sizeof(receive_data));
	}

	while(client_socket)
	{

		printf("Trying to get client data\n");
		if(get_client_data(client_socket, receive_data, sizeof(receive_data)))
		{
			printf("Client data: %s\n", receive_data);
			// check for equal command
			if ( !strcmp(receive_data, "GIVE") )
			{
				send(client_socket, send_data, sizeof(send_data), 0);
			}
		}
	}

	return 0;
}

