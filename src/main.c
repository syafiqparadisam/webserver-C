#include "../include/server.h"

int main()
{
    // create new socket Ipv4, byte stream communication based
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("file descriptor %d\n", sockfd);

    // if create socket failed, print an error
    if (sockfd == -1)
    {
        perror("socket failed");
        return 1;
    }
    printf("socket created successfully\n");

    // Create the address to bind the socket to
    struct sockaddr_in host_addr;
    int host_addrlen = sizeof(host_addr);

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to address
    if (bind(sockfd, (struct sockaddr *)&host_addr, host_addrlen) != 0)
    {
        perror("Web server bind");
        return 10;
    }
    printf("socket successfully bound to address\n");

    // Listen for incoming connections
    if (listen(sockfd, SOMAXCONN) != 0)
    {
        perror("Web server listen");
        return 1;
    }
    printf("Listening incoming request on port %d\n", PORT);

    accept_connection(sockfd, &host_addr, host_addrlen);

    return 0;
};
