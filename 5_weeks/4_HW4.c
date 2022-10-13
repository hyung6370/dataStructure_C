#include <stdio.h>
#include <stdlib.h>

typedef int elememt_stack;
typedef struct {
    elememt_stack* stackData;
    int capacity_stack;
    int top;
} Stack;

typedef int elememt_queue;
typedef struct {
    elememt_queue* queueData;
    int capacity_queue;
    int front;
    int rear;
} Queue;


void init_stack(Stack* s) {
    s->top = -1;
    s->capacity_stack = 2;
    s->stackData = (elememt_stack*)malloc(s->capacity_stack * sizeof(elememt_stack));
}

void init_queue(Queue* q) {
    q->front = 0;
    q->rear = 0;
    q->capacity_queue = 2;
    q->queueData = (elememt_queue*)malloc(q->capacity_queue * sizeof(elememt_queue));
}

int stackFull(Stack* s) {
    return (s->top == (s->capacity_stack - 1));
}

void queueFull(Queue* q) {
    printf("\n큐가 꽉 찼습니다. 배열 크기를 재할당 하겠습니다.\n");
    printf("-- 재할당 중.. --\n");
    elememt_queue* newQueue;

    newQueue = (elememt_queue *)malloc(sizeof(2 * q->capacity_queue * sizeof(q->queueData)));
    int start = (q->front + 1) % q->capacity_queue;

    if (start < 2) {
        for (int i = 0; i < q->capacity_queue - 1; i++) {
            newQueue[i] = q->queueData[start + i];
        }
    }
    else {
        for (int i = 0; i < q->capacity_queue - start; i++) {
            newQueue[i] = q->queueData[start + i];
        }
        for  (int i = 0; i < q->rear; i++) {
            newQueue[q->capacity_queue - start + i] = q->queueData[i];
        }
    }
    q->front = 2 * q->capacity_queue - 1;
    q->rear = q->capacity_queue - 1;
    q->capacity_queue *= 2;
    free(q->queueData);
    q->queueData = newQueue;
    
    printf("-- 재할당 완료 --\n");
}

int stackEmpty(Stack* s) {
    return (s->top == -1);
}

int queueEmpty(Queue* q) {
    return (q->front == q->rear);
}

void push(Stack* s, elememt_stack item) {
    if (stackFull(s)) {
        printf("\n스택이 꽉 찼습니다. 배열 크기를 재할당 하겠습니다.\n");
        printf("-- 재할당 중.. --\n");
        s->capacity_stack *= 2;
        s-> stackData = (elememt_stack*)realloc(s->stackData, 2 * s->capacity_stack * sizeof(elememt_stack));
        printf("-- 재할당 완료 --\n");
    }
    s->stackData[++(s->top)] = item;
}

elememt_stack pop(Stack* s) {
    if (stackEmpty(s)) {
        fprintf(stderr, "스택에 더이상 들어있는 데이터가 없습니다.\n");
        exit(1);
    }
    else return (s->stackData[(s->top)--]);
}

void addQueue(Queue* q, elememt_queue item) {
    q->rear = (q->rear + 1) % q->capacity_queue;
    if (q->rear == q->front) {
        queueFull(q);
    }
    q->queueData[q->rear] = item;
}

elememt_queue deleteQueue(Queue* q, elememt_queue item) {
    if (queueEmpty(q)) {
        fprintf(stderr, "큐에 더이상 들어있는 데이터가 없습니다.\n");
        exit(1);
    }
    else {
        q->front = (q->front+1) % q->capacity_queue;
        return q->queueData[q->front];
    }
}

void printStack(Stack* s) {
    printf("    index : item\n");
    for (int i = 0; i <= s->top; i++) {
        printf("\t%d :  %d\n", i, s->stackData[i]);
    }
    printf("\n");
}

void printQueue(Queue* q) {
    printf("    index : item\n");
    for (int i = q->front+1; i <= q->rear; i++) {
        printf("\t%d :  %d\n", i, q->queueData[i]);
    }
    printf("\n");
}

int main() {
    int firstChoiceNum;
    int choiceNum;
    int pushItem;
    int popItem;
    int addQItem;
    int deleteQItem;

    Stack s;
    Queue q;
    init_stack(&s);
    init_queue(&q);

    printf("선택 - 1.스택 2.큐 : ");
    scanf("%d", &firstChoiceNum);
    if (firstChoiceNum == 1) {
        while(1) {
            printf("스택 - 1.push 2.pop -1.exit : ");
            scanf("%d", &choiceNum);
            if (choiceNum == 1) {
                printf("push item : ");
                scanf("%d", &pushItem);
                push(&s, pushItem);
                printStack(&s);
            }
            else if (choiceNum == 2) {
                printf("pop item : ");
                scanf("%d", &popItem);
                pop(&s);
                printStack(&s);
            }
            else if (choiceNum == -1) {
                printf("\n- 종료합니다.-\n\n");
                printf("현재 스택 데이터\n");
                printStack(&s);
                break;
            }
        }
    }
    else if (firstChoiceNum == 2) {
        while(1) {
            printf("원형 큐 - 1.addQ 2.deleteQ -1.exit : ");
            scanf("%d", &choiceNum);
            if (choiceNum == 1) {
                printf("addQ item : ");
                scanf("%d", &addQItem);
                addQueue(&q, addQItem);
                printQueue(&q);
            }
            else if (choiceNum == 2) {
                printf("deleteQ item : ");
                scanf("%d", &deleteQItem);
                deleteQueue(&q, deleteQItem);
                printQueue(&q);
            }
            else if (choiceNum == -1) {
                printf("\n- 종료합니다.-\n\n");
                printf("현재 큐 데이터\n");
                printQueue(&q);
                break;
            }
        }
    }
}