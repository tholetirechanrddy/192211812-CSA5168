#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26

void removeDuplicates(char *keyword) {
    int length = strlen(keyword);
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (keyword[i] == keyword[j]) {
                for (int k = j; k < length; k++) {
                    keyword[k] = keyword[k + 1];
                }
                length--;
                j--;
            }
        }
    }
}

void generateCipherAlphabet(const char *keyword, char *cipherAlphabet) {
    int used[ALPHABET_SIZE] = {0};
    int index = 0;

    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A']) {
            cipherAlphabet[index++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipherAlphabet[index++] = ch;
        }
    }
    cipherAlphabet[index] = '\0';
}

void createSubstitutionMap(const char *cipherAlphabet, char *map) {
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        map[ch - 'A'] = cipherAlphabet[ch - 'A'];
    }
}

void encrypt(const char *plaintext, char *ciphertext, const char *map) {
    int i = 0;
    while (plaintext[i]) {
        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            ciphertext[i] = map[toupper(plaintext[i]) - 'A'];
            if (islower(plaintext[i])) {
                ciphertext[i] = tolower(ciphertext[i]);
            }
        } else {
            ciphertext[i] = plaintext[i];
        }
        i++;
    }
    ciphertext[i] = '\0';
}

void decrypt(const char *ciphertext, char *plaintext, const char *map) {
    char reverseMap[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        reverseMap[map[i] - 'A'] = 'A' + i;
    }
    int i = 0;
    while (ciphertext[i]) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            plaintext[i] = reverseMap[toupper(ciphertext[i]) - 'A'];
            if (islower(ciphertext[i])) {
                plaintext[i] = tolower(plaintext[i]);
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
        i++;
    }
    plaintext[i] = '\0';
}

int main() {
    const char *keyword = "CIPHER";
    char cipherAlphabet[ALPHABET_SIZE + 1];
    char substitutionMap[ALPHABET_SIZE];
    char plaintext[100];
    char ciphertext[100];
    char decryptedText[100];

    generateCipherAlphabet(keyword, cipherAlphabet);
    printf("Cipher Alphabet: %s\n", cipherAlphabet);
 
    createSubstitutionMap(cipherAlphabet, substitutionMap); 
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';    
    encrypt(plaintext, ciphertext, substitutionMap);
    printf("Ciphertext: %s\n", ciphertext); 
    decrypt(ciphertext, decryptedText, substitutionMap);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}

