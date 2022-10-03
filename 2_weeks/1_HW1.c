#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX_SIZE 100001
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void sort(int[], int);  // selection sort
int is_sorted(int A[], int n);

int main() {
    int i, n;
    int list[MAX_SIZE];

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
    sort(list, n);

    printf("\n Sorted array:\n ");
    // print out sorted numbers
    for (i = 0; i < n; i++) {
        printf("%d  ", list[i]);
    }

    is_sorted(list, n);

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
            printf("\n");
            printf("정렬 됨");
            return 1;
        }
        else {
            printf("\n");
            printf("정렬 실패");
            return 0;
        }
    }
}