// arp_client.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char buffer[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(1100);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    printf("Enter IP Address: ");
    fgets(buffer, sizeof(buffer), stdin);

    send(sock, buffer, strlen(buffer), 0);

    printf("ARP Response:\n");

    while (recv(sock, buffer, sizeof(buffer), 0) > 0) {
        printf("%s", buffer);
    }

    close(sock);
    return 0;
}