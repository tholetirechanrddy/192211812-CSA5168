#include <stdio.h>
#include <stdlib.h>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

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

void generate_keys(unsigned long long p, unsigned long long q, unsigned long long* e, unsigned long long* d, unsigned long long* n) {
    *n = p * q; 
    unsigned long long phi = (p - 1) * (q - 1); 
    *e = 65537; 
    while (gcd(*e, phi) != 1) {
        (*e)++;
    }

    *d = 1;
    while ((*d * *e) % phi != 1) {
        (*d)++;
    }
}

unsigned long long encrypt(unsigned long long message, unsigned long long e, unsigned long long n) {
    return mod_exp(message, e, n);
}

unsigned long long decrypt(unsigned long long ciphertext, unsigned long long d, unsigned long long n) {
    return mod_exp(ciphertext, d, n);
}

int main() {
    unsigned long long p = 61;
    unsigned long long q = 53;

    unsigned long long e, d, n;
    generate_keys(p, q, &e, &d, &n);

    printf("Public Key: (e = %llu, n = %llu)\n", e, n);
    printf("Private Key: (d = %llu, n = %llu)\n", d, n);

    unsigned long long message = 65;
    printf("Original message: %llu\n", message);

    unsigned long long ciphertext = encrypt(message, e, n);
    printf("Encrypted message: %llu\n", ciphertext);

    unsigned long long decrypted_message = decrypt(ciphertext, d, n);
    printf("Decrypted message: %llu\n", decrypted_message);
    unsigned long long new_e, new_d;
    generate_keys(p, q, &new_e, &new_d, &n);

    printf("\nNew Public Key: (e = %llu, n = %llu)\n", new_e, n);
    printf("New Private Key: (d = %llu, n = %llu)\n", new_d, n);

    return 0;
}

