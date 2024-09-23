#include <stdio.h>

unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}
unsigned long long encrypt(unsigned long long plaintext, unsigned long long e, unsigned long long n) {
    return mod_exp(plaintext, e, n);
}
void brute_force_attack(unsigned long long ciphertext, unsigned long long e, unsigned long long n) {
    printf("Attempting brute force attack...\n");
    for (int plaintext = 0; plaintext <= 25; plaintext++) {
        unsigned long long encrypted_value = encrypt(plaintext, e, n);
        if (encrypted_value == ciphertext) {
            printf("Found the plaintext! Ciphertext %llu corresponds to plaintext %d ('%c')\n", ciphertext, plaintext, plaintext + 'A');
            return;
        }
    }
    printf("No matching plaintext found.\n");
}

int main() {
    unsigned long long n = 3233; 
    unsigned long long e = 17;   
    unsigned long long ciphertext = 2790; 
    brute_force_attack(ciphertext, e, n);

    return 0;
}

