#include "main.h"
#include "./handler/handler.h"
#define PORT 3000
#define BUFFER_SIZE 1024
#define BUILD_FILE "build/main"

struct sockaddr_in host_addr;
int server_fd;
char *build_files[3] = {"build/main", "build/handler.out", "build/main.out"};

void sigint_handler(int sig)
{
    printf("Shutting down the server... \n");

    shutdown(server_fd, SHUT_RDWR);
    close(server_fd);

    for (int a = 0; a <= sizeof(build_files) / sizeof(build_files[0]); a++)
    {
        if (remove(build_files[a]) != 0)
        {
            printf("File %s gagal dihapus \n", BUILD_FILE);
        }
    }

    exit(0);
}

int main()
{
    // create new socket Ipv4, byte stream communication based
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("file descriptor %d\n", server_fd);

    // if create socket failed, print an error
    if (server_fd == -1)
    {
        perror("socket failed");
        return 1;
    }
    printf("socket created successfully\n");

    // Create the address to bind the socket to

    int host_addrlen = sizeof(host_addr);

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to address
    if (bind(server_fd, (struct sockaddr *)&host_addr, host_addrlen) != 0)
    {
        perror("Web server bind");
        return 10;
    }
    printf("socket successfully bound to address\n");

    // Listen for incoming connections
    if (listen(server_fd, SOMAXCONN) != 0)
    {
        perror("Web server listen");
        return 1;
    }
    printf("Listening incoming request on port %d\n", PORT);

    signal(SIGINT, sigint_handler);
    accept_connection(server_fd, host_addr, host_addrlen);

    return 0;
};
