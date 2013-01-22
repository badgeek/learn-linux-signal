#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>


void child_handler(int id)
{

}

int main(int argc, char *argv[])
{
	//set the signal
	struct sigaction sa_child;
	
	sigemptyset(&sa_child.sa_mask);
	sa_child.sa_flags = SA_RESTART;
	sa_child.sa_handler = child_handler;


	//socket stuff

	int sockfd;
	int clientfd;
	struct addrinfo addr_hint;
	struct addrinfo *addr_result;
	struct sockaddr_storage addr_client; // addrinfo client_addr;
    socklen_t sin_size;

    memset(&addr_hint, 0, sizeof(addr_hint));
	addr_hint.ai_family = AF_UNSPEC;
	addr_hint.ai_socktype = SOCK_STREAM;
	addr_hint.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, "20000", &addr_hint, &addr_result);


	sockfd = socket(addr_result->ai_family, addr_result->ai_socktype, addr_result->ai_protocol);

	//int bind(int s, struct sockaddr *addr, int addrlen);

	bind(sockfd, addr_result->ai_addr, addr_result->ai_addrlen);

	listen(sockfd, 10);


	clientfd = accept(sockfd, (struct sockaddr *) &addr_client, &sin_size);
	send(clientfd, "asikbos", 8, 0);

	close(sockfd);
	freeaddrinfo(addr_result);

}