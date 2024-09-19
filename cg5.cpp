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
 
int isCoprimeWith26(int a) {
    return gcd(a, ALPHABET_SIZE) == 1;
}
 
void affineEncrypt(const char *plaintext, char *ciphertext, int a, int b) {
    int i = 0;
    while (plaintext[i]) {
        char ch = plaintext[i];
        if (isalpha(ch)) {
        
            char base = islower(ch) ? 'a' : 'A';
            int p = toupper(ch) - 'A';
         
            int C = (a * p + b) % ALPHABET_SIZE;
             
            ciphertext[i] = base + C;
        } else { 
            ciphertext[i] = ch;
        }
        i++;
    }
    ciphertext[i] = '\0';   
}

int main() {
    char plaintext[100];
    char ciphertext[100];
    int a, b;
 
    printf("Enter value for a (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter value for b: ");
    scanf("%d", &b);
 
    if (a < 0 || a >= ALPHABET_SIZE || !isCoprimeWith26(a)) {
        printf("Invalid value for a. It must be between 0 and 25 and coprime with 26.\n");
        return 1;
    }
 
    printf("Enter the plaintext: ");
    getchar();   
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';   
 
    affineEncrypt(plaintext, ciphertext, a, b);
 
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

