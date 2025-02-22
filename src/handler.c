#include "../include/server.h"

void accept_connection(int sockfd, struct sockaddr_in *host_addr, int host_addrlen)
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
