#include <stdio.h>
#include <stdlib.h>
 
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}
 
unsigned long long unique_playfair_keys() {
    unsigned long long total_permutations = factorial(25);  
    unsigned long long row_permutations = factorial(5);  
    unsigned long long col_permutations = factorial(5);  
     
    unsigned long long unique_keys = total_permutations / (row_permutations * col_permutations);
    return unique_keys;
}

int power_of_2(unsigned long long num) {
    int power = 0;
    while (num > 1) {
        num /= 2;
        power++;
    }
    return power;
}

int main() {
    unsigned long long unique_keys = unique_playfair_keys();
    int power = power_of_2(unique_keys);

    printf("Approximate number of possible keys (as a power of 2): %d\n", power);
    
    return 0;
}

