#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100      /* 항 배열의 크기*/

typedef struct {
    float coef;
    int expon;
} polynomial;

polynomial terms[MAX_TERMS];
int avail = 0;

void attach(float coefficient, int exponent) {             /* 새로운 항을 다항식에 첨가한다. */
    if (avail >= MAX_TERMS) {
        printf(" 다항식에 항이 너무 많다.") ;
        exit(1);          
    }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}

void attach2(float coefficient, int exponent,int s) {  //같은 지수의 계수 더하기{
      /*  곱셈한 항을 다항식에 첨가 */
    int i;
    int j;
    
    if(avail >= MAX_TERMS){
        printf("다항식에 항이 너무 많다.");
        exit(1);
    }
    avail--;
    i = avail;
 
    for(j = i; j >= s; j--) {
        if(terms[j].expon == exponent) {      //지수가 같을 경우 계수를 더해줌
            terms[j].coef += coefficient;
            avail ++;
            return;
        }
        else break;
            //지수가 같지 않을 경우 그냥 다항식에 첨가
    }
    avail ++;
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}

void print(int start, int finish) {
    int i ;
    printf("\n") ;

    if (start <= finish) {
        for ( i = start ; i < finish ; i++ )
            printf("%f x^ %d + ", terms[i].coef, terms[i].expon);
        // 마지막 항을 출력
        printf("%f x^ %d \n", terms[finish].coef, terms[finish].expon);
   }
   else printf(" No terms ") ;

}


void pmult(int starta, int finisha, int startb, int finishb, int *startd, int *finishd) {  
    /* A(x)와 B(x)를 곱하여 D(x)를 생성한다. */
    float coefficient;
    int exponent;
    int i,j;
    int s;

    *startd = avail;
 
    for(i = starta; i<=finisha;i++) {
        for(j=startb;j<=finishb;j++) {
            coefficient = terms[i].coef * terms[j].coef;   //계수의 곱
            exponent = terms[i].expon + terms[j].expon;  // 지수의 합
            s=finisha+finishb;                        // s의 위치 지정
            attach2(coefficient,exponent,s);          //곱셈항 첨가   
        }
    }
    *finishd = avail - 1;
}

int main(int argc, char* argv[]) {

    int startA, finishA ;  // 다항식 A
    int startB, finishB ;  // 다항식 B
    int startC, finishC ;  // 다항식 C
    int i, n, e ;
    float c ;
 
    printf("다항식의 곱셈 연산 수행!\n");
    printf("다항식 A의 항의 수 : ") ;
    scanf("%d", &n) ;

    startA = avail ;
    for ( i = 1; i <= n; i++ ) {
        printf( "\n다항식 A의 %d 번째 항의 계수와 지수 : ", i) ;
        scanf("%f%d", &c, &e) ;

        attach(c, e) ;
    }   
    finishA = avail - 1 ;

    print(startA, finishA) ;   // 다항식 A의 입력결과

    printf("\n다항식 B의 항의 수 : ") ;
    scanf("%d", &n) ;

    startB = avail ;
    for ( i = 1; i <= n; i++ ) {
        printf( "\n다항식 B의 %d 번째 항의 계수와 지수 : ", i) ;
        scanf( "%f%d", &c, &e) ;

        attach(c, e) ;
    }
    finishB = avail - 1 ;

    print(startB, finishB) ;    // 다항식 b의 입력결과

    pmult(startA, finishA, startB, finishB, &startC, &finishC);   // 곱셈
  
    printf(" \n 곱셈의 결과 : ") ;
    print(startC, finishC) ;   // 곱셈 결과 출력

    for (int i = 0; i <= 100; i++) {
            printf("terms[%d] -> 계수 : %f,  지수 : %d\n", i, terms[i].coef, terms[i].expon);
        }

    return 0;
}