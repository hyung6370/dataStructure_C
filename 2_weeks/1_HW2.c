#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX_SIZE 1000001
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define _CRT_SECURE_NO_WARNINGS

void sort(int[], int);  // selection sort
int is_sorted(int A[], int n);

int main() {
    int i, n;
    int list[MAX_SIZE];
    int sec;
    srand(time(NULL));
    // FILE* fp;
    // fp = fopen("/Users/emptyhead/Desktop/C/test.txt", "w, ccs=UTF-8");

    printf("Enter the number of numbers to generate: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_SIZE) {
        fprintf(stderr, "Improper value of n\n");
        exit(EXIT_FAILURE);
    }

    // randomly generate numbers
    for (i = 0; i < n; i++) {
        list[i] = rand() % 1000;
        printf("%d  ", list[i]);
    }
    int start = clock();

    sort(list, n);

    sec = (double)(clock()-start) / CLOCKS_PER_SEC;

    printf("\n Sorted array:\n ");
    // print out sorted numbers
    for (i = 0; i < n; i++) {
        printf("n:%d  ", n);
        printf("%d  ", list[i]);
        printf("clock : %.3lf(sec)", (double)(clock()-start)/CLOCKS_PER_SEC);
        is_sorted(list, n);
        // fputc(list[i], fp);
        // printf("\n");
        // fputc((double)(clock()-start)/CLOCKS_PER_SEC, fp);
        
    // printf("\n");
    }
    // fclose(fp);
    

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
            printf("  정렬완료");
            printf("\n");
            return 1;
        }
        else {
            printf("  정렬실패");
            printf("\n");
            return 0;
        }
    }
}