/**
 * A program that repeatedly allocates a small amount of memory in
 * a loop that goes on for a long time.
 * Svita Kiran
 * 9/18/2025
*/

#include <stdio.h>
#include <stdlib.h>
        
/* A program that repeatedly allocates a small amount of memory in 
a loop that goes on for a long time
*/ 
int main (int arg, char *argv[]) {
					
  char *leak;
  int i = 0;

  while (1) {
    leak = (char *)malloc(1024);
    if (leak == NULL) {
        fprintf(stderr, "Memory allocation failed at iteration %d\n", i);
        break;
    }

    leak[0] = 'B';

    printf("Allocated and freed 1KB: iteration %d\n", i++);
    free(leak);

  }
  return 0;
}  