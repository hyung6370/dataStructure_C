#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 10

int queue[MAX_QUEUE_SIZE];
int front = 4;
int rear = 4;

int c_qFull() {
    if (front == rear) {
        printf("큐가 꽉 찼습니다. dequeue하고 다시 시도해주세요.");
        return 1;
    }
    else return 0;
}

int c_qEmpty() {
    if (front == rear) {
        printf("큐에 더이상 들어있는 데이터가 없습니다.\n");
        return 1;
    }
    else return 0;
}

void add_cq(int item) {
    rear = (rear+1) % MAX_QUEUE_SIZE;
    if (front == rear) {
        c_qFull();
    }
    else {
        queue[rear] = item;
    }
}

int delete_cq() {
    if (front == rear) {
        return c_qEmpty();
    }
    else {
        front = (front+1) % MAX_QUEUE_SIZE;
        return queue[front];
    }
}

void printQueue() {
    printf("    index : item\n");
    for (int i = front+1; i <= rear; i++) {
        printf("\t%d :  %d\n", i, queue[i]);
    }
    printf("\n");
}

int main() {
    int choiceNum;
    int addQItem;
    int deleteQItem;

    while(1) {
        printf("원형 큐 - 1.addQ 2.deleteQ -1.exit : ");
        scanf("%d", &choiceNum);
        if (choiceNum == 1) {
            printf("addQ item : ");
            scanf("%d", &addQItem);
            add_cq(addQItem);
            printQueue();
        }
        else if (choiceNum == 2) {
            printf("deleteQ item : ");
            scanf("%d", &deleteQItem);
            delete_cq();
            printQueue();
        }
        else if (choiceNum == -1) {
            printf("\n- 종료합니다.-\n\n");
            printf("현재 큐 데이터\n");
            printQueue();
            break;
        }
    }
}