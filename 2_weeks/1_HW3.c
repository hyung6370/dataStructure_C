#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 100001
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define _CRT_SECURE_NO_WARNINGS

void sort(int[], int);  // selection sort
int is_sorted(int A[], int n);
int binsearch(int list[], int searchNum, int left, int right);

int main() {
    int i, n;
    int searchNum;
    int list[MAX_SIZE];

    printf("Enter the number of numbers to generate: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_SIZE) {
        fprintf(stderr, "Improper value of n\n");
        exit(EXIT_FAILURE);
    }

    // randomly generate numbers
    for (i = 0; i < n; i++) {
        list[i] = rand() % 50002;
        printf("%d  ", list[i]);
    }

    sort(list, n);
    is_sorted(list, n);

    printf("\n Sorted array:\n ");
    for (i = 0; i < n; i++) {
        printf("%d  ", list[i]);
    }

    printf("\n\n");
    printf("Input Search Number(1 ~ 100000): ");
    printf("\n");
    scanf("%d", &searchNum);

    binsearch(list, searchNum, 0, n-1);
    
}

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

int is_sorted(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (A[i] <= A[i+1]) {
            printf("\n\n");
            printf("정렬 완료");
            printf("\n");
            return 1;
        }
        else {
            printf("\n\n");
            printf("정렬 실패");
            printf("\n");
            return 0;
        }
    }
}

int binsearch(int list[], int searchNum, int left, int right) {
    int counter = 0;
    int middle;

    while (1) {
        middle = (left + right) / 2;
        printf("left : %d, right : %d, middle : %d\n", left, right, middle);
        printf("counter: %d\n", counter);

        if (left < right) {
            if (list[middle] < searchNum) {
                left = middle + 1;
                printf("\n");
                counter++;
            }
            else if (list[middle] > searchNum) {
                printf("\n");
                right = middle - 1;
                counter++;
            }
            else {
                printf("\n");
                printf("이진 탐색 완료!\n");
                printf("찾고자 하는 %d은(는) %d번만에 list[%d]에서 탐색되었습니다.", searchNum, counter+1, middle);
                counter++;
                break;
            }
        }
        else {
            if (list[middle] != searchNum) {
                printf("이진 탐색 완료!\n");
                printf("찾고자 하는 %d은(는) list에 존재하지 않습니다.", searchNum);
            }
            else {
                printf("이진 탐색 완료!\n");
                printf("찾고자 하는 %d은(는) %d번만에 list[%d]에서 탐색되었습니다.", searchNum, counter+1, middle);
            }
            break;
        }
        
    }
    

    return 0;
}