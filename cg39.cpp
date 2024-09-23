#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_SIZE 1000
 
double english_freq[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 
    6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 
    7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 
    0.978, 2.360, 0.150, 1.974, 0.074
};
 
void calculate_frequency(const char *text, double *freq) {
    int letter_count[ALPHABET_SIZE] = {0};
    int total_letters = 0;
    
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            letter_count[toupper(text[i]) - 'A']++;
            total_letters++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = ((double)letter_count[i] / total_letters) * 100;
    }
}
 
void decrypt(const char *ciphertext, char *plaintext, int key) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            plaintext[i] = (ciphertext[i] - base - key + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}
 
double compute_score(const double *freq) {
    double score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += freq[i] * english_freq[i];
    }
    return score;
}
 
typedef struct {
    char plaintext[MAX_TEXT_SIZE];
    double score;
} Candidate;
 
int compare_candidates(const void *a, const void *b) {
    Candidate *ca = (Candidate *)a;
    Candidate *cb = (Candidate *)b;
    return (cb->score - ca->score) > 0 ? 1 : -1;
}
 
int main() {
    char ciphertext[MAX_TEXT_SIZE];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_SIZE, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0;  
    
    int top_n;
    printf("Enter the number of top plaintexts to display: ");
    scanf("%d", &top_n);
 
    Candidate candidates[ALPHABET_SIZE];
      
    for (int key = 0; key < ALPHABET_SIZE; key++) {
        char plaintext[MAX_TEXT_SIZE];
        decrypt(ciphertext, plaintext, key);
        
        double freq[ALPHABET_SIZE] = {0.0};
        calculate_frequency(plaintext, freq);
        
        double score = compute_score(freq);
        
        strcpy(candidates[key].plaintext, plaintext);
        candidates[key].score = score;
    }
      
    qsort(candidates, ALPHABET_SIZE, sizeof(Candidate), compare_candidates);
 
    printf("\nTop %d possible plaintexts:\n", top_n);
    for (int i = 0; i < top_n; i++) {
        printf("%d: %s (score: %.2f)\n", i+1, candidates[i].plaintext, candidates[i].score);
    }

    return 0;
}

