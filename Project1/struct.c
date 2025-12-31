/**
 * A struct that has 3-4 different variables
 *
 * Svita Kiran
 * 9/18/2025
*/

#include <stdio.h>
#include <stdlib.h>
        
/* A struct that has 3-4 different variables
*/ 

struct struct1 {
    char a;
    short b;
    char c;
};

int main (int arg, char *argv[]) {

  struct struct1 *s = malloc(sizeof(struct struct1));
  s->a = 'A';
  s->b = 0x1234;
  s->c = 'Z';

  printf("Size of struct: %lu bytes\n\n", sizeof(struct struct1));

  unsigned char *ptr = (unsigned char *)s;
  for (int i = 0; i < sizeof(struct struct1); i++) {
    printf("Byte %2d: %02X\n", i, ptr[i]);
  }
  
  free(s);
  return 0;
}