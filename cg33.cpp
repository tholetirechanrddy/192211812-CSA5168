#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8  
#define KEY_SIZE 8    
int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2, 
    60, 52, 44, 36, 28, 20, 12, 4, 
    62, 54, 46, 38, 30, 22, 14, 6, 
    64, 56, 48, 40, 32, 24, 16, 8, 
    57, 49, 41, 33, 25, 17, 9, 1, 
    59, 51, 43, 35, 27, 19, 11, 3, 
    61, 53, 45, 37, 29, 21, 13, 5, 
    63, 55, 47, 39, 31, 23, 15, 7
};
 
int FP[] = {
    40, 8, 48, 16, 56, 24, 64, 32, 
    39, 7, 47, 15, 55, 23, 63, 31, 
    38, 6, 46, 14, 54, 22, 62, 30, 
    37, 5, 45, 13, 53, 21, 61, 29, 
    36, 4, 44, 12, 52, 20, 60, 28, 
    35, 3, 43, 11, 51, 19, 59, 27, 
    34, 2, 42, 10, 50, 18, 58, 26, 
    33, 1, 41, 9, 49, 17, 57, 25
};
 
int S_BOX[4][16] = {
    {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
    {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
};
 
void permute(unsigned char *in, unsigned char *out, int *table, int n) {
    for (int i = 0; i < n; i++) {
        int pos = table[i] - 1;
        int byte_pos = pos / 8;
        int bit_pos = pos % 8;
        out[i / 8] |= ((in[byte_pos] >> (7 - bit_pos)) & 0x01) << (7 - (i % 8));
    }
} 
void des_encrypt(unsigned char *plain_text, unsigned char *key, unsigned char *cipher_text) {
    unsigned char permuted_block[BLOCK_SIZE] = {0};
 
    permute(plain_text, permuted_block, IP, 64);
 
    permute(permuted_block, cipher_text, FP, 64);
}

int main() {
    unsigned char plain_text[BLOCK_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0};  
    unsigned char key[KEY_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9b, 0xbc, 0xde, 0xef};  
    unsigned char cipher_text[BLOCK_SIZE] = {0};

    printf("Plaintext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", plain_text[i]);
    }
    printf("\n");
 
    des_encrypt(plain_text, key, cipher_text);
 
    printf("Ciphertext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", cipher_text[i]);
    }
    printf("\n");

    return 0;
}

