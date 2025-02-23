#ifndef ACCEPT_H
#define ACCEPT_H

#include <sys/socket.h>
#include <stdio.h>
#include <error.h>
#include <arpa/inet.h> // Untuk socket
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 1024

void accept_connection(int sockfd, struct sockaddr_in host_addr, int host_addrlen);

#endif