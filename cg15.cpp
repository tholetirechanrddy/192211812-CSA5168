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
 
void decrypt(const char *ciphertext, int shift, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = (ciphertext[i] - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE + 'a';
        } else {
            plaintext[i] = ciphertext[i];  
        }
    }
    plaintext[strlen(ciphertext)] = '\0';  
}
 
void rank_plaintexts(const char *ciphertext, int top_n) {
    double frequency[ALPHABET_SIZE];
    calculate_frequency(ciphertext, frequency);

    char plaintext[MAX_CIPHERTEXT_LENGTH];
 
    int assumed_shift = 'e' - 'a';  
    double scores[ALPHABET_SIZE] = {0};

    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        decrypt(ciphertext, shift, plaintext);
         
        for (int i = 0; plaintext[i] != '\0'; i++) {
            if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
                scores[shift] += frequency[plaintext[i] - 'a'];
            }
        }
    }
 
    printf("Top %d possible plaintexts:\n", top_n);
    for (int i = 0; i < top_n; i++) { 
        int best_shift = -1;
        double best_score = -1;

        for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
            if (scores[shift] > best_score) {
                best_score = scores[shift];
                best_shift = shift;
            }
        }
 
        decrypt(ciphertext, best_shift, plaintext);
        printf("Shift %d: %s (Score: %.5f)\n", best_shift, plaintext, best_score);
        scores[best_shift] = -1;  
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

    rank_plaintexts(ciphertext, top_n);

    return 0;
}

