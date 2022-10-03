#include <stdio.h>
#include <stdlib.h>

// 오름차순 비교 함수 구현
int compare(const void *a, const void *b) {

    // void 포인터를 int 포인터로 변환한 뒤 역참조하여 값을 가져옴
    int n1 = *(int *)a;
    int n2 = *(int *)b;

    if (n1 < n2) {
        return -1;
    }

    if (n1 > n2) {
        return 1;
    }

    return 0;
}

int main() {
    int numArr[10] = { 8, 4, 2, 5, 3, 7, 10, 1, 6, 9 }; 

    qsort(numArr, sizeof(numArr)/sizeof(int), sizeof(int), compare);

    for (int i = 0; i < 10; i++) {
        printf("%d", numArr[i]);
    }

    printf("\n");

    return 0;
}