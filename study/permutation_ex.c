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
    char list[10] = "12345";
    perm(list, 0, 4);
}