#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 10

int stack[MAX_STACK_SIZE];
int top = -1;

int isFull() {
    if (top >= MAX_STACK_SIZE - 1) {
        printf("스택이 꽉 찼습니다. pop하고 다시 시도해주세요.\n");
        return 1;
    }
    else return 0;
}

int isEmpty() {
    if (top == -1) {
        printf("스택에 더이상 들어있는 데이터가 없습니다.\n");
        return 1;
    } 
    else return 0;
}

void push(int item) {
    if (!isFull()) {
        top++;
        stack[top] = item;
    }
}

int pop() {
    if (!isEmpty()) {
        return stack[top--];
    }
}

void printStack() {
    printf("    index : item\n");
    for (int i = 0; i <= top; i++) {
        printf("\t%d :  %d\n", i, stack[i]);
    }
    printf("\n");
}

int main() {
    int choiceNum;
    int pushItem;
    int popItem;

    while(1) {
        printf("스택 - 1.push 2.pop -1.exit : ");
        scanf("%d", &choiceNum);
        if (choiceNum == 1) {
            printf("push item : ");
            scanf("%d", &pushItem);
            push(pushItem);
            printStack();
        }
        else if (choiceNum == 2) {
            printf("pop item : ");
            scanf("%d", &popItem);
            pop();
            printStack();
        }
        else if (choiceNum == -1) {
            printf("\n- 종료합니다.-\n\n");
            printf("현재 스택 데이터\n");
            printStack();
            break;
        }
    }
}