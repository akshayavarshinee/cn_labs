// rarp_client.c
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char buffer[1024];

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(1309);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter MAC Address: ");
    fgets(buffer, sizeof(buffer), stdin);

    buffer[strcspn(buffer, "\n")] = 0;

    // send MAC to server
    sendto(sock, buffer, strlen(buffer), 0,
           (struct sockaddr *)&server, sizeof(server));

    // receive IP
    recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);

    printf("IP Address: %s\n", buffer);

    close(sock);
    return 0;
}