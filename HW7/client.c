/*
	C ECHO client example using sockets
*/
#include <stdio.h>	//printf
#include <string.h>	//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>
#include<stdlib.h>

int main(int argc , char *argv[])
{
	int sock;
	struct sockaddr_in server;
	float usr_input, server_total; 
	
	if(argc != 2){
		printf("Usage: ./client <port #>");
	}

	int port = atoi(argv[1]);
	if(port <= 1023){
		printf("Error: Port must be greater than 1023\n");
		return EXIT_FAILURE;
	}
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( port );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}
	
	
	
	//keep communicating with server
	while(1)
	{
		printf("Enter a number: ");
		scanf("%f", &usr_input);
		
		//Send some data
		if(send(sock , &usr_input, sizeof(usr_input), 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		
		//Receive a reply from the server
		if( recv(sock , &server_total , sizeof(float) , 0) < 0)
		{
			puts("recv failed");
			break;
		}
		
		printf("Total: %f\n", server_total);
	}
	
	close(sock);
	return 0;
}