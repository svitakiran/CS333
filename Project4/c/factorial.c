/* This function should take in an integer argument and then return its factorial value
as and integer as well. 

Svita Kiran
10/30/2025
*/

#include <stdio.h>
#include <stdlib.h>

int (*calc)(const int);

int factorial(const int num) {
    if (num < 0) {
        return -1;
    }
    else {
        int n = 1;
        for (int i = 1; i <= num; i++) {
            n *= i;
        }
        
        return n;
    }
    
}

int main(int argc, char *argv[]) {
    calc = &factorial;
    // int ans = calc(5);
    int N = atoi(argv[1]);
    int ans = calc(N);
    printf("factorial: %d\n",ans);
    return 0;
}