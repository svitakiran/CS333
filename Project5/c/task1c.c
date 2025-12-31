/**
 * Writing a program that can handle a segmentation
 * fault error
 * 
 * Svita Kiran
 * 11/13/2025
 * CS333
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig) {
    printf("segmentation fault");
    exit(0);
}

int main(int argc, char const *argv[])
{
    signal(SIGSEGV, handler);
    int *p = NULL;
    *p = 10;
    return 0;
}
