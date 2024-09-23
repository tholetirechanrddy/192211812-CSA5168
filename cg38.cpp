#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 3  
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

int determinant(int matrix[SIZE][SIZE]) {
    int det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
            - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
            + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    return det % 26;
}

void cofactor(int matrix[SIZE][SIZE], int cofactor_matrix[SIZE][SIZE]) {
    cofactor_matrix[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) % 26;
    cofactor_matrix[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) % 26;
    cofactor_matrix[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) % 26;

    cofactor_matrix[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) % 26;
    cofactor_matrix[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) % 26;
    cofactor_matrix[1][2] = (matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2]) % 26;

    cofactor_matrix[2][0] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) % 26;
    cofactor_matrix[2][1] = (matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1]) % 26;
    cofactor_matrix[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
}

void adjugate(int matrix[SIZE][SIZE], int adj_matrix[SIZE][SIZE]) {
    int cofactor_matrix[SIZE][SIZE];
    cofactor(matrix, cofactor_matrix);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            adj_matrix[i][j] = cofactor_matrix[j][i];
        }
    }
}

int inverse_matrix(int matrix[SIZE][SIZE], int inv_matrix[SIZE][SIZE]) {
    int det = determinant(matrix);
    int det_inv = mod_inverse(det, 26);

    if (det_inv == -1) {
        return 0; 
    }

    int adj_matrix[SIZE][SIZE];
    adjugate(matrix, adj_matrix);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            inv_matrix[i][j] = (adj_matrix[i][j] * det_inv) % 26;
            if (inv_matrix[i][j] < 0) {
                inv_matrix[i][j] += 26; 
            }
        }
    }

    return 1; 
}

void matrix_multiply(int a[SIZE][SIZE], int b[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
            result[i][j] %= 26;
        }
    }
}

void hill_cipher_encrypt(int key[SIZE][SIZE], int plaintext_vector[SIZE], int ciphertext_vector[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        ciphertext_vector[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            ciphertext_vector[i] += key[i][j] * plaintext_vector[j];
        }
        ciphertext_vector[i] %= 26;
    }
}

void hill_cipher_attack(int plaintext_matrix[SIZE][SIZE], int ciphertext_matrix[SIZE][SIZE], int key_matrix[SIZE][SIZE]) {
    int inv_plaintext_matrix[SIZE][SIZE];

    if (inverse_matrix(plaintext_matrix, inv_plaintext_matrix)) {
        matrix_multiply(inv_plaintext_matrix, ciphertext_matrix, key_matrix);
        printf("Recovered Key Matrix:\n");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", key_matrix[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("Plaintext matrix is not invertible. Attack failed.\n");
    }
}

void char_to_int_vector(char *text, int vector[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        vector[i] = text[i] - 'A';
    }
}

void int_to_char_vector(int vector[SIZE], char *text) {
    for (int i = 0; i < SIZE; i++) {
        text[i] = vector[i] + 'A';
    }
    text[SIZE] = '\0'; 
}

int main() {
    char plaintext[SIZE + 1], ciphertext[SIZE + 1];
    int plaintext_matrix[SIZE][SIZE], ciphertext_matrix[SIZE][SIZE], key_matrix[SIZE][SIZE];

    printf("Enter 3-letter plaintext (uppercase): ");
    scanf("%s", plaintext);

    printf("Enter corresponding 3-letter ciphertext (uppercase): ");
    scanf("%s", ciphertext);

    for (int i = 0; i < SIZE; i++) {
        char_to_int_vector(plaintext, plaintext_matrix[i]);
        char_to_int_vector(ciphertext, ciphertext_matrix[i]);
    }

    hill_cipher_attack(plaintext_matrix, ciphertext_matrix, key_matrix);

    return 0;
}

