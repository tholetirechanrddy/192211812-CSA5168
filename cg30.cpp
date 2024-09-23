#include <stdio.h>
#include <string.h>
#include <stdint.h>

void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *out, int len) {
    for (int i = 0; i < len; i++) {
        out[i] = block1[i] ^ block2[i];
    }
}

void cbc_mac(uint8_t *key, uint8_t *message, uint8_t *mac, int block_size) {
    for (int i = 0; i < block_size; i++) {
        mac[i] = message[i] ^ key[i];  
    }
}

int main() {
    uint8_t key[16] = {0x00};          
    uint8_t message[16] = {0x01};     
    uint8_t mac[16];                   
    uint8_t x_xor_t[16];              
    uint8_t new_mac[16];               

    cbc_mac(key, message, mac, 16);    

    xor_blocks(message, mac, x_xor_t, 16);  

    cbc_mac(mac, x_xor_t, new_mac, 16);  

    printf("Original MAC: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", mac[i]);
    }
    printf("\nMAC for X || (X ? T): ");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", new_mac[i]);
    }
    printf("\n");

    return 0;
}

