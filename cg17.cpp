#include <stdio.h>
#include <stdint.h>

int initial_permutation[64] = { 
    58, 50, 42, 34, 26, 18, 10, 2, 
    60, 52, 44, 36, 28, 20, 12, 4, 
    62, 54, 46, 38, 30, 22, 14, 6, 
    64, 56, 48, 40, 32, 24, 16, 8, 
    57, 49, 41, 33, 25, 17, 9, 1, 
    59, 51, 43, 35, 27, 19, 11, 3, 
    61, 53, 45, 37, 29, 21, 13, 5, 
    63, 55, 47, 39, 31, 23, 15, 7 
};

int final_permutation[64] = { 
    40, 8, 48, 16, 56, 24, 64, 32, 
    39, 7, 47, 15, 55, 23, 63, 31, 
    38, 6, 46, 14, 54, 22, 62, 30, 
    37, 5, 45, 13, 53, 21, 61, 29, 
    36, 4, 44, 12, 52, 20, 60, 28, 
    35, 3, 43, 11, 51, 19, 59, 27, 
    34, 2, 42, 10, 50, 18, 58, 26, 
    33, 1, 41, 9, 49, 17, 57, 25 
};

int expansion_table[48] = { 
    32, 1, 2, 3, 4, 5, 
    4, 5, 6, 7, 8, 9, 
    8, 9, 10, 11, 12, 13, 
    12, 13, 14, 15, 16, 17, 
    16, 17, 18, 19, 20, 21, 
    20, 21, 22, 23, 24, 25, 
    24, 25, 26, 27, 28, 29, 
    28, 29, 30, 31, 32, 1 
};

int permutation_table[32] = { 
    16, 7, 20, 21, 
    29, 12, 28, 17, 
    1, 15, 23, 26, 
    5, 18, 31, 10, 
    2, 8, 24, 14, 
    32, 27, 3, 9, 
    19, 13, 30, 6, 
    22, 11, 4, 25 
};

int s_box[8][4][16] = {  };

int key_shifts[16] = { 
    1, 1, 2, 2, 2, 2, 2, 2, 
    1, 2, 2, 2, 2, 2, 2, 1 
};

int permuted_choice_1[56] = { 
    57, 49, 41, 33, 25, 17, 9, 
    1, 58, 50, 42, 34, 26, 18, 
    10, 2, 59, 51, 43, 35, 27, 
    19, 11, 3, 60, 52, 44, 36, 
    63, 55, 47, 39, 31, 23, 15, 
    7, 62, 54, 46, 38, 30, 22, 
    14, 6, 61, 53, 45, 37, 29, 
    21, 13, 5, 28, 20, 12, 4 
};

int permuted_choice_2[48] = { 
    14, 17, 11, 24, 1, 5, 
    3, 28, 15, 6, 21, 10, 
    23, 19, 12, 4, 26, 8, 
    16, 7, 27, 20, 13, 2, 
    41, 52, 31, 37, 47, 55, 
    30, 40, 51, 45, 33, 48, 
    44, 49, 39, 56, 34, 53, 
    46, 42, 50, 36, 29, 32 
};

uint64_t rotate_left(uint64_t n, int d, int total_bits) {
    return ((n << d) | (n >> (total_bits - d))) & ((1ULL << total_bits) - 1);
}

uint64_t permute(uint64_t input, int *table, int n) {
    uint64_t output = 0;
    for (int i = 0; i < n; i++) {
        output <<= 1;
        output |= (input >> (64 - table[i])) & 1;
    }
    return output;
}

uint32_t feistel(uint32_t R, uint64_t K) {
    uint64_t expanded_R = permute(R, expansion_table, 48);
    uint64_t xored = expanded_R ^ K;

    uint32_t sbox_output = 0;
    for (int i = 0; i < 8; i++) {
        int row = ((xored >> (42 - 6 * i)) & 0x20) | ((xored >> (42 - 6 * i)) & 1);
        int col = (xored >> (43 - 6 * i)) & 0x1E;
        sbox_output <<= 4;
        sbox_output |= s_box[i][row][col];
    }

    return permute(sbox_output, permutation_table, 32);
}

uint64_t des_decrypt(uint64_t ciphertext, uint64_t subkeys[16]) {
    uint64_t permuted_input = permute(ciphertext, initial_permutation, 64);
    uint32_t L = permuted_input >> 32;
    uint32_t R = permuted_input & 0xFFFFFFFF;

    for (int i = 15; i >= 0; i--) {
        uint32_t temp = R;
        R = L ^ feistel(R, subkeys[i]);
        L = temp;
    }

    uint64_t preoutput = ((uint64_t)R << 32) | L;
    return permute(preoutput, final_permutation, 64);
}
void generate_keys(uint64_t key, uint64_t subkeys[16]) {
    uint64_t permuted_key = permute(key, permuted_choice_1, 56);
    uint32_t C = permuted_key >> 28;
    uint32_t D = permuted_key & 0x0FFFFFFF;

    for (int i = 0; i < 16; i++) {
        C = rotate_left(C, key_shifts[i], 28);
        D = rotate_left(D, key_shifts[i], 28);
        uint64_t combined = ((uint64_t)C << 28) | D;
        subkeys[i] = permute(combined, permuted_choice_2, 48);
    }
}

int main() {
    uint64_t ciphertext = 0x85E813540F0AB405; 
    uint64_t key = 0x133457799BBCDFF1; 
    uint64_t subkeys[16];

    generate_keys(key, subkeys);

    uint64_t plaintext = des_decrypt(ciphertext, subkeys);
    printf("Decrypted plaintext: %016llx\n", plaintext);

    return 0;
}

