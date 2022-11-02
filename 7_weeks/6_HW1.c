#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

node* insert_front(node *head, int data) {
    node *ptr;
    ptr = (node*)malloc(sizeof(node));
    ptr->data = data;
    ptr->next = head;
    head = ptr;
    return head;
}

node* insert_last(node *head, int data) {
    node *ptr;
    ptr = head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr->next = (node*)malloc(sizeof(node));
    ptr->next->data = data;
    ptr->next->next = NULL;
    return head;
}

node* search(node *head, int data) {
    int nodeNum = 0;
    node *ptr;
    ptr = head;
    if (ptr->next == NULL) {
        return NULL;
    }
    else {
        while (ptr->next != NULL) {
            if (ptr->data == data) {
                printf("\n노드번호 : %d\n", nodeNum);
                return ptr;
            }
            else {
                nodeNum++;
                ptr = ptr->next;
            }
            if (ptr->next == NULL) {
                printf("\n찾는 데이터가 없습니다!\n");
            }
        }
        return NULL;
    }
}

node* invert(node *head) {
    node *pre = NULL;
    node *cur = head;

    while (cur != NULL) {
        node *next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    head = pre;
    return head;
}

node* delete_front(node *head) {
    node *ptr = NULL;
    if (head != NULL) {
        ptr = head;
        head = ptr->next;
    }
    printf("삭제 데이터 : %d\n", ptr->data);
    free(ptr);
    return head;
}

node* delete_(node *head, int data) {
    node *ptr;
    ptr = head;
    if (ptr->next == NULL) {
        return NULL;
    }
    else {
        while (ptr->next != NULL) {
            if (ptr->data == data) {
                node *temp = ptr; // 삭제할 데이터 temp에 넣어주고, 
                if (temp == NULL) return NULL;
                if (head == temp) head = temp->next;
                else {
                    node* cur = head;
                    while (cur->next != temp) {
                        cur = cur->next;
                    }
                    cur->next = temp->next;
                }
                temp->next = NULL;
                return temp;
                free(temp);
            }
            else {
                ptr = ptr->next;
            }
            if (ptr->next == NULL) {
                printf("\n찾는 데이터가 없습니다!\n");
            }
        }
        return NULL;
    }
}



void print_list(node* head) {
    node *ptr = NULL;
    ptr = head;
    printf("\nHEAD->");
    while (ptr != NULL) {
        printf("%d->", ptr->data);
        ptr = ptr->next;
    }
    printf("NULL\n\n");
}

int main() {
    node* A = NULL;

    int choiceNum;
    int operationData;
    while(1) {
        printf("\n 리스트 기본연산\n");
        printf(" 0. print list\n");
        printf(" 1. insert_front\n");
        printf(" 2. insert_last\n");
        printf(" 3. delete_front\n");
        printf(" 4. delete_\n");
        printf(" 5. search\n");
        printf(" 6. invert\n");
        printf("-1. exit\n");
        printf("어떤 기능을 수행할까요? : ");
        scanf("%d", &choiceNum);

        switch(choiceNum) {
            case 0:
                print_list(A);
                break;

            case 1:
                printf("데이터 : ");
                scanf("%d", &operationData);
                A = insert_front(A, operationData);
                print_list(A);
                break;

            case 2:
                printf("데이터 : ");
                scanf("%d", &operationData);
                A = insert_last(A, operationData);
                print_list(A);
                break;

            case 3:
                A = delete_front(A);
                print_list(A);
                break;

            case 4:
                printf("삭제 데이터 : ");
                scanf("%d", &operationData);
                delete_(A, operationData);
                print_list(A);
                break;

            case 5:
                printf("데이터 : ");
                scanf("%d", &operationData);
                search(A, operationData);
                print_list(A);
                break;

            case 6:
                printf("역순 데이터 : ");
                A = invert(A);
                print_list(A);
                break;

            case -1:
                printf("\n종료합니다!\n");
                printf("최종 리스트 : ");
                print_list(A);
                exit(1);
        }
    }
}