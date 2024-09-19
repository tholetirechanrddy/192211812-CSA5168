#include <stdio.h>
#include <ctype.h>
#include <string.h> 

#define ALPHABET_SIZE 26 
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
} 
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;   
}
 
char affineDecryptChar(char c, int a, int b) {
    if (isalpha(c)) {
        char base = islower(c) ? 'a' : 'A';
        int num = toupper(c) - 'A';
        int a_inv = modInverse(a, ALPHABET_SIZE);
        if (a_inv == -1) {
            return c;  
        }
        int p = (a_inv * (num - b + ALPHABET_SIZE)) % ALPHABET_SIZE;
        return base + p;
    }
    return c;   
} 
void affineDecrypt(const char *ciphertext, char *plaintext, int a, int b) {
    int i = 0;
    while (ciphertext[i]) {
        plaintext[i] = affineDecryptChar(ciphertext[i], a, b);
        i++;
    }
    plaintext[i] = '\0';   
}
 
void breakAffineCipher(const char *ciphertext) {
    char mostFrequent = 'B';
    char secondMostFrequent = 'U';
    char plaintext[100];
    char decryptedText[100];
    
    int mostFrequentIndex = mostFrequent - 'A';
    int secondMostFrequentIndex = secondMostFrequent - 'A';
 
    for (int a = 1; a < ALPHABET_SIZE; a++) {
        if (gcd(a, ALPHABET_SIZE) != 1) {
            continue;   
        }
        for (int b = 0; b < ALPHABET_SIZE; b++) { 
            int possible_p1 = (mostFrequentIndex - b + ALPHABET_SIZE) % ALPHABET_SIZE;
            int possible_p2 = (secondMostFrequentIndex - b + ALPHABET_SIZE) % ALPHABET_SIZE;
            int a_inv = modInverse(a, ALPHABET_SIZE);
            if (a_inv == -1) {
                continue;   
            }
            int plainChar1 = (a_inv * possible_p1) % ALPHABET_SIZE;
            int plainChar2 = (a_inv * possible_p2) % ALPHABET_SIZE;
 
            affineDecrypt(ciphertext, decryptedText, a, b);
            printf("Trying a = %d, b = %d\n", a, b);
            printf("Decrypted Text: %s\n", decryptedText);
        }
    }
}

int main() {
    char ciphertext[100];
    
    // Get the ciphertext from the user
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';  // Remove newline character

    // Break the affine cipher
    breakAffineCipher(ciphertext);

    return 0;
}

