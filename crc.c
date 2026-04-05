#include <stdio.h>
#include <string.h>

int main() {
    char data[100], key[30];
    char temp[100], rem[30];
    int data_len, key_len, i, j;

    printf("Enter Data: ");
    scanf("%s", data);

    printf("Enter Generator (Key): ");
    scanf("%s", key);

    data_len = strlen(data);
    key_len = strlen(key);

    // copy data into temp
    strcpy(temp, data);

    // append zeros
    for (i = 0; i < key_len - 1; i++) {
        temp[data_len + i] = '0';
    }
    temp[data_len + i] = '\0';

    // division
    for (i = 0; i < data_len; i++) {
        if (temp[i] == '1') {
            for (j = 0; j < key_len; j++) {
                temp[i + j] =
                    (temp[i + j] == key[j]) ? '0' : '1';
            }
        }
    }

    // remainder
    strncpy(rem, temp + data_len, key_len - 1);
    rem[key_len - 1] = '\0';

    printf("CRC Remainder: %s\n", rem);

    // codeword
    strcat(data, rem);
    printf("Codeword (Sent Data): %s\n", data);

    return 0;
}