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
	while ( waitpid(-1, NULL, WNOHANG) > 0 );
}

int main(int argc, char *argv[])
{
	//set the signal
	struct sigaction sa_child;
	sigemptyset(&sa_child.sa_mask);
	sa_child.sa_flags = SA_RESTART;
	sa_child.sa_handler = child_handler;

	//fork stuff
	int fid;

	//socket stuff
	int sockfd;
	int clientfd;
	struct addrinfo addr_hint;
	struct addrinfo *addr_result; // we need to free this later!
	struct sockaddr_storage addr_client; // addrinfo client_addr; pakai storage krn bisa ipv4/6
    socklen_t sin_size;
    int reuse_true = 1;

    memset(&addr_hint, 0, sizeof(addr_hint));
	addr_hint.ai_family = AF_UNSPEC;
	addr_hint.ai_socktype = SOCK_STREAM;
	addr_hint.ai_flags = AI_PASSIVE;



	getaddrinfo(NULL, "20000", &addr_hint, &addr_result);


	sockfd = socket(addr_result->ai_family, addr_result->ai_socktype, addr_result->ai_protocol);

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse_true, sizeof(int));


	//int bind(int s, struct sockaddr *addr, int addrlen);

	bind(sockfd, addr_result->ai_addr, addr_result->ai_addrlen);

	listen(sockfd, 10);



	while(1)
	{
			clientfd = accept(sockfd, (struct sockaddr *) &addr_client, &sin_size); //blocking sampai ada yg connect dan di accept

			fid=fork();

			if (fid == 0)
			{
				close(sockfd);
				send(clientfd, "asikbos", 8, 0);
				close(clientfd);
			}

			close(clientfd);
	}


	close(sockfd);
	freeaddrinfo(addr_result);

}