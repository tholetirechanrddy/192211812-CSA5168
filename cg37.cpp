#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char english_freq[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

void count_frequencies(char *ciphertext, int *freq) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            freq[ciphertext[i] - 'A']++;
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            freq[ciphertext[i] - 'a']++;
        }
    }
}

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}
void generate_plaintext(char *ciphertext, char *plaintext, char *mapping) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = mapping[ciphertext[i] - 'A'];
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = mapping[ciphertext[i] - 'a'] + 32; 
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}

void letter_frequency_attack(char *ciphertext, int top_n) {
    int freq[26] = {0};          
    int sorted_freq[26];        
    char mapping[26];            
    char possible_plaintext[1000]; 
    char temp_ciphertext[1000];

    strcpy(temp_ciphertext, ciphertext);

    count_frequencies(temp_ciphertext, freq);

    int positions[26];
    for (int i = 0; i < 26; i++) {
        sorted_freq[i] = freq[i];
        positions[i] = i; 
    }

    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (sorted_freq[i] < sorted_freq[j]) {
                int temp = sorted_freq[i];
                sorted_freq[i] = sorted_freq[j];
                sorted_freq[j] = temp;

                temp = positions[i];
                positions[i] = positions[j];
                positions[j] = temp;
            }
        }
    }

    for (int attempt = 0; attempt < top_n && attempt < 26; attempt++) {
        for (int i = 0; i < 26; i++) {
            mapping[positions[i]] = english_freq[i];
        }

        generate_plaintext(temp_ciphertext, possible_plaintext, mapping);
        printf("Possible Plaintext #%d:\n%s\n\n", attempt + 1, possible_plaintext);
    }
}

int main() {
    char ciphertext[1000];
    int top_n;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, 1000, stdin);

    int length = strlen(ciphertext);
    if (ciphertext[length - 1] == '\n') {
        ciphertext[length - 1] = '\0';
    }

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &top_n);

    letter_frequency_attack(ciphertext, top_n);

    return 0;
}

