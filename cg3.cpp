#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5
 
void generateMatrix(const char *keyword, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int used[26] = {0};   
    int k = 0;
     
    for (int i = 0; keyword[i]; i++) {
        char ch = toupper(keyword[i]);
        if (ch == 'J') ch = 'I';   
        if (isalpha(ch) && !used[ch - 'A']) {
            matrix[k / MATRIX_SIZE][k % MATRIX_SIZE] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }
     
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue;   
        if (!used[ch - 'A']) {
            matrix[k / MATRIX_SIZE][k % MATRIX_SIZE] = ch;
            k++;
        }
    }
} 
void prepareText(const char *input, char *output) {
    int len = strlen(input);
    int j = 0;
    
    for (int i = 0; i < len; i++) {
        char ch = toupper(input[i]);
        if (ch == 'J') ch = 'I';  
        if (isalpha(ch)) {
            if (j > 0 && output[j - 1] == ch) {
                output[j++] = 'X';  
            }
            output[j++] = ch;
        }
    }
     
    if (j % 2 != 0) {
        output[j++] = 'X';
    }
    
    output[j] = '\0';
}
 
void encryptDigraphs(const char matrix[MATRIX_SIZE][MATRIX_SIZE], const char *plaintext, char *ciphertext) {
    int len = strlen(plaintext);
    int j = 0;
    
    for (int i = 0; i < len; i += 2) {
        char a = plaintext[i];
        char b = plaintext[i + 1];
        int row1, col1, row2, col2;
         
        for (int r = 0; r < MATRIX_SIZE; r++) {
            for (int c = 0; c < MATRIX_SIZE; c++) {
                if (matrix[r][c] == a) {
                    row1 = r; col1 = c;
                }
                if (matrix[r][c] == b) {
                    row2 = r; col2 = c;
                }
            }
        }
         
        if (row1 == row2) { 
            ciphertext[j++] = matrix[row1][(col1 + 1) % MATRIX_SIZE];
            ciphertext[j++] = matrix[row2][(col2 + 1) % MATRIX_SIZE];
        } else if (col1 == col2) { 
            ciphertext[j++] = matrix[(row1 + 1) % MATRIX_SIZE][col1];
            ciphertext[j++] = matrix[(row2 + 1) % MATRIX_SIZE][col2];
        } else { 
            ciphertext[j++] = matrix[row1][col2];
            ciphertext[j++] = matrix[row2][col1];
        }
    }
    
    ciphertext[j] = '\0';
}

int main() {
    char keyword[100];
    char plaintext[100];
    char matrix[MATRIX_SIZE][MATRIX_SIZE];
    char preparedText[200];
    char ciphertext[200];
    
    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';  
    
    generateMatrix(keyword, matrix);
     
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';   
     
    prepareText(plaintext, preparedText);
     
    encryptDigraphs(matrix, preparedText, ciphertext);
     
    printf("Ciphertext: %s\n", ciphertext);
    
    return 0;
}

