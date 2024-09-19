#include <stdio.h>
#include <string.h>

#define MAX_LEN 100
 
void encrypt(char *plaintext, int *key, int key_len, char *ciphertext) {
    int len = strlen(plaintext);
    int index = 0;

    for (int i = 0; i < len; i++) {
        if (plaintext[i] == ' ') {
            ciphertext[index++] = ' ';  
            continue;
        }
        int shift = key[i % key_len];
        ciphertext[index++] = (plaintext[i] - 'a' + shift) % 26 + 'a';  
    }
    ciphertext[index] = '\0';  
}
 
void derive_key(char *ciphertext, char *target_plaintext, int *derived_key) {
    int len = strlen(ciphertext);

    for (int i = 0; i < len; i++) {
        if (ciphertext[i] == ' ') {
            derived_key[i] = -1; 
            continue;
        }
        derived_key[i] = (ciphertext[i] - target_plaintext[i] + 26) % 26;   
    }
} 
void print_key(int *key, int len) {
    for (int i = 0; i < len; i++) {
        if (key[i] != -1) { 
            printf("%d ", key[i]);
        } else {
            printf("  "); 
        }
    }
    printf("\n");
}

int main() {
    char plaintext[] = "send more money";
    int key_stream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int key_len = sizeof(key_stream) / sizeof(key_stream[0]);
    char ciphertext[MAX_LEN];


    encrypt(plaintext, key_stream, key_len, ciphertext);
    printf("Encrypted ciphertext: %s\n", ciphertext);
 
    char target_plaintext[] = "cash not needed";
    int derived_key[MAX_LEN];
 
    derive_key(ciphertext, target_plaintext, derived_key);
    printf("Derived key: ");
    print_key(derived_key, strlen(ciphertext));

    return 0;
}

