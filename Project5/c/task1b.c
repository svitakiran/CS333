/**
 * Writing a program that can handle a floating point
 * exception
 * 
 * Svita Kiran
 * 11/13/2025
 * CS333
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig) {
    printf("floating point exception");
    exit(0);
}

int main(int argc, char const *argv[])
{
    signal(SIGFPE, handler);
    int x = 1;
    int y = 0;
    int z = x / y;
    return 0;
}
