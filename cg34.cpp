#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8  
#define KEY_SIZE 8    

void mock_encrypt_block(unsigned char *input, unsigned char *output, unsigned char *key) {
 
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i];  
    }
}

void mock_decrypt_block(unsigned char *input, unsigned char *output, unsigned char *key) { 
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i]; 
    }
}
 
void pad_data(unsigned char *input, int input_len, unsigned char *output, int total_len) {
    memcpy(output, input, input_len);
    output[input_len] = 0x80;  
    for (int i = input_len + 1; i < total_len; i++) {
        output[i] = 0x00;  
    }
}
 
void ecb_mode(unsigned char *input, unsigned char *output, int len, unsigned char *key) {
    unsigned char block[BLOCK_SIZE];
    unsigned char enc_block[BLOCK_SIZE];

    for (int i = 0; i < len; i += BLOCK_SIZE) {
        memcpy(block, input + i, BLOCK_SIZE);
        mock_encrypt_block(block, enc_block, key);
        memcpy(output + i, enc_block, BLOCK_SIZE);
    }
}
 
void cbc_mode(unsigned char *input, unsigned char *output, int len, unsigned char *key, unsigned char *iv) {
    unsigned char block[BLOCK_SIZE];
    unsigned char enc_block[BLOCK_SIZE];
    unsigned char xor_block[BLOCK_SIZE];

    memcpy(xor_block, iv, BLOCK_SIZE);  

    for (int i = 0; i < len; i += BLOCK_SIZE) { 
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] = input[i + j] ^ xor_block[j];
        }

        mock_encrypt_block(block, enc_block, key);
        memcpy(output + i, enc_block, BLOCK_SIZE);
        memcpy(xor_block, enc_block, BLOCK_SIZE); 
    }
}
 
void cfb_mode(unsigned char *input, unsigned char *output, int len, unsigned char *key, unsigned char *iv) {
    unsigned char enc_block[BLOCK_SIZE];
    unsigned char shift_reg[BLOCK_SIZE];

    memcpy(shift_reg, iv, BLOCK_SIZE);  

    for (int i = 0; i < len; i += BLOCK_SIZE) {
        mock_encrypt_block(shift_reg, enc_block, key);
 
        for (int j = 0; j < BLOCK_SIZE; j++) {
            output[i + j] = input[i + j] ^ enc_block[j];
        } 
        memcpy(shift_reg, output + i, BLOCK_SIZE);
    }
}
 
void print_hex(unsigned char *data, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

int main() {
    unsigned char key[KEY_SIZE] = {0x1f, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f, 0x7a, 0x8b};
    unsigned char iv[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    unsigned char plaintext[16] = "HELLO_WORLD_16";  
    int padded_len = ((sizeof(plaintext) / BLOCK_SIZE) + 1) * BLOCK_SIZE;
    unsigned char padded_plaintext[padded_len];
    unsigned char ciphertext[padded_len];
    unsigned char decryptedtext[padded_len];
 
    pad_data(plaintext, sizeof(plaintext), padded_plaintext, padded_len);
 
    printf("ECB Mode Encryption:\n");
    ecb_mode(padded_plaintext, ciphertext, padded_len, key);
    print_hex(ciphertext, padded_len);
 
    printf("CBC Mode Encryption:\n");
    cbc_mode(padded_plaintext, ciphertext, padded_len, key, iv);
    print_hex(ciphertext, padded_len);
 
    printf("CFB Mode Encryption:\n");
    cfb_mode(padded_plaintext, ciphertext, padded_len, key, iv);
    print_hex(ciphertext, padded_len);

    return 0;
}

