#include <stdio.h>
#include <string.h>

#define MATRIX_SIZE 2
#define MOD 26
 
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}

void get_inverse_matrix(int key[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % MOD;
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
    int i, index = 0;

    for (i = 0; i < len; i += 2) {
        if (plaintext[i] == ' ') {
            i--; 
            continue;
        }

        int a = plaintext[i] - 'a';
        int b = (i + 1 < len && plaintext[i + 1] != ' ') ? plaintext[i + 1] - 'a' : 'x' - 'a';  

        ciphertext[index++] = (key[0][0] * a + key[0][1] * b) % MOD + 'a';
        ciphertext[index++] = (key[1][0] * a + key[1][1] * b) % MOD + 'a';
    }
    ciphertext[index] = '\0';  
}

void decrypt(char *ciphertext, int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext) {
    int inverse[MATRIX_SIZE][MATRIX_SIZE];
    get_inverse_matrix(key, inverse);

    int len = strlen(ciphertext);
    int i, index = 0;

    for (i = 0; i < len; i += 2) {
        int a = ciphertext[i] - 'a';
        int b = ciphertext[i + 1] - 'a';

        plaintext[index++] = (inverse[0][0] * a + inverse[0][1] * b) % MOD + 'a';
        plaintext[index++] = (inverse[1][0] * a + inverse[1][1] * b) % MOD + 'a';
    }
    plaintext[index] = '\0';  
}

int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE] = {{9, 4}, {5, 7}};
    char plaintext[] = "meetmeattheusualplaceattenrathertahaneightoclock";
    char ciphertext[100];
    char decrypted[100];

    encrypt(plaintext, key, ciphertext);
    printf("Encrypted message: %s\n", ciphertext);

    decrypt(ciphertext, key, decrypted);
    printf("Decrypted message: %s\n", decrypted);

    return 0;
}

