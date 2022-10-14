#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100  // postfix가 들어가 있는 곳 

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

int stack[MAX_STACK_SIZE]; // global stack
char expr[MAX_EXPR_SIZE];  // input string

int eval(void) {
    // expr[] 배열에 문자열로 저장된 postfix 수식 계산
    // expr[]과 stack[], 그리고 top은 전역변수
    // get_token() 함수는 수식의 각 문자의 precedence를 return
    // 수식에서 피연산자는 한 문자로 구성된다고 가정

    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;      // 수식 문자열의 현재 판독 위치
    top = -1;       // stack 초기화
    token = get_token(&symbol, &n);  // expr 배열의 n번째 값을 읽어서, symbol에 둬라

    while (token != eos) {
        if (token == operand) // 숫자면 스택에
            push(symbol - '0'); // 피연산자를 만나면 스택에 저장
        else {
            // stack에서 피연산자 2개를 제거한 후, 이를 이용하여
            // 수식을 계산한 후 결과를 다시 stack에 저장
            op2 = pop();
            op1 = pop();

            switch(token) {
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
            }
        }
        token = get_token(&symbol, &n);
    }
    return pop();  // return result
}

precedence get_token(char *symbol, int *n) {
    // 수식 문자열에서 다음 문자를 검사하여, 해당 token을 반환

    *symbol = expr[(*n)++];
    switch(*symbol) {
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '/': return divide;
        case '*': return times;
        case '%': return mod;
        case ' ': return eos;
        default : return operand;  // 오류 검사 없음. 피연산자
    }
}

int main() {

}