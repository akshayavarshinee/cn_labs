// udp_server.c
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    char buffer[1024];

    // predefined DNS table
    char *hosts[] = {"yahoo.com", "gmail.com", "cricinfo.com", "facebook.com"};
    char *ips[]   = {"68.180.206.184", "209.85.148.19", "80.168.92.140", "69.63.189.16"};

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(1362);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr *)&server, sizeof(server));

    printf("UDP DNS Server Running...\n");

    while (1) {
        recvfrom(sock, buffer, sizeof(buffer), 0,
                 (struct sockaddr *)&client, &len);

        buffer[strcspn(buffer, "\n")] = 0;

        printf("Request: %s\n", buffer);

        char *response = "Host Not Found";

        for (int i = 0; i < 4; i++) {
            if (strcmp(buffer, hosts[i]) == 0) {
                response = ips[i];
                break;
            }
        }

        sendto(sock, response, strlen(response), 0,
               (struct sockaddr *)&client, len);
    }

    close(sock);
    return 0;
}