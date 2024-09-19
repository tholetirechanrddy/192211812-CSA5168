#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

void prepare_key(char key_table[5][5]) {
    char key[5][5] = {
        {'M', 'F', 'H', 'I', 'J'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };
 
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            key_table[i][j] = key[i][j];
        }
    }
}

void find_position(char ch, char key_table[5][5], int *row, int *col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (key_table[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void playfair_encrypt(char *plaintext, char key_table[5][5], char *ciphertext) {
    int index = 0;
    int length = strlen(plaintext);

    for (int i = 0; i < length; i++) {
        if (isalpha(plaintext[i])) {
            char ch = toupper(plaintext[i]);
            if (ch == 'J') ch = 'I';  
            plaintext[index++] = ch;
        }
    }
    plaintext[index] = '\0';  
 
    for (int i = 0; i < index; i += 2) {
        char ch1 = plaintext[i];
        char ch2 = (i + 1 < index) ? plaintext[i + 1] : 'X';  

        if (ch1 == ch2) {
            ch2 = 'X';  
            i--;  
        }

        int row1, col1, row2, col2;
        find_position(ch1, key_table, &row1, &col1);
        find_position(ch2, key_table, &row2, &col2);

        if (row1 == row2) {
            ciphertext[i] = key_table[row1][(col1 + 1) % 5];
            ciphertext[i + 1] = key_table[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            ciphertext[i] = key_table[(row1 + 1) % 5][col1];
            ciphertext[i + 1] = key_table[(row2 + 1) % 5][col2];
        } else {
            ciphertext[i] = key_table[row1][col2];
            ciphertext[i + 1] = key_table[row2][col1];
        }
    }
    ciphertext[index] = '\0';  
}

int main() {
    char key_table[5][5];
    char plaintext[MAX_LEN] = "Must see you over Cadogan West. Coming at once.";
    char ciphertext[MAX_LEN];

    prepare_key(key_table);
    playfair_encrypt(plaintext, key_table, ciphertext);

    printf("Encrypted message: %s\n", ciphertext);
    return 0;
}

