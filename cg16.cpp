#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26
#define MAX_CIPHERTEXT_LENGTH 1000
#define TOP_N 10
 
void calculate_frequency(const char *ciphertext, double frequency[ALPHABET_SIZE]) {
    int letter_count = 0;
    int count[ALPHABET_SIZE] = {0};

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            count[ciphertext[i] - 'a']++;
            letter_count++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequency[i] = (double)count[i] / letter_count;
    }
}
 
void decrypt(const char *ciphertext, const char *substitution, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = substitution[ciphertext[i] - 'a'];
        } else {
            plaintext[i] = ciphertext[i];  
        }
    }
    plaintext[strlen(ciphertext)] = '\0';  
}
 
void generate_possible_plaintexts(const char *ciphertext, int top_n) {
    double frequency[ALPHABET_SIZE];
    calculate_frequency(ciphertext, frequency);

    char plaintext[MAX_CIPHERTEXT_LENGTH];
    char substitution[ALPHABET_SIZE];
    
    char english_order[ALPHABET_SIZE] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'u', 'c', 'm', 'w', 'f', 'y', 'p', 'b', 'g', 'v', 'k', 'j', 'x', 'q', 'z'};
     
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        substitution[i] = ' ';
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) { 
        if (i < ALPHABET_SIZE) {
            substitution[i] = english_order[i];
        }
    }

    printf("Top %d possible plaintexts:\n", top_n);
     
    for (int i = 0; i < top_n; i++) {
        decrypt(ciphertext, substitution, plaintext);
        printf("Plaintext %d: %s\n", i + 1, plaintext);
         
        char temp = substitution[0];
        for (int j = 0; j < ALPHABET_SIZE - 1; j++) {
            substitution[j] = substitution[j + 1];
        }
        substitution[ALPHABET_SIZE - 1] = temp;
    }
}

int main() {
    char ciphertext[MAX_CIPHERTEXT_LENGTH];
    
    printf("Enter ciphertext (lowercase letters only): ");
    fgets(ciphertext, MAX_CIPHERTEXT_LENGTH, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0;  

    int top_n;
    printf("How many top possible plaintexts would you like to see? ");
    scanf("%d", &top_n);
    
    if (top_n > TOP_N) {
        top_n = TOP_N;  
    }

    generate_possible_plaintexts(ciphertext, top_n);

    return 0;
}

