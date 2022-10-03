#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
#define MAX_TERMS 10000
#define _CRT_SECURE_NO_WARNINGS

typedef struct {
    float coef;
    int expon;
} Polynomial;

int avail = 0;

Polynomial *terms = 0;

void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD);
void pmul(int startA, int finishA, int startB, int finishB, int *startD, int *finishD);
void attach(float coefficient, int exponent);
void attach_mul(float coefficient, int exponent, int s);

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

void pmul(int startA, int finishA, int startB, int finishB, int *startD, int *finishD) {
    float coefficient;
    int exponent;
    int s;
    *startD = avail;

    for (int i = startA; i <= finishA; i++) {
        for (int j = startB; j <= finishB; j++) {
            coefficient = terms[i].coef * terms[j].coef;
            exponent = terms[i].expon + terms[j].expon;
            s = finishA + finishB;
            attach_mul(coefficient, exponent, s);
        }
    }
    *finishD = avail - 1;
}

void attach(float coefficient, int exponent) {
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "다항식에 항이 너무 많습니다.");
        exit(EXIT_FAILURE);
    }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}

void attach_mul(float coefficient, int exponent, int s) {
    int i;

    if (avail >= MAX_TERMS) {
        printf("다항식에 항이 너무 많습니다.");
        exit(EXIT_FAILURE);
    }
    avail--;
    i = avail;
    for (int j = i; j >= s; j--) {
        if (terms[j].expon == exponent) {
            terms[j].coef += coefficient;
            avail++;
            return;
        }
        else break;
    }
    avail++;
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}

int main() {
    int i = 0, j = 0;
    int startA, startB, startD;
    int finishA, finishB, finishD;
    int temp;
    int count1 = 0, count2 = 0;
    int choiceOp;
    float input_coef;
    int input_expon;

    terms = (Polynomial*)malloc(sizeof(Polynomial)*MAX_TERMS);

    printf("1. 덧셈, 2. 곱셈 : ");
    scanf("%d", &choiceOp);
    
    startA = avail;
    while(1) {
        printf("A(x)의 항을 입력하세요. (coef expon) : ");
        scanf("%f %d", &input_coef, &input_expon);

        if (input_coef == -1 && input_expon == -1) break;
        i++; count1++;
        attach(input_coef, input_expon);
    }
    finishA = avail-1;

    printf("다항식 A(x)\n");
    printf("\tcoef\t\texpon\t\n");
    for (int i = 0; i < count1; i++) {
        printf("\t%.2f\t\t%d\t\n", terms[i].coef, terms[i].expon);
    }

    startB = avail;
    while(1) {
        printf("B(x)의 항을 입력하세요. (coef expon) : ");
        scanf("%f %d", &input_coef, &input_expon);

        if (input_coef == -1 && input_expon == -1) break;
        j++; count2++;
        attach(input_coef, input_expon);
    }
    finishB = avail-1;


    printf("다항식 B(x)\n");
    printf("\tcoef\t\texpon\t\n");
    for (int i = count1; i < count1 + count2; i++) {
        printf("\t%.2f\t\t%d\t\n", terms[i].coef, terms[i].expon);
    }

    avail = finishB + 1;

    if (choiceOp == 1) {
        padd(startA, finishA, startB, finishB, &startD, &finishD);

        printf("\n다항식 덧셈 결과 : D(x)\n");
        printf("\tcoef\t\texpon\t\n");
        for (int i = startD; i <= finishD-1; i++) {
            printf("\t%.2f\t\t%d\t\n", terms[i].coef, terms[i].expon);
        }
    }
    else if (choiceOp == 2) {
        pmul(startA, finishA, startB, finishB, &startD, &finishD);

        startA = startD;
        finishA = startA + (finishB-startB);
        startB = finishA + 1;
        finishB = startB + (finishA - startA);
        temp = finishB - startB;

        for (int i = 1; i <= temp+1; i++) {
            padd(startA, finishA, startB, finishB, &startD, &finishD);
            startB = startB + temp + 1;
            finishB = finishB + temp + 1;
            startA = startD;
            finishA = finishD;

            printf("single_mul - C%d(x)\n", i);
            printf("\tcoef\t\texpon\t\n");
            for (int k = startD; k <= finishD; k++)
                printf("\t%.2f\t\t%d\t\n", terms[k].coef, terms[k].expon);
        }

        printf("\n다항식 곱셈 결과 : D(x)\n");
        printf("\tcoef\t\texpon\t\n");
        for (int i = startD; i <= finishD; i++) {
            printf("\t%.2f\t\t%d\t\n", terms[i].coef, terms[i].expon);
        }

    }
    
}