#include <stdio.h>

int factorial(int n);

int main() {
    int (*pf)(int);
    pf = factorial;
    printf("%d", pf(3));
}

int factorial (int n) {
    if (n <= 1) {
        return 1;
    }
    else {
        return n * factorial(n-1);
    }
}