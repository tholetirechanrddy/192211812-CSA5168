#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STATE_SIZE 25  
#define RATE_LANES 16  
#define CAPACITY_LANES 9 

int are_all_capacity_nonzero(unsigned long long capacity[CAPACITY_LANES]) {
    for (int i = 0; i < CAPACITY_LANES; i++) {
        if (capacity[i] == 0) {
            return 0; 
        }
    }
    return 1; 
}

int main() {
    srand(time(NULL));

    unsigned long long state[STATE_SIZE] = {0};

    unsigned long long capacity[CAPACITY_LANES] = {0}; 

    int block_count = 0;

    while (!are_all_capacity_nonzero(capacity)) {
        block_count++;

        for (int i = 0; i < RATE_LANES; i++) {
            unsigned long long message_block_lane = ((unsigned long long)rand() << 1) | 1; 

            state[i] ^= message_block_lane;
        }

        for (int i = 0; i < CAPACITY_LANES; i++) {
            capacity[i] ^= state[RATE_LANES + i]; 
        }

        printf("After block %d, capacity lanes:\n", block_count);
        for (int i = 0; i < CAPACITY_LANES; i++) {
            printf("Lane %d: %llx\n", i, capacity[i]);
        }
    }

    printf("All capacity lanes have at least one non-zero bit after %d message blocks.\n", block_count);

    return 0;
}

