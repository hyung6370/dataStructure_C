#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x, y, t)((t)=(x), (x)=(y), (y)=(t))


void perm (int *list, int i, int n) {
    int temp;
    if (i == n) {
        for (int j = 0; j <= n; j++) {
            printf("%d", list[j]);
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

void input() {
    int num;
    printf("입력 : ");
    scanf("%d", &num);
    int data[num+1];

    if (num < 1 || num > 32) {
        fprintf(stderr, "입력 범위(1~32)를 벗어났습니다.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i <= num-1; i++) {
        data[i] = i+1;
    }

    perm(data, 0, num-1);
    
}

int main() {
    clock_t start = clock();

    input();
    clock_t end = clock();
    printf("\n");
    printf("clock : %.3lf(sec)", ((double)(end-start)) / CLOCKS_PER_SEC);
    return 0;
}