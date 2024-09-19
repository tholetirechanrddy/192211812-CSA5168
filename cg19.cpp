#include <stdio.h>
#include <stdint.h>
#include <string.h>

void xor_block(uint8_t *input, uint8_t *prev_cipher, uint8_t *output, int block_size) {
    for (int i = 0; i < block_size; i++) {
        output[i] = input[i] ^ prev_cipher[i];
    }
}

void simple_des_encrypt(uint8_t *block, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < 8; i++) {
        output[i] = block[i] ^ key[i];
    }
}

void triple_des_encrypt(uint8_t *block, uint8_t *key1, uint8_t *key2, uint8_t *key3, uint8_t *output) {
    uint8_t temp[8];

    simple_des_encrypt(block, key1, temp);

    simple_des_encrypt(temp, key2, temp);

    simple_des_encrypt(temp, key3, output);
}

void triple_des_cbc_encrypt(uint8_t *plaintext, uint8_t *key1, uint8_t *key2, uint8_t *key3, uint8_t *iv, uint8_t *ciphertext, int len) {
    uint8_t block[8], cipher_block[8];
    int i;

    memcpy(cipher_block, iv, 8);

    for (i = 0; i < len; i += 8) {
        xor_block(&plaintext[i], cipher_block, block, 8);

        triple_des_encrypt(block, key1, key2, key3, cipher_block);

        memcpy(&ciphertext[i], cipher_block, 8);
    }
}
void pad(uint8_t *data, int *len) {
    int pad_len = 8 - (*len % 8);
    for (int i = 0; i < pad_len; i++) {
        data[*len + i] = pad_len;
    }
    *len += pad_len;
}
void print_hex(const char *label, uint8_t *data, int len) {
    printf("%s: ", label);
    for (int i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    uint8_t plaintext[] = "This is a test message for 3DES CBC mode.";
    uint8_t key1[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF}; 
    uint8_t key2[] = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10}; 
    uint8_t key3[] = {0x89, 0x67, 0x45, 0x23, 0x01, 0x12, 0x34, 0x56}; 
    uint8_t iv[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 

    int len = strlen((char *)plaintext);
    pad(plaintext, &len);

    uint8_t ciphertext[64];

    triple_des_cbc_encrypt(plaintext, key1, key2, key3, iv, ciphertext, len);

    print_hex("Encrypted", ciphertext, len);

    return 0;
}

