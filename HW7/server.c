/*
	C socket server example
*/

#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#include<stdlib.h>

int main(int argc , char *argv[])
{
	int socket_desc , client_sock , c , read_size;
	struct sockaddr_in server , client;
	float client_num, total = 0;
	
	if(argc != 2){
		printf("Usage: ./server <port #>\n");
		return EXIT_FAILURE;
	}

	int port = atoi(argv[1]);
	if(port <= 1023){
		printf("Error: Port must be greater than 1023\n");
		return EXIT_FAILURE;
	}


	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( port );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print error message
		perror("bind failed. Error");
		return 1;
	}
	
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept an incoming connection
	c = sizeof(struct sockaddr_in);
	
	//accept connection from a client
	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}
	
	
	//Receive a message from client
	while( (read_size = recv(client_sock , &client_num , sizeof(client_num) , 0)) > 0 )
	{
		total += client_num;
		//Send the message back to client
		write(client_sock , &total , sizeof(float));
	}
	
	if(read_size == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}
	
	return 0;
}
