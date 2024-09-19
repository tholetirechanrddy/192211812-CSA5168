#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CIPHERTEXT_SIZE 1000
#define ALPHABET_SIZE 256 
void countFrequency(const char *ciphertext, int frequency[]) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        unsigned char ch = ciphertext[i];
        if (ch >= 32 && ch <= 126) {  
            frequency[ch]++;
        }
    }
} 
void printFrequency(int frequency[]) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > 0) {
            printf("Character '%c' (ASCII %d) appears %d times\n", i, i, frequency[i]);
        }
    }
} 
void decrypt(const char *ciphertext, char *plaintext, char *substitution) {
    int i = 0;
    while (ciphertext[i]) {
        if (isprint(ciphertext[i])) {
            plaintext[i] = substitution[(unsigned char)ciphertext[i]];
        } else {
            plaintext[i] = ciphertext[i];
        }
        i++;
    }
    plaintext[i] = '\0';
}

int main() {
    char ciphertext[MAX_CIPHERTEXT_SIZE] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 (88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    int frequency[ALPHABET_SIZE] = {0};
    char substitution[ALPHABET_SIZE];
    char plaintext[MAX_CIPHERTEXT_SIZE]; 
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        substitution[i] = (char)i;
    } 
    countFrequency(ciphertext, frequency); 
    printf("Character frequencies:\n");
    printFrequency(frequency);
 
    decrypt(ciphertext, plaintext, substitution); 
    printf("Decrypted text:\n%s\n", plaintext);

    return 0;
}

