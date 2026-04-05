// packet_counter.c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    int count = 0;
    char buffer[1024];

    fp = fopen("capture.pcap", "rb");

    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    // read file in chunks
    while (fread(buffer, 1, sizeof(buffer), fp) > 0) {
        count++;
    }

    printf("Approx packet count: %d\n", count);

    fclose(fp);
    return 0;
}