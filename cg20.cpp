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

void print_hex(const char *label, uint8_t *data, int len) {
    printf("%s: ", label);
    for (int i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    uint8_t plaintext[] = "This is a message to encrypt with ECB.";
    uint8_t key[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF}; 

    int len = ((strlen((char *)plaintext) + 7) / 8) * 8;
    uint8_t padded_plaintext[len];
    memcpy(padded_plaintext, plaintext, strlen((char *)plaintext));
    memset(&padded_plaintext[strlen((char *)plaintext)], 0, len - strlen((char *)plaintext)); 

    uint8_t ciphertext[len];

    ecb_encrypt(padded_plaintext, key, ciphertext, len);

    print_hex("Encrypted", ciphertext, len);

    uint8_t decrypted[len];

    ecb_decrypt(ciphertext, key, decrypted, len);

    printf("Decrypted: %s\n", decrypted);

    return 0;
}

