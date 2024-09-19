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

void cbc_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, int len) {
    uint8_t block[8], cipher_block[8];
    memcpy(cipher_block, iv, 8); 
    for (int i = 0; i < len; i += 8) {
        for (int j = 0; j < 8; j++) {
            block[j] = plaintext[i + j] ^ cipher_block[j];
        }
        s_des_encrypt(block, key, cipher_block);
        memcpy(&ciphertext[i], cipher_block, 8);
    }
}

void cbc_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *iv, uint8_t *plaintext, int len) {
    uint8_t block[8], prev_cipher[8];
    memcpy(prev_cipher, iv, 8); 

    for (int i = 0; i < len; i += 8) {
        s_des_decrypt(&ciphertext[i], key, block);
        for (int j = 0; j < 8; j++) {
            plaintext[i + j] = block[j] ^ prev_cipher[j];
        }
        memcpy(prev_cipher, &ciphertext[i], 8);
    }
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
    const char *binary_plaintext = "0000000100100011"; 
    const char *binary_key = "01111111"; 
    const char *binary_iv = "10101010"; 

    uint8_t plaintext[16];
    uint8_t key[8];
    uint8_t iv[8];
    uint8_t ciphertext[16];
    uint8_t decrypted[16];

    binary_to_byte_array(binary_plaintext, plaintext);
    binary_to_byte_array(binary_key, key);
    binary_to_byte_array(binary_iv, iv);

    int len = sizeof(plaintext);

    cbc_encrypt(plaintext, key, iv, ciphertext, len);
    print_hex("CBC Encrypted", ciphertext, len);

    cbc_decrypt(ciphertext, key, iv, decrypted, len);
    print_hex("CBC Decrypted", decrypted, len);

    return 0;
}

