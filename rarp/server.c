// rarp_server.c
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    char buffer[1024];

    // mapping table
    char *ip[]  = {"165.165.80.80", "165.165.79.1"};
    char *mac[] = {"6A:08:AA:C2", "8A:BC:E3:FA"};

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(1309);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr *)&server, sizeof(server));

    printf("RARP Server Running...\n");

    while (1) {
        recvfrom(sock, buffer, sizeof(buffer), 0,
                 (struct sockaddr *)&client, &len);

        buffer[strcspn(buffer, "\n")] = 0;

        printf("Received MAC: %s\n", buffer);

        char *response = "Not Found";

        for (int i = 0; i < 2; i++) {
            if (strcmp(buffer, mac[i]) == 0) {
                response = ip[i];
                break;
            }
        }

        sendto(sock, response, strlen(response), 0,
               (struct sockaddr *)&client, len);
    }

    close(sock);
    return 0;
}