#include <stdio.h>
#include <stdlib.h>
int extended_gcd(int a, int b, int *x, int *y);
int mod_inverse(int e, int phi);
int is_prime(int num);
void find_factors(int n, int *p, int *q);

int main() {
    int e = 31;
    int n = 3599;
    int p, q;

    find_factors(n, &p, &q);

    printf("p = %d, q = %d\n", p, q);
    int phi = (p - 1) * (q - 1);
    printf("phi(n) = %d\n", phi);
    int d = mod_inverse(e, phi);
    printf("Private key d = %d\n", d);

    return 0;
}
int extended_gcd(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = extended_gcd(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

int mod_inverse(int e, int phi) {
    int x, y;
    int gcd = extended_gcd(e, phi, &x, &y);
    if (gcd != 1) {
        printf("Inverse does not exist\n");
        exit(1);
    }
    return (x % phi + phi) % phi; 
}

void find_factors(int n, int *p, int *q) {
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            int j = n / i;
            if (is_prime(i) && is_prime(j)) {
                *p = i;
                *q = j;
                return;
            }
        }
    }
    printf("No factors found\n");
    exit(1);
}
int is_prime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return 0;
    }
    return 1;
}

