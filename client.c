/*tcp-client*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*user given data*/
#define CLIENT_PORT 14888
#define SERVER_PORT 14999
//#define CLIENT_IP 0.0.0.0
//#define SERVER_IP 0.0.0.0

/*static data*/
#define BUFF_SIZE 256

int main(){
/*creating socket*/
	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);

/*connecting to server and get the server socket
we need to have responsibility to control the count
of connections(for example just one)*/

	struct sockaddr_in server_sock_addr;
	server_sock_addr.sin_family		= AF_INET;
	server_sock_addr.sin_port		= htons(SERVER_PORT);		
	server_sock_addr.sin_addr.s_addr	= htonl(INADDR_ANY);

//int connection_status;
	while(-1 == connect(client_socket, (struct sockaddr*)&server_sock_addr,
				sizeof(server_sock_addr))){
		printf("Trying to connect to server...\n");
		sleep(2);
	}

/*sending and receiving data(server should take portion of data
with terminator at the end and notify about receiving)*/
	char buff[BUFF_SIZE];
	while(1){
		scanf("%s", buff);
		write(client_socket, (char*)buff, sizeof(buff)-1);
		memset(buff, '0', sizeof(buff));

	}

/*close connection*/
	close(client_socket);
}
