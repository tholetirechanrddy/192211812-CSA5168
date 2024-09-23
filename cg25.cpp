#include <stdio.h>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    unsigned long long n, e, plaintext_block;
    
    printf("Enter the modulus n: ");
    scanf("%llu", &n);

    printf("Enter the public key exponent e: ");
    scanf("%llu", &e);

    printf("Enter the plaintext block: ");
    scanf("%llu", &plaintext_block);

    unsigned long long factor = gcd(plaintext_block, n);

    if (factor > 1 && factor < n) {
        printf("Found a factor of n: %llu\n", factor);
        
        unsigned long long other_factor = n / factor;
        printf("The other factor of n is: %llu\n", other_factor);
    } else {
        printf("No non-trivial factor found.\n");
    }

    return 0;
}

