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
    int i = 0;
    int count1 = 0;
    int count2 = 0;
    int num1, num2;
    terms = (Polynomial*)malloc(sizeof(Polynomial)*MAX_TERMS);
    while(1) {
        printf("A(x)의 항을 입력하세요. (coef expon) : ");
        scanf("%d %d", &num1, &num2);
        if (num1 == -1 && num2 == -1) break;
        terms[i].coef = num1;
        terms[i].expon = num2;
        i++; count1++;
    }
    printf("다항식 A(x)");
    printf("   coef     expon   \n");
    for (int i = 0; i < count1; i++) {
        printf("   %.2f      %d    \n", terms[i].coef, terms[i].expon);
    }

    while(1) {
        printf("B(x)의 항을 입력하세요. (coef expon) : ");
        scanf("%d %d", &num1, &num2);
        if (num1 == -1 && num2 == -1) break;
        terms[i+count1].coef = num1;
        terms[i+count1].expon = num2;
        i++; count2++;
    }
    printf("다항식 B(x)");
    printf("   coef     expon   \n");
    for (int i = count1; i < count1 + count2; i++) {
        printf("   %.2f      %d    \n", terms[i+count1].coef, terms[i+count1].expon);
    }
    printf("\n");
    printf("\n");
    printf("terms의 길이 : %lu", sizeof(terms));
    
}