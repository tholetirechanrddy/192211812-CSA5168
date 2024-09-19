#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100
 
void prepareKey(const char *key, char *preparedKey, int textLength) {
    int keyLength = strlen(key);
    int j = 0;
     
    for (int i = 0; i < textLength; i++) {
        if (isalpha(key[j])) {
            preparedKey[i] = toupper(key[j]);
            j = (j + 1) % keyLength;
        } else { 
            i--;
        }
    }
    preparedKey[textLength] = '\0';
}
 
void vigenereEncrypt(const char *plaintext, const char *key, char *ciphertext) {
    int textLength = strlen(plaintext);
    char preparedKey[MAX_LEN];
     
    prepareKey(key, preparedKey, textLength);
     
    for (int i = 0; i < textLength; i++) {
        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            char shift = toupper(preparedKey[i]) - 'A';
            ciphertext[i] = ((toupper(plaintext[i]) - 'A' + shift) % 26) + base;
        } else {
           
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[textLength] = '\0'; 
}

int main() {
    char plaintext[MAX_LEN];
    char key[MAX_LEN];
    char ciphertext[MAX_LEN];
    
        
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';   
     
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';   
     
    vigenereEncrypt(plaintext, key, ciphertext);
     
    printf("Ciphertext: %s\n", ciphertext);
    
    return 0;
}

