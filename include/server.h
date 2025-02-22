#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <string.h>
#define PORT 3000
#define BUFFER_SIZE 1024
#include <arpa/inet.h> // Untuk socket
#include <sys/socket.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void accept_connection(int sockfd, struct sockaddr_in *host_addr, socklen_t host_addrlen);

#endif // SERVER_H
