#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100
#define COMPARE(x,y) (((x)<(y)) ? -1:((x)==(y)) ? 0:1)
typedef struct {
    int coef;
    int expon;
} Polynomial;

Polynomial terms[MAX_TERMS];
int avail=0;
void padd(int starta, int finisha, int startb, int finishb, int *startc, int *finishc);
void attach(int coefficient, int exponent);

int main() {
    int starta, finisha, startb, finishb, startcc, finishcc;
    starta=0;
    printf("다항식을 입력하시오: \n"); 
    while(1) {
        printf("%d번째 계수 : ", starta+1);
        scanf("%d", &terms[starta].coef);

        if (terms[starta].coef==0) break ;
        printf("%d번째 지수 : ", starta+1);
        scanf("%d", &terms[starta].expon);
        
        if (terms[starta].expon==0) break ;
        starta++;
    }

    finisha=starta;
    printf("다항식 A : ");
    for(starta=0; starta<=finisha; starta++) {
        if(terms[starta].expon==0) {
            printf("%d\n", terms[starta].coef);
            break;
        }
        printf("%dX^%d+", terms[starta].coef, terms[starta].expon);
    }
    starta=0;
    startb=finisha+1;
    printf("\nB 다항식을 입력하시오 .\n");

    while(1) {
        printf("%d번째 계수 : ", startb-finisha);
        scanf("%d", &terms[startb].coef);

        if (terms[startb].coef==0) break ;
        printf("%d번째 지수 : ", startb-finisha);
        scanf("%d", &terms[startb].expon);

        if (terms[startb].expon==0) break ;
        startb++;
    }
    finishb=startb;
    startb=finisha+1;
    printf("B 다항식: ");

    for(; startb<=finishb; startb++) {
        if(terms[startb].expon==0) {
            printf("%d\n", terms[startb].coef);
            break;
        }
    printf("%dX^%d+", terms[startb].coef, terms[startb].expon);
    }

    startb=finisha+1;
    avail=finishb+1;
    padd(starta, finisha, startb, finishb, &startcc, &finishcc);
    printf("두 다항식의 합은\n : ");
    printf("sa%d fa%d sb%d fb%d sc%d fc%d \n",starta, finisha, startb, finishb, startcc, finishcc);

    for(; startcc<=finishcc; startcc++) {
        printf("%dX^%d+", terms[startcc].coef, terms[startcc].expon);
        if(terms[startcc].expon==0) {
            printf("%d\n",terms[startcc].coef);
            break;
        }
    }
}

void padd(int starta, int finisha, int startb, int finishb, int *startc, int *finishc) {
    int coefficient;
    *startc=avail;

    while(starta<=finisha && startb<=finishb) {
        switch(COMPARE(terms[starta].expon, terms[startb].expon)) {
            case -1 : attach(terms[startb].coef, terms[startb].expon);
                startb++;
                break;

            case 0 : coefficient=terms[starta].coef+terms[startb].coef;
                if(coefficient)
                    attach(coefficient,
                terms[starta].expon);
                starta++;
                startb++;
                break;

            case 1 : attach(terms[starta].coef, terms[starta].expon);
                starta++;
        }
    }

    for(; starta<=finisha; starta++)
        attach(terms[starta].coef, terms[starta].expon);
    for(; startb<=finishb; startb++)
        attach(terms[startb].coef, terms[startb].expon);
    *finishc=avail-1;
}

void attach(int coefficient, int exponent) {
    if(avail>=MAX_TERMS) {
        fprintf(stderr, "다항식에 항이 너무 많다.\n"); 
    exit(1);
    }

terms[avail].coef=coefficient;
terms[avail++].expon=exponent;
}