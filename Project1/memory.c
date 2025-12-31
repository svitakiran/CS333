/**
 * A program that declares a variable of each of the basic types 
 * and assigns each one a value.
 * Svita Kiran
 * 9/18/2025 
*/

#include <stdio.h>
#include <stdlib.h>
        
/* A program that declares a variable of each of the basic types 
and assigns each one a value.
*/ 
int main (int arg, char *argv[]) {
					
  char c = 'A';
  short s = 0x1234;
  int i = 0x12345678;
  long l = 0x12345678ABCDEF00;
  float f = 123.456f;
  double d = 123.456789;

  unsigned char *ptr;
  int j;

  #define PRINT_MEMORY(var, type) \
    ptr = (unsigned char *)&(var); \
    printf(#type " (%lu bytes):\n", sizeof(type)); \
    for (j = 0; j < sizeof(type); j++) { \
      printf("  byte %d: %02X\n", j, ptr[j]); \
    } \
    printf("\n");

  PRINT_MEMORY(c, char);
  PRINT_MEMORY(s, short);
  PRINT_MEMORY(i, int);
  PRINT_MEMORY(l, long);
  PRINT_MEMORY(f, float);
  PRINT_MEMORY(d, double);

  return 0;
}  