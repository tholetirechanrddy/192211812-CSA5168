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
 
typedef struct {
    char letter;
    double freq;
} LetterFreq;
 
void calculate_frequency(const char *text, LetterFreq *freq) {
    int letter_count[ALPHABET_SIZE] = {0};
    int total_letters = 0;
    
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            letter_count[toupper(text[i]) - 'A']++;
            total_letters++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i].letter = 'A' + i;
        freq[i].freq = ((double)letter_count[i] / total_letters) * 100;
    }
}
 
int compare_letter_freq(const void *a, const void *b) {
    LetterFreq *la = (LetterFreq *)a;
    LetterFreq *lb = (LetterFreq *)b;
    return (lb->freq - la->freq) > 0 ? 1 : -1;
}
 
void decrypt(const char *ciphertext, char *plaintext, char *mapping) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            int index = toupper(ciphertext[i]) - 'A';
            plaintext[i] = islower(ciphertext[i]) ? tolower(mapping[index]) : mapping[index];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}
 
double compute_score(const char *plaintext) {
    int letter_count[ALPHABET_SIZE] = {0};
    int total_letters = 0;

    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            letter_count[toupper(plaintext[i]) - 'A']++;
            total_letters++;
        }
    }

    double score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        double freq_in_text = ((double)letter_count[i] / total_letters) * 100;
        score += freq_in_text * english_freq[i];
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
 
    LetterFreq cipher_freq[ALPHABET_SIZE];
    calculate_frequency(ciphertext, cipher_freq);
 
    qsort(cipher_freq, ALPHABET_SIZE, sizeof(LetterFreq), compare_letter_freq);
 
    Candidate candidates[ALPHABET_SIZE];
     
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        char mapping[ALPHABET_SIZE];
 
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            mapping[cipher_freq[j].letter - 'A'] = 'A' + j;
        }
 
        char plaintext[MAX_TEXT_SIZE];
        decrypt(ciphertext, plaintext, mapping);
 
        double score = compute_score(plaintext);
         
        strcpy(candidates[i].plaintext, plaintext);
        candidates[i].score = score;
    }
 
    qsort(candidates, ALPHABET_SIZE, sizeof(Candidate), compare_candidates);
 
    printf("\nTop %d possible plaintexts:\n", top_n);
    for (int i = 0; i < top_n; i++) {
        printf("%d: %s (score: %.2f)\n", i+1, candidates[i].plaintext, candidates[i].score);
    }

    return 0;
}

