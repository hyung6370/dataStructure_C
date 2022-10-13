#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 10

typedef int element;
typedef struct {
    element stack[MAX_STACK_SIZE];
    int top;
} Stack;

void init_stack(Stack *s) {
    s->top = -1;
}

int isFull(Stack *s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}

int isEmpty(Stack *s) {
    return (s->top == -1);
}

void push(Stack *s, element item) {
    if (isFull(s)) {
        fprintf(stderr, "스택이 다찼습니다.\n");
        return;
    }
    else {
        s->stack[++(s->top)] = item;
    }
}

element pop(Stack *s) {
    if (isEmpty(s)) {
        fprintf(stderr, "더 이상 스택에 들어있는 데이터가 없습니다.\n");
        exit(1);
    }
    else {
        return s->stack[(s->top)--];
    }
}

void printStack() {
    for (int i = 0; i <= Stack.top; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int main() {
    int choiceNum;
    int pushItem;
    int popItem;
    Stack s;
    init_stack(&s);
    while(1) {
        printf("스택 - 1.push 2.pop 3.exit : ");
        scanf("%d", &choiceNum);
        if (choiceNum == 1) {
            printf("push item : ");
            scanf("%d", &pushItem);
            push(&s, pushItem);
            
        }
        else if (choiceNum == 2) {
            printf("pop item : ");
            scanf("%d", &popItem);
            printf("%d\n", pop(&s));
        }
        else if (choiceNum == 3) {
            printf("종료!\n");
            break;
        }
    }
}