#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 16
#define BLOCK_SIZE_64 8 
#define R_CON_128 0x87 
#define R_CON_64 0x1B 

void left_shift(uint8_t *input, uint8_t *output, int size) {
    int carry = 0;
    for (int i = 0; i < size; i++) {
        int new_carry = (input[i] >> 7) & 1;
        output[i] = (input[i] << 1) | carry;
        carry = new_carry;
    }
    if (carry) {
        output[size - 1] ^= R_CON_128;
    }
}

void generate_subkeys(uint8_t *key, uint8_t *k1, uint8_t *k2, int block_size) {
    uint8_t block[BLOCK_SIZE] = {0}; 
    uint8_t temp[BLOCK_SIZE] = {0};

    memcpy(temp, key, block_size);

    left_shift(temp, k1, block_size);
    
    left_shift(k1, k2, block_size);
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x00}; 
    uint8_t k1[BLOCK_SIZE] = {0};    
    uint8_t k2[BLOCK_SIZE] = {0};    

    generate_subkeys(key, k1, k2, BLOCK_SIZE);

    printf("K1: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", k1[i]);
    }
    printf("\nK2: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", k2[i]);
    }
    printf("\n");

    return 0;
}

