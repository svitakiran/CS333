/**
 * Estimating the time cost of memory management in C
 * 
 * Svita Kiran
 * 11/13/2025
 * CS333
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    const int iterations = 10000;
    size_t sizes[] = {100 * sizeof(int), 10000 * sizeof(int), 1000000 * sizeof(int)};
    int num_sizes = 3;

    for (int s = 0; s < num_sizes; s++) {
        size_t size = sizes[s];

        void *temp = malloc(size);
        free(temp);

        clock_t start = clock();
        for (int i = 0; i < iterations; i++) {
            void *p = malloc(size);
            free(p);
        }
        clock_t end = clock();

        double total_time = (double)(end - start) / CLOCKS_PER_SEC;
        double avg_time = total_time / iterations * 1e6;

        printf("size: %zu bytes, average time: %.2f microseconds\n", size, avg_time);
    }

    return 0;
}