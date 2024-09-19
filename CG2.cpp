#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26
 
void createMapping(char *plaintext_alphabet, char *ciphertext_alphabet, char *mapping) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        mapping[plaintext_alphabet[i] - 'A'] = ciphertext_alphabet[i];
    }
} 
void encryptMessage(const char *plaintext, const char *mapping, char *ciphertext) {
    int i = 0;
    while (plaintext[i] != '\0') {
        if (isalpha(plaintext[i])) { 
            char ch = toupper(plaintext[i]);
            ciphertext[i] = mapping[ch - 'A'];
        } else { 
            ciphertext[i] = plaintext[i];
        }
        i++;
    }
    ciphertext[i] = '\0';  
}

int main() {
    char plaintext_alphabet[ALPHABET_SIZE + 1];
    char ciphertext_alphabet[ALPHABET_SIZE + 1];
    char mapping[ALPHABET_SIZE];
    char plaintext[100];
    char ciphertext[100];
 
    printf("Enter the plaintext alphabet (e.g., ABCDEFGHIJKLMNOPQRSTUVWXYZ): ");
    fgets(plaintext_alphabet, sizeof(plaintext_alphabet), stdin);
    plaintext_alphabet[strcspn(plaintext_alphabet, "\n")] = '\0';  

    printf("Enter the ciphertext alphabet (e.g., QWERTYUIOPASDFGHJKLZXCVBNM): ");
    fgets(ciphertext_alphabet, sizeof(ciphertext_alphabet), stdin);
    ciphertext_alphabet[strcspn(ciphertext_alphabet, "\n")] = '\0';  
 
    if (strlen(plaintext_alphabet) != ALPHABET_SIZE || strlen(ciphertext_alphabet) != ALPHABET_SIZE) {
        printf("Both alphabets must be exactly 26 characters long.\n");
        return 1;
    }
 
    createMapping(plaintext_alphabet, ciphertext_alphabet, mapping);

    printf("Enter the plaintext message: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  

    encryptMessage(plaintext, mapping, ciphertext);
 
    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}

