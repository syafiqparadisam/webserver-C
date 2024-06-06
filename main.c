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

    accept_connection(sockfd, host_addr, host_addrlen);

    return 0;
};

void accept_connection(int sockfd, struct sockaddr_in host_addr, int host_addrlen)
{
    struct sockaddr_in client_addr;
    int client_addrlen = sizeof(client_addr);
    // buffer to save the request
    char buffer[BUFFER_SIZE];

    // respons structure
    char resp[] = "HTTP/1.0 200 OK\r\n"
                  "Server: webserver-c\r\n"
                  "Content-type: text/html\r\n\r\n"
                  "<html>hello, world</html>\r\n";
    // Waiting accept connections
    while (1 + 1 == 2)
    {
        int newsockfd = accept(sockfd, (struct sockaddr *)&host_addr, (socklen_t *)&host_addrlen);
        printf("new sockfd %d\n", newsockfd);

        if (newsockfd < 0)
        {
            perror("web server failed to accept");
            continue;
        }
        printf("connection accepted\n");

        // Get client address
        int sockn = getsockname(newsockfd, (struct sockaddr *)&client_addr,
                                (socklen_t *)&client_addrlen);
        if (sockn < 0)
        {
            perror("webserver (getsockname)");
            continue;
        }

        // read from socket request
        int val_read = read(newsockfd, buffer, BUFFER_SIZE);
        if (val_read < 0)
        {
            perror("web server read");
            continue;
        }

        // Read the request and formatted
        char method[BUFFER_SIZE], uri[BUFFER_SIZE], version[BUFFER_SIZE];
        sscanf(buffer, "%s %s %s", method, uri, version);
        printf("[%s:%u] %s %s %s\n", inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port), method, version, uri);

        // write to the socket
        int val_write = write(newsockfd, resp, strlen(resp));
        printf("write to socket\n %s\n", resp);
        if (val_write < 0)
        {
            perror("web server write");
            continue;
        }

        close(newsockfd);
    }
}