#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) (((x) < (y)) ? -1: ((x) == (y)) ? 0 : 1)

// int compare(int x, int y) {
//     if (x < y)
//         return -1;
//     else if (x == y) 
//         return 0;
//     else
//         return 1;
// }

int binsearch(int list[], int searchNum, int left, int right) {
    int middle;
    if (left <= right) {
        middle = (left + right) / 2;
        switch (COMPARE(list[middle], searchNum)) {
            case -1: 
                return binsearch(list, searchNum, middle+1, right);
            case 0:
                return middle;
            case 1:
                return binsearch(list, searchNum, left, middle-1);
        }
    }
    return -1;
}

int main() {
    int inputNum;
    int searchNum;
    int arr[100];
    int max = arr[0];
    int min = arr[0];

    printf("입력 개수 : ");
    scanf("%d", &inputNum);

    printf("데이터 입력\n");
    for (int i = 0; i < inputNum; i++) {
        scanf("%d", &arr[i]);
    }

    int dataSize = sizeof(arr) / sizeof(int);

    printf("\n");
    printf("입력받은 데이터 : ");
    for (int i = 0; i < inputNum; i++) {
        printf("%d ", arr[i]);
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i]; 
    }

    printf("max: %d\n", max);
    printf("min: %d\n", min);

    printf("\n");
    printf("찾을 숫자를 입력하세요: ");
    scanf("%d", &searchNum);

    // printf("FLAG1");
    // binsearch(arr, searchNum, arr[0], arr[inputNum-1]);

    int answer = binsearch(arr, searchNum, min, max);
    // printf("FLAG2");
    printf("%d번째 인덱스, 값: %d\n", answer+1, arr[answer]);
    
}