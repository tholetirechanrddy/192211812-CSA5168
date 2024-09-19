#include <stdio.h>
#include <stdint.h>
#include <string.h>

void simple_des_encrypt(uint8_t *block, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < 8; i++) {
        output[i] = block[i] ^ key[i]; 
    }
}

void simple_des_decrypt(uint8_t *block, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < 8; i++) {
        output[i] = block[i] ^ key[i]; 
    }
}

void ecb_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext, int len) {
    uint8_t block[8];
    for (int i = 0; i < len; i += 8) {
        simple_des_encrypt(&plaintext[i], key, &ciphertext[i]);
    }
}

void ecb_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext, int len) {
    uint8_t block[8];
    for (int i = 0; i < len; i += 8) {
        simple_des_decrypt(&ciphertext[i], key, &plaintext[i]);
    }
}

void xor_block(uint8_t *input, uint8_t *prev_cipher, uint8_t *output, int block_size) {
    for (int i = 0; i < block_size; i++) {
        output[i] = input[i] ^ prev_cipher[i];
    }
}

void cbc_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, int len) {
    uint8_t block[8], cipher_block[8];
    memcpy(cipher_block, iv, 8);

    for (int i = 0; i < len; i += 8) {
        xor_block(&plaintext[i], cipher_block, block, 8);
        simple_des_encrypt(block, key, cipher_block);
        memcpy(&ciphertext[i], cipher_block, 8);
    }
}

void cbc_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *iv, uint8_t *plaintext, int len) {
    uint8_t block[8], prev_cipher[8];
    memcpy(prev_cipher, iv, 8); 

    for (int i = 0; i < len; i += 8) {
        simple_des_decrypt(&ciphertext[i], key, block);
        xor_block(block, prev_cipher, &plaintext[i], 8);
        memcpy(prev_cipher, &ciphertext[i], 8);
    }
}

void cfb_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, int len) {
    uint8_t block[8], keystream[8];
    memcpy(keystream, iv, 8); 

    for (int i = 0; i < len; i += 8) {
        simple_des_encrypt(keystream, key, block);
        xor_block(&plaintext[i], block, &ciphertext[i], 8);
        memcpy(keystream, &ciphertext[i], 8);
    }
}

void cfb_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *iv, uint8_t *plaintext, int len) {
    uint8_t block[8], keystream[8];
    memcpy(keystream, iv, 8); 

    for (int i = 0; i < len; i += 8) {
        simple_des_encrypt(keystream, key, block);
        xor_block(&ciphertext[i], block, &plaintext[i], 8);
        memcpy(keystream, &ciphertext[i], 8);
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
    uint8_t plaintext[] = "This is a test message.";
    uint8_t key[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    uint8_t iv[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 

    int len = strlen((char *)plaintext);
    pad(plaintext, &len); 

    uint8_t ciphertext[len];
    uint8_t decrypted[len];

    ecb_encrypt(plaintext, key, ciphertext, len);
    print_hex("ECB Encrypted", ciphertext, len);
    ecb_decrypt(ciphertext, key, decrypted, len);
    printf("ECB Decrypted: %s\n", decrypted);

    memcpy(plaintext, "This is a test message.", len); 
    pad(plaintext, &len); 
    uint8_t cbc_ciphertext[len];
    uint8_t cbc_decrypted[len];

    cbc_encrypt(plaintext, key, iv, cbc_ciphertext, len);
    print_hex("CBC Encrypted", cbc_ciphertext, len);
    cbc_decrypt(cbc_ciphertext, key, iv, cbc_decrypted, len);
    printf("CBC Decrypted: %s\n", cbc_decrypted);

    memcpy(plaintext, "This is a test message.", len); 
    pad(plaintext, &len); // Ensure padding
    uint8_t cfb_ciphertext[len];
    uint8_t cfb_decrypted[len];

    cfb_encrypt(plaintext, key, iv, cfb_ciphertext, len);
    print_hex("CFB Encrypted", cfb_ciphertext, len);
    cfb_decrypt(cfb_ciphertext, key, iv, cfb_decrypted, len);
    printf("CFB Decrypted: %s\n", cfb_decrypted);

    return 0;
}

