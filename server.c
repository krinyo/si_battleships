/*tcp-server*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*user given data*/
#define SERVER_PORT 14999
//#define SERVER_IP 0.0.0.0

/*static data*/
#define BUFF_SIZE 256
#define MAX_CONNECTIONS 1

int main(){
/*creating socket*/
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

/*bind server socket with using struct*/
	struct sockaddr_in server_sock_addr;
	server_sock_addr.sin_family		= AF_INET;
	server_sock_addr.sin_port		= htons(SERVER_PORT);		
	server_sock_addr.sin_addr.s_addr	= htonl(INADDR_ANY);

	//int bind_status = bind(client__socket, (struct sockaddr*)&client_sock_addr, sizeof(client_sock_addr));

	while(-1 == bind(server_socket, (struct sockaddr*)&server_sock_addr,
				sizeof(server_sock_addr))){
		printf("Trying to bind socket\n");
		sleep(2);
	}
/*listen*/
	//struct sockaddr_in client_sock_addr;
	//client_sock_addr.sin_family           = AF_INET;
	//client_sock_addr.sin_port             = htons(CLIENT_PORT);
	//client_sock_addr.sin_addr.s_addr      = htonl(INADDR_ANY);
	listen(server_socket, MAX_CONNECTIONS);
	int conn_counter = 0;
	int client_socket_desc;
	while(conn_counter < MAX_CONNECTIONS){
		if((client_socket_desc = accept(server_socket, NULL, NULL)) != -1){
			printf("ACCEPTED!\n");
			conn_counter ++;
		}
	}
	//client_socket_desc = accept(server_socket, NULL, NULL);


/*read and write data*/
	char buff[BUFF_SIZE];
	while(1){
		//printf("zebis\n");
		read(client_socket_desc, buff, sizeof(buff)-1);
		printf("%s\n", buff);
		memset(buff, '0', sizeof(buff));
	}
/*close*/
	close(client_socket_desc);
}
