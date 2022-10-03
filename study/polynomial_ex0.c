#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
#define MAX_DEGREE 101
#define MAX_TERMS 100
#define _CRT_SECURE_NO_WARNINGS

typedef struct {
    float coef;
    int expon;
} Polynomial;

int startA, startB, startD;
int finishA, finishB, finishD;
int degree1, degree2;
int avail = 0;

Polynomial *terms = 0;


void attach(float coefficient, int exponent);

void print_poly(int start, int finish, Polynomial terms[]){
    printf("%.0fx^%d", terms[start].coef, terms[start].expon);

    for (int i = start+1; i < finish; i++) {
        printf(" + %.0fx^%d", terms[i].coef, terms[i].expon);
    }
    printf("\n");
}

void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD) {
    float coefficient;
    *startD = avail;

    while (startA <= finishA && startB <= finishB)
        switch (COMPARE(terms[startA].expon, terms[startB].expon)) {
            case -1:
                attach(terms[startB].coef, terms[startB].expon);
                startB++;
                break;

            case 0:
                coefficient = terms[startA].coef + terms[startB].coef;
                if (coefficient)
                    attach(coefficient, terms[startA].expon);
                startA++;
                startB++;
                break;

            case 1:
                attach(terms[startA].coef, terms[startA].expon);
                startA++;
        }

        for (; startA <= finishA; startA++)
            attach(terms[startA].coef, terms[startA].expon);

        for (; startB <= finishB; startB++)
            attach(terms[startB].coef, terms[startB].expon);

        *finishD = avail - 1;
}

void attach(float coefficient, int exponent) {
    // if (avail >= 10) {
    //     printf("배열 크기 재할당\n");
    //     polynomial *terms = (polynomial*)realloc(terms, sizeof(polynomial)*MAX_TERMS);
    // }
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "다항식에 항이 너무 많습니다.");
        exit(EXIT_FAILURE);
    }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}


int main() {

    terms = (Polynomial*)malloc(sizeof(Polynomial)*MAX_TERMS);

    printf("첫번째 다항식의 차수를 입력하세요 : ");
    scanf("%d", &degree1);

    startA = 0;
    finishA = degree1 + 1;

    for (int i = 0; i <= degree1; i++) {
        terms[i].expon = degree1 - i;
        printf("x^(%d)의 상수를 입력하세요 : ", degree1-i);
        scanf("%f", &terms[i].coef);
    }

    printf("\n두번째 다항식의 차수를 입력하세요 : ");
    scanf("%d", &degree2);

    startB = finishA + 1;
    finishB = startB + degree2 + 1;

    for (int i = 0; i <= degree2; i++) {
        terms[startB+i].expon = degree2 - i;
        printf("x^(%d)의 상수를 입력하세요 : ", degree2 - i);
        scanf("%f", &terms[startB+i].coef);
    }

    if (terms == NULL) {
        printf("메모리가 다차서 재할당 합니다!");
    }

    avail = finishB + 1;

    printf("\n첫번째 다항식 : ");
    print_poly(startA, finishA, terms);

    printf("\n두번째 다항식 : ");
    print_poly(startB, finishB, terms);
    printf("\n");

    printf("덧셈 결과\n");
    padd(startA, finishA, startB, finishB, &startD, &finishD);

    print_poly(startD, finishD+1, terms);
}