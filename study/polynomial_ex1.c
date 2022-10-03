#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
#define MAX_DEGREE 101
#define MAX_TERMS 100
#define _CRT_SECURE_NO_WARNINGS

typedef struct {
    float coef; // 계수 -> 실수
    int expon;  // 지수 -> 정수
} polynomial;

polynomial terms[MAX_TERMS];
int avail = 0;

void attach(float coefficient, int exponent);

void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD) {
    float coefficient;
    *startD = avail;

    while (startA <= finishA && startB <= finishB) 
        switch (COMPARE(terms[startA].expon, terms[startB].expon)) {
            case -1: // a의 지수가 b의 지수보다 작은 경우
                attach(terms[startB].coef, terms[startB].expon);
                startB++;
                break;
            
            case 0: // 지수가 같은 경우
                coefficient = terms[startA].coef + terms[startB].coef;
                if (coefficient)
                    attach(coefficient, terms[startA].expon);
                startA++;
                startB++;
                break;
            
            case 1: // a의 지수가 b의 지수보다 큰 경우
                attach(terms[startA].coef, terms[startA].expon);
                startA++;
        }

        // A(x)의 나머지 항들을 첨가
        for (; startA <= finishA; startA++)
            attach(terms[startA].coef, terms[startA].expon);
        
        // B(x)의 나머지 항들을 첨가
        for (; startB <= finishB; startB++)
            attach(terms[startB].coef, terms[startB].expon);
        
        *finishD = avail - 1;
}

// 새로운 항을 첨가하는 attach 함수
void attach(float coefficient, int exponent) {
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "다항식에 항이 너무 많습니다.");
        exit(EXIT_FAILURE);
    }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}

int main() {

}