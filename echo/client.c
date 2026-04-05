// echo_client.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char buffer[1024];

    // 1. Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Setup server address
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 3. Connect
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    while (1) {
        printf("Enter message: ");
        fgets(buffer, sizeof(buffer), stdin);

        // 4. Send message
        send(sock, buffer, strlen(buffer), 0);

        // exit condition
        if (strncmp(buffer, "exit", 4) == 0)
            break;

        // 5. Receive reply
        recv(sock, buffer, sizeof(buffer), 0);

        printf("Server: %s", buffer);
    }

    close(sock);
    return 0;
}