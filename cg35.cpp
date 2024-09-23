#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_LEN 100

void generate_random_key(int *key, int length) {
    for (int i = 0; i < length; i++) {
        key[i] = rand() % 26; 
    }
}

void encrypt(char *plaintext, char *ciphertext, int *key, int length) {
    for (int i = 0; i < length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A' + key[i]) % 26) + 'A'; 
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((plaintext[i] - 'a' + key[i]) % 26) + 'a'; 
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[length] = '\0'; 
}

void decrypt(char *ciphertext, char *plaintext, int *key, int length) {
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - key[i] + 26) % 26) + 'A'; 
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((ciphertext[i] - 'a' - key[i] + 26) % 26) + 'a';
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[length] = '\0'; 
}

int main() {
    char plaintext[MAX_LEN], ciphertext[MAX_LEN], decryptedtext[MAX_LEN];
    int key[MAX_LEN];

    srand(time(0));

    printf("Enter the plaintext: ");
    fgets(plaintext, MAX_LEN, stdin);

    int length = strlen(plaintext);
    if (plaintext[length - 1] == '\n') {
        plaintext[length - 1] = '\0';
        length--;
    }

    generate_random_key(key, length);

    printf("Generated key: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");

    encrypt(plaintext, ciphertext, key, length);
    printf("Ciphertext: %s\n", ciphertext);

    decrypt(ciphertext, decryptedtext, key, length);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

