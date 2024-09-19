#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 2
#define MOD 26
 
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;  
}
 
int determinant(int key[MATRIX_SIZE][MATRIX_SIZE]) {
    return (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % MOD;
}
 
void get_inverse_matrix(int key[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(key);
    det = (det + MOD) % MOD;  
    int inv_det = mod_inverse(det, MOD);

    if (inv_det == -1) {
        printf("Inverse doesn't exist.\n");
        return;
    }

    inverse[0][0] = (key[1][1] * inv_det) % MOD;
    inverse[0][1] = (-key[0][1] * inv_det) % MOD;
    inverse[1][0] = (-key[1][0] * inv_det) % MOD;
    inverse[1][1] = (key[0][0] * inv_det) % MOD;
 
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (inverse[i][j] < 0) {
                inverse[i][j] += MOD;
            }
        }
    }
}
 
void encrypt(char *plaintext, int key[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext) {
    int len = strlen(plaintext);
    int index = 0;

    for (int i = 0; i < len; i += 2) {
        int a = plaintext[i] - 'a';
        int b = (i + 1 < len) ? plaintext[i + 1] - 'a' : 'x' - 'a';  

        ciphertext[index++] = (key[0][0] * a + key[0][1] * b) % MOD + 'a';
        ciphertext[index++] = (key[1][0] * a + key[1][1] * b) % MOD + 'a';
    }
    ciphertext[index] = '\0';  
}
 
void derive_key(char *plaintext, char *ciphertext, int key[MATRIX_SIZE][MATRIX_SIZE]) {
    int p1[2], p2[2], c1[2], c2[2];

    p1[0] = plaintext[0] - 'a';
    p1[1] = plaintext[1] - 'a';
    p2[0] = plaintext[2] - 'a';
    p2[1] = plaintext[3] - 'a';

    c1[0] = ciphertext[0] - 'a';
    c1[1] = ciphertext[1] - 'a';
    c2[0] = ciphertext[2] - 'a';
    c2[1] = ciphertext[3] - 'a';
 
    int matrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {p1[0], p1[1]},
        {p2[0], p2[1]}
    };

    int result[MATRIX_SIZE][MATRIX_SIZE] = {
        {c1[0], c1[1]},
        {c2[0], c2[1]}
    };
 
    int inv_matrix[MATRIX_SIZE][MATRIX_SIZE];
    get_inverse_matrix(matrix, inv_matrix);
 
    key[0][0] = (inv_matrix[0][0] * result[0][0] + inv_matrix[0][1] * result[1][0]) % MOD;
    key[0][1] = (inv_matrix[0][0] * result[0][1] + inv_matrix[0][1] * result[1][1]) % MOD;
    key[1][0] = (inv_matrix[1][0] * result[0][0] + inv_matrix[1][1] * result[1][0]) % MOD;
    key[1][1] = (inv_matrix[1][0] * result[0][1] + inv_matrix[1][1] * result[1][1]) % MOD;
}
 
void print_key_matrix(int key[MATRIX_SIZE][MATRIX_SIZE]) {
    printf("Recovered Key Matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }
}

int main() { 
    char plaintext[] = "meet";
    char ciphertext[] = "qgzm";  
    int key[MATRIX_SIZE][MATRIX_SIZE];
 
    derive_key(plaintext, ciphertext, key);
    print_key_matrix(key);
 
    char new_plaintext[] = "attackatdawn";
    char new_ciphertext[100];
    encrypt(new_plaintext, key, new_ciphertext);
    printf("Encrypted message: %s\n", new_ciphertext);

    return 0;
}

