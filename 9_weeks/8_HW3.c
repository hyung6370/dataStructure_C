#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node *treePointer;
typedef struct node {
    int data;
    treePointer leftChild, rightChild;
} node;

int* findData(int inputNum) {
    int *data = (int *)malloc(sizeof(int) * inputNum);

    srand((unsigned int)time(NULL));
    for (int i = 0; i < inputNum; i++) {
        data[i] = rand() % inputNum + 1;
        for (int j = 0; j < i; j++) {
            if (data[i] == data[j]) {
                i--;
                break;
            }
        }
    }
    return data;
}

treePointer newNode(int item) {
    treePointer temp = (treePointer)malloc(sizeof(node));
    temp->data = item;
    temp->leftChild = temp->rightChild = NULL;
    return temp;
}

// 이진 탐색 트리
// treePointer traversal(treePointer ptr, int data) {
//     if (ptr == NULL) return newNode(data);    

//     if (data < ptr->data) {
//         ptr->leftChild = traversal(ptr->leftChild, data);
//     }
//     else ptr->rightChild = traversal(ptr->rightChild, data);
    
//     return ptr;
// }

treePointer traversal(treePointer ptr, int data) {
    if (ptr == NULL) return newNode(data);    

    if (data % 2 == 0) {
        ptr->leftChild = traversal(ptr->leftChild, data);
    }
    else if (data % 2 == 1) {
        ptr->rightChild = traversal(ptr->rightChild, data);
    }
    return ptr;
}

void inorder (treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%d ", ptr->data);
        inorder(ptr->rightChild);
    }
}

void preorder (treePointer ptr) {
    if (ptr) {
        printf("%d ", ptr->data);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

void postorder (treePointer ptr) {
    if (ptr) {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%d ", ptr->data);
    }
}

int main() {
    printf("랜덤 트리 자동 생성 (D)\n");
    treePointer A = NULL;

    int inputNum;
    printf("Input n : ");
    scanf("%d", &inputNum);

    int *data = findData(inputNum);
    for (int i = 0; i < inputNum; i++) {
        A = traversal(A, data[i]);
    }
    printf("\n생성한 랜덤 데이터 : ");
    for (int i = 0; i < inputNum; i++) {
        printf("%d ", data[i]);
    }

    printf("\n트리 순회 (D)\n");
    printf("Inorder : ");
    inorder(A);

    printf("\nPreorder : ");
    preorder(A);

    printf("\nPostorder : ");
    postorder(A);
    printf("\n");
    return 0;
}