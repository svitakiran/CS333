/**
 * Writing a program that can respond to an interrupt
 * (ctrl + C).
 * 
 * Svita Kiran
 * 11/13/2025
 * CS333
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig) {
    printf("Interrupted!");
    exit(0);

}

int main(int argc, char const *argv[])
{
    signal(SIGINT, handler);
    while (1)
    {
        // loop
    }
    
    return 0;
}
