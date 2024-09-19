#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void s_des_encrypt(uint8_t *block, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < 8; i++) {
        output[i] = block[i] ^ key[i];
    }
}
void s_des_decrypt(uint8_t *block, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < 8; i++) {
        output[i] = block[i] ^ key[i];
    }
}

void ctr_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *initial_counter, uint8_t *ciphertext, int len) {
    uint8_t counter[8];
    uint8_t keystream[8];
    uint8_t block[8];

    memcpy(counter, initial_counter, 8); 

    for (int i = 0; i < len; i += 8) {
        s_des_encrypt(counter, key, keystream);
        for (int j = 0; j < 8; j++) {
            block[j] = (i + j < len) ? plaintext[i + j] : 0;
        }
        for (int j = 0; j < 8; j++) {
            ciphertext[i + j] = block[j] ^ keystream[j];
        }
        for (int j = 7; j >= 0; j--) {
            if (++counter[j] != 0) break;
        }
    }
}
void ctr_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *initial_counter, uint8_t *plaintext, int len) {
    ctr_encrypt(ciphertext, key, initial_counter, plaintext, len);
}
void print_hex(const char *label, uint8_t *data, int len) {
    printf("%s: ", label);
    for (int i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}
void binary_to_byte_array(const char *binary, uint8_t *byte_array) {
    size_t len = strlen(binary);
    for (size_t i = 0; i < len; i += 8) {
        byte_array[i / 8] = (uint8_t) strtol(binary + i, NULL, 2);
    }
}

int main() {
    const char *binary_plaintext = "000000010000001000000100"; 
    const char *binary_key = "0111111101"; 
    const char *binary_counter = "00000000"; 
    uint8_t plaintext[24];
    uint8_t key[8];
    uint8_t initial_counter[8];
    uint8_t ciphertext[24];
    uint8_t decrypted[24];

    binary_to_byte_array(binary_plaintext, plaintext);
    binary_to_byte_array(binary_key, key);
    binary_to_byte_array(binary_counter, initial_counter);

    int len = sizeof(plaintext);

    ctr_encrypt(plaintext, key, initial_counter, ciphertext, len);
    print_hex("CTR Encrypted", ciphertext, len);

    ctr_decrypt(ciphertext, key, initial_counter, decrypted, len);
    print_hex("CTR Decrypted", decrypted, len);

    return 0;
}

