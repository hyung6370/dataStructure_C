#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 1601
#define ITERATIONS 42
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

void sort(int list[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n-1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[min])
                min = j;
        SWAP(list[i], list[min], temp);
    }
}

int main(void) {
    int position;
    int list[MAX_SIZE];
    int sizelist[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400,
    500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600
    ,1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800,
    2900, 3000};

    clock_t start, stop;
    double duration;
    printf("    n   time\n");

    for (int i = 0; i < ITERATIONS; i++) {
        for (int j = 0; j < sizelist[i]; j++)
            list[j] = sizelist[i]-j;

        start = clock();    // 시작 시간 측정
        sort(list, sizelist[i]);    // sort 함수 호출
        stop = clock();     // 종료 시간 측정
        // CLOCKS_PER_SEC = 초당 클럭의 수, Macro: 1000
        duration = ((double)(stop-start)) / CLOCKS_PER_SEC;
        printf("%6d  %.2f\n", sizelist[i], duration);
    }
}