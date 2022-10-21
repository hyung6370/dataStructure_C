#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100  // postfix가 들어가 있는 곳 
#define _CRT_SECURE_NO_WARNINGS

typedef enum {
    lparen, // "("
    rparen, // ")"
    plus,   // "+"
    minus,  // "-"
    times,  // "*"
    divide, // "/"
    mod,    // "%"
    eos,    // 끝
    operand // 피연산자 
} precedence;

static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 }; // 스택 내 우선순위
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 }; // 입력 될 때 우선순위
    
int stack[MAX_STACK_SIZE]; // global stack
char expr[MAX_EXPR_SIZE];  // input string
char new_expr[MAX_STACK_SIZE];

int value;
int top;

void push(int item);
int pop();
int eval(char* expr);
precedence get_token(char *expr, char* symbol, int *n);
void postfix(char* expr, char* new_expr);
char print_token(precedence token);

void push(int item) {
    if (top == MAX_STACK_SIZE - 1) {
        printf("스택이 꽉 차있습니다.\n");
        return;
    }
    else {
        stack[++top] = item;
    }
}

int pop() {
    if (top == -1) {
        printf("스택이 비어있습니다.\n");
        return eos;
    }
    else {
        return stack[top--];
    }
}

int eval(char* expr) {
    // expr[] 배열에 문자열로 저장된 postfix 수식 계산
    // expr[]과 stack[], 그리고 top은 전역변수
    // get_token() 함수는 수식의 각 문자의 precedence를 return
    // 수식에서 피연산자는 한 문자로 구성된다고 가정

    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;      // 수식 문자열의 현재 판독 위치
    top = -1;       // stack 초기화
    token = get_token(expr, &symbol, &n);  // expr 배열의 n번째 값을 읽어서, symbol에 둬라
                                     // expr 수식에서 토큰을 하나씩 검사

    while (token != eos) {
        if (token == operand) 
            push(symbol - '0'); // 피연산자를 만나면 스택에 저장
        else {
            // stack에서 피연산자 2개를 제거한 후, 이를 이용하여
            // 수식을 계산한 후 결과를 다시 stack에 저장
            op2 = pop();
            op1 = pop();

            switch(token) { // 토큰이 뭐냐에 따라서
                case plus:
                    push(op1 + op2);
                    break;
                
                case minus:
                    push(op1 - op2);
                    break;
                
                case times:
                    push(op1 * op2);
                    break;
                
                case divide:
                    push(op1 / op2);
                    break;
                
                case mod:
                    push(op1 % op2);
            } // 계산하고 다시 push 
        }
        token = get_token(expr, &symbol, &n);
    }
    return pop();  // return result, 스택 0에 있는 값을 리턴하면 원하는 수식의 결과 얻음
}

precedence get_token(char *expr, char* symbol, int *n) {
    // 수식 문자열에서 다음 문자를 검사하여, 해당 token을 반환

    *symbol = expr[(*n)++];  // 문자를 하나씩 가져온다
    switch(*symbol) {
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '/': return divide;
        case '*': return times;
        case '%': return mod;
        case ' ': return eos;
        default : return operand;  // 오류 검사 없음. 피연산자의 값은 symbol에 할당
    }
}

void postfix(char* expr, char* new_expr) {
    // 수식을 후위 표기식으로 출력한다.
    // expr[] (infix 저장)과 stack[], 그리고 top은 전역변수
    // new_expr[]에 결과값 저장

    char symbol;
    precedence token;
    int n = 0;
    int top = -1;

    push(eos); // place eos on stack
    for (token = get_token(expr, &symbol, &n); token != eos; token = get_token(expr, &symbol, &n)) {
        if (token == operand) printf("%c", symbol);
        else if (token == rparen) {
            // 왼쪽 괄호가 나올 때까지 stack pop
            while (stack[top] != lparen)
                print_token(pop());
            pop(); // 왼쪽 괄호 제거 
        }
        else {  // 우선순위가 높은 연산자 pop, associativity?
            while (isp[stack[top]] >= icp[token])
                print_token(pop());
            push(token);
        }
    }
    while ((token == pop()) != eos)
        print_token(token);
    printf("\n");

    strcpy(expr, new_expr);
    puts(expr);
}

char print_token(precedence token) {
    static int index = 0;
    char aChar;

    switch (token) {
        case plus : aChar = '+'; break;
        case minus : aChar = '-'; break;
        case divide : aChar = '/'; break;
        case times : aChar = '*'; break;
        case mod : aChar = '%'; break;
        case eos : aChar = ' '; break;
        default : aChar - token;
    }
    new_expr[index++] = aChar;
}

int main() {
    printf("Infix : ");
    scanf("%s", expr);
    printf("Infix to Postfix :\n");
    postfix(expr, new_expr);
    printf("Token | Stack\n");
    
    // printf("Infix to Postfix :\n");
    // printf("  Token | Stack \n");
    for (int i = 0; i <= top; i++) {
        printf("stack[%d] : %c\n", i, stack[i]);
    }
}