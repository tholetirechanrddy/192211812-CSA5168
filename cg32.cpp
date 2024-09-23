#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define MESSAGE_SIZE 32  
#define K_SIZE 32       

void rand_bytes(uint8_t *buf, size_t len);
void dsa_sign(const uint8_t *message, uint8_t *signature1, uint8_t *signature2);
void rsa_sign(const uint8_t *message, uint8_t *signature);

void rand_bytes(uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; i++) {
        buf[i] = rand() % 256;
    }
}

void dsa_sign(const uint8_t *message, uint8_t *signature1, uint8_t *signature2) {
    uint8_t k1[K_SIZE], k2[K_SIZE];
    uint8_t r1 = 0, r2 = 0, s1 = 0, s2 = 0;

    rand_bytes(k1, K_SIZE);
    rand_bytes(k2, K_SIZE);

    r1 = (k1[0] % 10);
    r2 = (k2[0] % 10); 
    s1 = (k1[0] + r1) % 10;
    s2 = (k2[0] + r2) % 10; 

    signature1[0] = r1;
    signature1[1] = s1;
    signature2[0] = r2;
    signature2[1] = s2;
}

void rsa_sign(const uint8_t *message, uint8_t *signature) {
    signature[0] = (message[0] % 10); 
}

int main() {
    srand(time(NULL));

    uint8_t message[MESSAGE_SIZE] = {0x01}; 
    uint8_t dsa_signature1[2], dsa_signature2[2];
    uint8_t rsa_signature[2];

    dsa_sign(message, dsa_signature1, dsa_signature2);
    rsa_sign(message, rsa_signature);

    printf("DSA Signature 1: r = %d, s = %d\n", dsa_signature1[0], dsa_signature1[1]);
    printf("DSA Signature 2: r = %d, s = %d\n", dsa_signature2[0], dsa_signature2[1]);
    printf("RSA Signature: %d\n", rsa_signature[0]);

    return 0;
}

