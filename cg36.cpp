#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; 
}

void encrypt(char* plaintext, char* ciphertext, int a, int b) {
    int i = 0;
    while (plaintext[i] != '\0') {
        char ch = plaintext[i];

        if (ch >= 'A' && ch <= 'Z') {
            ciphertext[i] = ((a * (ch - 'A') + b) % 26) + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            ciphertext[i] = ((a * (ch - 'a') + b) % 26) + 'a';
        } else {
            ciphertext[i] = ch; 
        }
        i++;
    }
    ciphertext[i] = '\0'; 
}

void decrypt(char* ciphertext, char* plaintext, int a, int b) {
    int i = 0;
    int a_inv = mod_inverse(a, 26); 
    
    if (a_inv == -1) {
        printf("Decryption not possible, 'a' and 26 are not coprime.\n");
        return;
    }

    while (ciphertext[i] != '\0') {
        char ch = ciphertext[i];

        if (ch >= 'A' && ch <= 'Z') {
            plaintext[i] = (a_inv * ((ch - 'A' - b + 26) % 26)) % 26 + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            plaintext[i] = (a_inv * ((ch - 'a' - b + 26) % 26)) % 26 + 'a';
        } else {
            plaintext[i] = ch; 
        }
        i++;
    }
    plaintext[i] = '\0'; 
}

int main() {
    char plaintext[100], ciphertext[100], decryptedtext[100];
    int a, b;

    printf("Enter the value of a: ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);

    if (gcd(a, 26) != 1) {
        printf("'a' must be coprime with 26 for the cipher to work.\n");
        return 1;
    }

    printf("Enter the plaintext: ");
    getchar();
    fgets(plaintext, 100, stdin);

    int length = 0;
    while (plaintext[length] != '\0') {
        if (plaintext[length] == '\n') {
            plaintext[length] = '\0';
            break;
        }
        length++;
    }

    encrypt(plaintext, ciphertext, a, b);
    printf("Encrypted text: %s\n", ciphertext);

    decrypt(ciphertext, decryptedtext, a, b);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

