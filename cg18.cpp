#include <stdio.h>
#include <stdint.h>

int pc1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

int pc2[48] = {
    14, 17, 11, 24, 1, 5, 
    3, 28, 15, 6, 21, 10, 
    23, 19, 12, 4, 26, 8, 
    16, 7, 27, 20, 13, 2, 
    41, 52, 31, 37, 47, 55, 
    30, 40, 51, 45, 33, 48, 
    44, 49, 39, 56, 34, 53, 
    46, 42, 50, 36, 29, 32 
};

int shift_schedule[16] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

uint32_t rotate_left(uint32_t value, int shifts, int size) {
    return ((value << shifts) | (value >> (size - shifts))) & ((1 << size) - 1);
}

uint64_t permute(uint64_t input, int *table, int n) {
    uint64_t output = 0;
    for (int i = 0; i < n; i++) {
        output <<= 1;
        output |= (input >> (64 - table[i])) & 1;
    }
    return output;
}

void generate_subkeys(uint64_t key, uint64_t subkeys[16]) {
    uint64_t permuted_key = permute(key, pc1, 56);
    
    uint32_t C = (permuted_key >> 28) & 0x0FFFFFFF;
    uint32_t D = permuted_key & 0x0FFFFFFF;

    // Generate 16 subkeys
    for (int round = 0; round < 16; round++) {
        C = rotate_left(C, shift_schedule[round], 28);
        D = rotate_left(D, shift_schedule[round], 28);

        uint64_t combined = ((uint64_t)C << 28) | D;
        subkeys[round] = permute(combined, pc2, 48);

        printf("Subkey %d: %012llx\n", round + 1, subkeys[round]);
    }
}

int main() {
    uint64_t key = 0x133457799BBCDFF1; 

    uint64_t subkeys[16];

    generate_subkeys(key, subkeys);

    return 0;
}

