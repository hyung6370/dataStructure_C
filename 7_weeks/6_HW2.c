#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

typedef struct {
    node *top;
} stack;

void init(stack* s) {
    s->top = NULL;
}

int is_empty(stack* s) {
    return (s->top == NULL);
}

void push(stack* s, int data) {
    node *ptr = (node*)malloc(sizeof(node));
    ptr->data = data;
    ptr->next = s->top;
    s->top = ptr;
}

int pop(stack* s) {
    if (is_empty(s)) {
        fprintf(stderr, "\n스택이 비어있습니다.\n");
        exit(1);
    }
    else {
        node *ptr = s->top;
        int data = ptr->data;
        s->top = s->top->next;
        printf("pop item : %d\n", ptr->data);
        free(ptr);
        return data;
    }
}

void print_stack(stack* s) {
    printf("\nHEAD->");
    for (node *p = s->top; p != NULL; p = p->next) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
}


int main() {
    stack A;
    init(&A);

    int choiceNum;
    int operationData;
    while(1) {
        printf("\n 리스트로 구현한 스택\n");
        printf(" 1. push\n");
        printf(" 2. pop\n");
        printf("-1. exit\n");
        printf("어떤 기능을 수행할까요? : ");
        scanf("%d", &choiceNum);

        switch(choiceNum) {
            case 1:
                printf("push item : ");
                scanf("%d", &operationData);
                push(&A, operationData);
                print_stack(&A);
                break;

            case 2:
                pop(&A);
                print_stack(&A);
                break;

            case -1:
                printf("\n종료합니다!\n");
                printf("최종 스택 리스트 : \n");
                print_stack(&A);
                exit(1);
        }
    }
}