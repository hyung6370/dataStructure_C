#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

typedef struct {
    node *front;
    node *rear;
    int count;
} queue;

void init(queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
}

int is_empty(queue* q) {
    return (q->count == 0);
}

void add_q(queue* q, int data) {
    node *ptr = (node*)malloc(sizeof(node));
    ptr->data = data;
    ptr->next = NULL;
    if (is_empty(q)) {
        q->front = ptr;
    }
    else {
        q->rear->next = ptr;
    }
    q->rear = ptr;
    q->count++;
}

int delete_q(queue* q) {
    if (is_empty(q)) {
        fprintf(stderr, "\n큐가 비어있습니다.\n");
        exit(1);
    }
    else {
        node *ptr = q->front;
        int data = ptr->data;
        q->front = ptr->next;
        printf("deleteq item : %d\n", ptr->data);
        free(ptr);
        q->count--;
        return data;
    }
}

void print_queue(queue* q) {
    printf("\nHEAD->");
    for (node *p = q->front; p != NULL; p = p->next) {
        printf("%d->", p->data);
    }
    // node *p = q->front;
    // while (p != NULL) {
    //     printf("%d->", p->data);
    //     p = p->next;
    // }
    printf("NULL\n");
}

int main() {
    queue A;
    init(&A);

    int choiceNum;
    int operationData;
    while(1) {
        printf("\n 리스트로 구현한 큐\n");
        printf(" 1. addq\n");
        printf(" 2. deleteq\n");
        printf("-1. exit\n");
        printf("어떤 기능을 수행할까요? : ");
        scanf("%d", &choiceNum);

        switch(choiceNum) {
            case 1:
                printf("addq item : ");
                scanf("%d", &operationData);
                add_q(&A, operationData);
                print_queue(&A);
                break;
            
            case 2:
                delete_q(&A);
                print_queue(&A);
                break;

            case -1:
                printf("\n종료합니다!\n");
                printf("최종 큐 리스트 : \n");
                print_queue(&A);
                exit(1);
        }
    }
}