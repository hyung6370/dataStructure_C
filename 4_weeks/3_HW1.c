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
int avail = 0;

Polynomial *terms = 0;

void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD);
void attach(float coefficient, int exponent);
void print_poly(int start, int finish);

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
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "다항식에 항이 너무 많습니다.");
        exit(EXIT_FAILURE);
    }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}

void print_poly(int start, int finish) {
    int i = start;
    int j = finish;

    for(i = start; i <= j; i++) {
        if(terms[i].coef >= 0 && i == start && terms[i].expon !=0) {
        // 계수가 양수이고 첫항
        // 이고 지수가 0이 아니면
            printf("%.2f",terms[i].coef);
            printf("x^");
            printf("%d ",terms[i].expon);
        }
        else if(terms[i].coef >= 0 && terms[i].expon !=0) {
        // 계수가 양수이고 지수가 0이
        // 아니고 첫항이 아니면
            printf("+%.2f",terms[i].coef);
            printf("x^");
            printf("%d ",terms[i].expon);
        }
        else if(terms[i].coef < 0 && terms[i].expon !=0) {
        // 계수가 음수이고 지수가 0이 아니면
            printf("%.2f",terms[i].coef);
            printf("x^");
            printf("%d ",terms[i].expon);
        }
        else if(terms[i].coef > 0 && terms[i].expon == 0) {
        // 계수가 양수이고 지수가 0이면
            printf("+ %.2f",terms[i].coef);
            break;
        }
        else if(terms[i].coef < 0 && terms[i].expon == 0) {
        // 계수가 음수이고 지수가 0이면
            printf("%.2f",terms[i].coef);
            break;
        }
    }
    printf("\n");
    // return 0;
}


int main() {
    
    int i = 0;
    int j = 0;
    int count1 = 0;
    int count2 = 0;
    int input_coef, input_expon;

    terms = (Polynomial*)malloc(sizeof(Polynomial)*10);

    while(1) {
        printf("A(x)의 항을 입력하세요. (coef expon) : ");
        scanf("%d %d", &input_coef, &input_expon);

        if (input_coef == -1 && input_expon == -1) break;
        terms[i].coef = input_coef;
        terms[i].expon = input_expon;
        i++; count1++;
    }
    startA = 0;
    finishA = count1-1;

    printf("다항식 A(x)\n");
    printf("\tcoef\t\texpon\t\n");
    for (int i = 0; i < count1; i++) {
        printf("\t%.2f\t\t%d\t\n", terms[i].coef, terms[i].expon);
    }


    while(1) {
        printf("B(x)의 항을 입력하세요. (coef expon) : ");
        scanf("%d %d", &input_coef, &input_expon);

        if (input_coef == -1 && input_expon == -1) break;
        terms[j+count1].coef = input_coef;
        terms[j+count1].expon = input_expon;
        j++; count2++;
    }
    startB = finishA + 1;
    finishB = finishA + startB;

    printf("다항식 B(x)\n");
    printf("\tcoef\t\texpon\t\n");
    for (int i = count1; i < count1 + count2; i++) {
        printf("\t%.2f\t\t%d\t\n", terms[i].coef, terms[i].expon);
    }

    avail = finishB + 1;

    if (avail >= 10) {
        printf("\n다항식에 항이 너무 많아 메모리를 재할당하겠습니다\n");
        terms = (Polynomial*)realloc(terms, sizeof(Polynomial)*MAX_TERMS);
        printf("할당중..\n");
        printf("할당완료!\n");
    }

    padd(startA, finishA, startB, finishB, &startD, &finishD);

    printf("\n다항식 덧셈 결과 : D(x)\n");
    printf("\tcoef\t\texpon\t\n");
    for (int i = startD; i <= finishD-1; i++) {
        printf("\t%.2f\t\t%d\t\n", terms[i].coef, terms[i].expon);
    }
    print_poly(startD, finishD);
}