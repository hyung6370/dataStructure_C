#include <stdio.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

void perm (char *list, int i, int n) {
    int temp;
    if (i == n) {
        for (int j = 0; j <= n; j++) {
            printf("%c", list[j]);
        }
        printf("   ");
    }
    else {
        for (int j = i; j <= n; j++) {
            SWAP(list[i], list[j], temp);
            perm(list, i+1, n);
            SWAP(list[i], list[j], temp);
        }
    }
}

int main(void) {
    // CASE_1
    char list[10] = "GO";
    perm(list, 0, 1);

    // CASE_2
    // char list[10] = "BOY";
    // perm(list, 0, 2);

    // CASE_3
    // char list[10] = "GIRL";
    // perm(list, 0, 3);

    // CASE_4
    // char list[10] = "GIRLS";
    // perm(list, 0, 4);
}