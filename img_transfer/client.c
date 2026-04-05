// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 4000

int main() {
    int sock;
    struct sockaddr_in server;
    FILE *fp;
    char buffer[1024];
    int n;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    printf("Connected to server\n");

    fp = fopen("input.jpg", "rb");
    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    while ((n = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        send(sock, buffer, n, 0);
    }

    printf("Image sent successfully\n");

    fclose(fp);
    close(sock);

    return 0;
}