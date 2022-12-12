#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))
#define _CRT_SECURE_NO_WARNINGS

// 선택 정렬
void sort(int list[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n-1; i++) {
        min = i;
        for (j = i+1; j < n; j++)
            if (list[j < list[min]])
                min = j;
        SWAP(list[i], list[min], temp);
    }
}

// 삽입 정렬
void insertion_sort(int list[], int n) {
    int i, j;
    int next;
    for (i = 1; i < n; i++) {
        next = list[i];
        for (j = i-1; j >= 0 && next < list[j]; j--)
            list[j+1] = list[j];
        list[j+1] = next;
    }
}

// 퀵 정렬
void quick_sort(int list[], int left, int right) {
    int pivot, i, j;
    int temp;
    if (left < right) {
        i = left;
        j = right+1;
        pivot = list[left];

        do {
            do
                i++;
            while (list[i] < pivot);
            do
                j--;
            while (list[j] > pivot);
            if (i < j)
                SWAP(list[i], list[j], temp);
        } while (i < j);
        SWAP(list[left], list[j], temp);
        quick_sort(list, left, j-1);
        quick_sort(list, j+1, right);
    }
}

// 배열 랜덤으로 생성
int* array_random(int* list, int num) {
    list = (int*)malloc(sizeof(int) * num);

    for (int i = 0; i < num; i++) {
        list[i] = rand() / (0x7fff * 1.0);
        list[i] = list[i] * 100000000;
    }
    return list;
}

// 삽입 정렬 제대로 정렬 되었는지 확인해주는 함수
int sorted_check(int list[], int num) {
    for (int i = 0; i < num-1; i++) {
        if (list[i] > list[i+1]) {
            return 0;
        }
    }
    return 1;
}

// 배열 오름차순으로 생성
int* array_ascend(int* list, int num) {
    list = (int*)malloc(sizeof(int) * num);

    for (int i = 0; i < num; i++)
        list[i] = i + 1;
    
    return list;
}

// 배열 내림차순으로 생성
int* array_deascend(int* list, int num) {
    list = (int*)malloc(sizeof(int) * num);
    
    for (int i = 0; i < num; i++)
        list[i] = num - i;
    
    return list;
}

// 메인 함수
int main() {
    int menuChoice;
    clock_t start, end;
    int num;
    double selection_time;
    double insertion_time;
    double quick_time;

    while (1) {
        printf("\n");
        printf("(선택) 1. 랜덤 생성 데이터의 정렬, 2. 오름차순 데이터 정렬, 3. 내림차순 데이터 정렬, -1. 종료 : ");
        scanf("%d", &menuChoice);
        if (menuChoice == -1) {
            printf("종료합니다\n");
            break;
        }
        int* A = NULL;
        
        if (menuChoice == 1) {
            printf("\n");
            printf("12.1. 랜덤 생성 데이터의 정렬\n");
            printf("  원소 수 : ");
            scanf("%d", &num);
            int* B = (int*)malloc(sizeof(int) * num);

            for (int i = 0; i <= num; i++) {
                A = array_random(A, i);
            }
            
            memcpy(B, A, sizeof(int) * num);
            insertion_sort(B, num);

            printf("B[i] <= B[i+1] 체크\n");
            if (sorted_check(B, num) == 1) {
                printf("삽입 정렬 완료\n");
            }
            else printf("삽입 정렬 실패\n");
            printf("\n");

            start = clock();
            sort(A, num);
            end = clock();
            selection_time = (double)(end - start) / CLOCKS_PER_SEC;
            printf("selection sort time : %f\n", selection_time);

            start = clock();
            insertion_sort(A, num);
            end = clock();
            insertion_time = (double)(end - start) / CLOCKS_PER_SEC;
            printf("insertion sort time : %f\n", insertion_time);

            start = clock();
            quick_sort(A, 0, num-1);
            end = clock();
            quick_time = (double)(end - start) / CLOCKS_PER_SEC;
            printf("quick sort time : %f\n", quick_time);
        }

        if (menuChoice == 2) {
            printf("\n");
            printf("12.2. 오름차순 정렬된 데이터의 정렬\n");
            printf("  원소 수 : ");
            scanf("%d", &num);

            for (int i = 0; i <= num; i++) {
                A = array_ascend(A, i);
            }
            
            start = clock();
            sort(A, num);
            end = clock();
            selection_time = (double)(end - start) / CLOCKS_PER_SEC;
            printf("selection sort time : %f\n", selection_time);

            start = clock();
            insertion_sort(A, num);
            end = clock();
            insertion_time = (double)(end - start) / CLOCKS_PER_SEC;
            printf("insertion sort time : %f\n", insertion_time);

            start = clock();
            quick_sort(A, 0, num-1);
            end = clock();
            quick_time = (double)(end - start) / CLOCKS_PER_SEC;
            printf("quick sort time : %f\n", quick_time);
        }

        if (menuChoice == 3) {
            printf("\n");
            printf("12.3. 내림차순 정렬된 데이터의 정렬\n");
            printf("  원소 수 : ");
            scanf("%d", &num);

            for (int i = 0; i <= num; i++) {
                A = array_deascend(A, i);
            }
            
            start = clock();
            sort(A, num);
            end = clock();
            selection_time = (double)(end - start) / CLOCKS_PER_SEC;
            printf("selection sort time : %f\n", selection_time);

            start = clock();
            insertion_sort(A, num);
            end = clock();
            insertion_time = (double)(end - start) / CLOCKS_PER_SEC;
            printf("insertion sort time : %f\n", insertion_time);

            start = clock();
            quick_sort(A, 0, num-1);
            end = clock();
            quick_time = (double)(end - start) / CLOCKS_PER_SEC;
            printf("quick sort time : %f\n", quick_time);
        }

        else {
            printf("잘못 입력하셨습니다\n");
        }
    }
}