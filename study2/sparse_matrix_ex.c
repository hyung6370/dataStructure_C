#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101
#define MAX_COL 15
#define MAX_ROW 15

typedef struct {
    int col;
    int row;
    int value;
} term;

term a[MAX_TERMS];

// 희소 행렬의 전치
void transpose(term a[], term b[]);

// 희소 행렬의 빠른 전치
void fastTranspose(term a[], term b[]);

// 두 희소 행렬의 곱셈
void mmult (term a[], term b[], term d[]);

// storeSum 함수 
void storeSum(term d[], int *totalD, int row, int column, int *sum);



// 희소 행렬의 전치
void transpose(term a[], term b[]) {
    int n, i, j, currentB;
    n = a[0].value; // 총 원소의 수
    b[0].row = a[0].col; // b의 행 수 = a의 행 수
    b[0].col = a[0].row;
    b[0].value = n;

    if (n > 0) {  // 0이 아닌 행렬
        currentB = 1;

        for (i = 0; i < a[0].col; i++)
        // a에서의 열별 전치
            for (j = 1; j <= n; j++)
            // 현재 열로부터 원소를 찾는다  
            if (a[j].col == i) {
                b[currentB].row = a[j].col;
                b[currentB].col = a[j].row;
                b[currentB].value = a[j].value;
                currentB++;
            }
    }
}

// 희소 행렬의 빠른 전치
void fastTranspose(term a[], term b[]) {
    // a를 전치시켜 b에 저장
    int rowTerms[MAX_COL];
    int startingPos[MAX_COL];
    int i, j;
    int numCols = a[0].col; 
    int numTerms = a[0].value;

    b[0].row = numCols; 
    b[0].col = a[0].row;
    b[0].value = numTerms;

    if (numTerms > 0) {  // 0이 아닌 행렬
        for (i = 0; i < numCols; i++)
            rowTerms[i] = 0;
        
        for (i = 1; i <= numTerms; i++)
            rowTerms[a[i].col]++;
        startingPos[0] = 1;

        for (i = 1; i < numCols; i++)
            startingPos[i] = startingPos[i-1] + rowTerms[i-1];
        
        for(i = 1; i <= numTerms; i++) {
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}



int main() {

}