/**
 * A program that allows you to see where values are on the stack.
 *
 * Svita Kiran
 * 9/18/2025
*/

#include <stdio.h>
#include <stdlib.h>
        
/* A program that allows you to see where values are on the stack.
*/ 
int main (int arg, char *argv[]) {
					
  int a = 0x11111111;
  int b = 0x22222222;
  char c = 'C';
  double d = 100;	

  unsigned char *ptr;
  ptr = (unsigned char *)&ptr;
  for(int i = 0; i < 100; i++) {
    printf("Byte %d: %02X\n", i, ptr[i]);
  }
					
  return 0;
}  