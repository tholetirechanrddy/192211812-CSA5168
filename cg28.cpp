#include <stdio.h>

unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    unsigned long long a = 5;  
    unsigned long long q = 23;
    unsigned long long secret_alice = 6; 
    unsigned long long secret_bob = 15;  
    unsigned long long alice_public = mod_exp(a, secret_alice, q);
    unsigned long long bob_public = mod_exp(a, secret_bob, q);
    unsigned long long alice_shared_secret = mod_exp(bob_public, secret_alice, q);

    unsigned long long bob_shared_secret = mod_exp(alice_public, secret_bob, q);

    printf("Alice's public value (to send to Bob): %llu\n", alice_public);
    printf("Bob's public value (to send to Alice): %llu\n", bob_public);
    printf("Shared secret calculated by Alice: %llu\n", alice_shared_secret);
    printf("Shared secret calculated by Bob: %llu\n", bob_shared_secret);

    if (alice_shared_secret == bob_shared_secret) {
        printf("Key exchange successful! Shared secret: %llu\n", alice_shared_secret);
    } else {
        printf("Key exchange failed. Shared secrets do not match.\n");
    }

    return 0;
}

