// echo_server.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024];

    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Bind
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // 3. Listen
    listen(server_fd, 3);

    printf("Waiting for connection...\n");

    // 4. Accept
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    while (1) {
        // 5. Receive
        int n = recv(new_socket, buffer, sizeof(buffer), 0);
        buffer[n] = '\0';

        printf("Client: %s", buffer);

        // exit condition
        if (strncmp(buffer, "exit", 4) == 0)
            break;

        // 6. Send back same message
        send(new_socket, buffer, strlen(buffer), 0);
    }

    close(new_socket);
    close(server_fd);
    return 0;
}