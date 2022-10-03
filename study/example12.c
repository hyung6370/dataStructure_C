#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define MAX_TERMS 100
#define COMPARE(x,y) ( ((x)<(y)) ? -1: ((x)==(y)) ? 0 : 1)

int input();
void output(int start, int finish);
void add();
void mul();
int attach(int x, int y);

typedef struct{
    int coef;
    int expon;
} polynomial;

polynomial terms[MAX_TERMS];
polynomial terms_pol[MAX_TERMS]={0,};
polynomial terms_temp[MAX_TERMS];// 곱셈을 위해 선언

int avail =0;// 현재 사용할 structure배열의 index 값
int starta=0;// A(x)의 맨 처음 index
int finisha=0;// A(x)의 맨 끝 index
int startb=0;// B(x)의 맨 처음 index
int finishb=0;// B(x)의 맨 끝 index
int starto=0;// 결과 다항식의 맨 처음 index
int finisho=0;// 결과 다항식의 맨 끝 index

int main() {
    int menu;

    printf("================ MENU ================ \n");
    printf("= 1. Input A(x)                      = \n");
    printf("= 2. Input B(x)                      = \n");
    printf("= 3. Addition of A(x) and B(x)       = \n");
    printf("= 4. Multiplication of A(x) and B(x) = \n");
    printf("= 5. Exit Program                    = \n");
    printf("====================================== \n");
    printf("\n Enter your choice ? \n");

    while(1) {
        scanf("%d",&menu);

        getchar();
        switch(menu) {
            case 1 :
                printf("Input A(x) (ex: 1x2+3x1+1 ) ? ");
                starta=avail;
                input();
                finisha=avail-1;
                printf("A(x) = ");
                output(starta,finisha);
                break;
            case 2 :
                printf("Input B(x) ? ");
                startb=avail;
                input();
                finishb=avail-1;
                printf("B(x) = ");
                output(startb,finishb);
                break;
            case 3 :
                starto=avail;
                add();
                break;
            case 4 :
                starto=avail;
                mul();
                break;
            case 5 :
                return 0;
                break;
            }
    }
}

int input() { // 다항식을 입력받음 지수나 계수가 1일 경우는 꼭 1을 써야한다.

    char temp[MAX_TERMS];
    char temp2[9];
    int i=0;
    int c=0;
    int ch;
    int j=1;

    scanf("%s", &temp);
    while( (int)temp[i] != 0) {
    j=1;
        if(isdigit(temp[i])) {
            c=0;
            if(temp[i-1]=='-') { // 입력받은 글자 앞의 부호가 -이면 음수를 계수에 저장
                j=-1;
                while(isdigit(temp[i])) {
                    temp2[c]=temp[i];
                    c++;
                    i++;
                }
                terms[avail].coef=atoi(temp2)*j;
                for(c=0;c<9;c++)
                    temp2[c]='x';
            }
            else if(temp[i-1]=='x') { //입력받은 글자 앞이 x이면 지수에 저장 
                while(isdigit(temp[i])) {
                    temp2[c]=temp[i];
                    c++;
                    i++;
                }
                terms[avail++].expon=atoi(temp2)*j;
                for(c=0;c<9;c++)
                    temp2[c]='x';
            }
            else if(temp[i-1]=='+') { //입력받은 글자 앞이 +면 계수에 저장
                while(isdigit(temp[i])) {
                    temp2[c]=temp[i];   
                    c++;
                    i++;
                }
                terms[avail].coef=atoi(temp2)*j;
                for(c=0;c<9;c++)
                    temp2[c]='x';
            }
            else {
                while(isdigit(temp[i])) { //위의 경우가 아니면 계수에 저장
                    temp2[c]=temp[i];
                    c++;
                    i++;
                }
                terms[avail].coef=atoi(temp2)*j;
                for(c=0;c<9;c++)
                    temp2[c]='x';
            }
            if ((int)temp[i] == 0)
                terms[avail++].expon=0;
        }
        else i++;
    }
    return 0;
}

void output(int start, int finish) {
    int i=start;
    int j=finish;

    for(i=start;i<=j;i++) {
        if(terms[i].coef >= 0 && i == start && terms[i].expon !=0) {
        // 계수가 양수이고 첫항
        // 이고 지수가 0이 아니면
            printf("%d",terms[i].coef);
            printf("x");
            printf("%d",terms[i].expon);
        }
        else if(terms[i].coef >= 0 && terms[i].expon !=0) {
        // 계수가 양수이고 지수가 0이
        // 아니고 첫항이 아니면
            printf("+%d",terms[i].coef);
            printf("x");
            printf("%d",terms[i].expon);
        }
        else if(terms[i].coef < 0 && terms[i].expon !=0) {
        // 계수가 음수이고 지수가 0이 아니면
            printf("%d",terms[i].coef);
            printf("x");
            printf("%d",terms[i].expon);
        }
        else if(terms[i].coef > 0 && terms[i].expon == 0) {
        // 계수가 양수이고 지수가 0이면
            printf("+%d",terms[i].coef);
            break;
        }
        else if(terms[i].coef < 0 && terms[i].expon == 0) {
        // 계수가 음수이고 지수가 0이면
            printf("%d",terms[i].coef);
            break;
        }
    }
    printf("\n");
    // return 0;
}

void add() {
    while((starta <= finisha)  && (startb <= finishb)) {
        switch(COMPARE(terms[starta].expon, terms[startb].expon)) {
            case -1:// 지수를 비교해서 뒤에것이 크면 뒤에항의 index를 증가
                attach(terms[startb].coef, terms[startb].expon);
                startb++;
                break;
            case 0://지수가 같으면 두 계수의 합을 반환하고 둘다 index를 증가
                attach(terms[starta].coef+terms[startb].coef,terms[starta].expon);
                starta++;
                startb++;
                break;
            case 1://지수가 앞에것이 크면 앞의항의 index를 증가
                attach(terms[starta].coef,terms[starta].expon);
                starta++;
                break;
        }
    }
    finisho=avail-1;//저장된 다항식의 마지막 index값
    output(starto, finisho);//화면에 출력
}

int attach(int x, int y) { //넘어온 값을 결과에 저장 
    terms[avail].coef=x;
    terms[avail++].expon=y;
}

void mul() {
    int size = terms[starta].expon + terms[startb].expon + 1;//결과값 저장을 위해....
    int i, j;
    int *mulOut;

    mulOut = (int *)malloc(size);

    for(i = 0; i < size; i++)//새로운 배열(계수만 계산)을 초기화
        mulOut[i] = 0;

    for(i = starta; i <= finisha; i++)
        for(j = startb; j <= finishb; j++)
            mulOut[terms[i].expon + terms[j].expon] += terms[i].coef * terms[j].coef;
        //지수의 합을 배열의 index로 하고 거기에 게수의 곱을 저장한다.
    for(i = size - 1; i >= 0; i--)
        if(mulOut[i] != 0) {
            if (i == size -1);
            else {
                if(mulOut[i] > 0)
                    printf("+");//양수이면
                else
                    printf("-");//음수이면
            }
            printf("%d", abs(mulOut[i]));// 절대값을 출력한다.
            if(i != 0)
                printf("x%d", i);
        }

printf("\n");
}