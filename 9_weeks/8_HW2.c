#include <stdio.h>
#include <stdlib.h>

typedef struct node *treePointer;
typedef struct node {
    int data;
    treePointer leftChild, rightChild;
} node;

treePointer make_tree_by_code() {
    treePointer n1, n2, n3, n4, n5;
    n1 = (treePointer)malloc(sizeof(node));
    n2 = (treePointer)malloc(sizeof(node));
    n3 = (treePointer)malloc(sizeof(node));
    n4 = (treePointer)malloc(sizeof(node));
    n5 = (treePointer)malloc(sizeof(node));

    n1->data = 5;
    n1->leftChild = n2;
    n1->rightChild = n3;

    n2->data = 3;
    n2->leftChild = n4;
    n2->rightChild = n5;

    n3->data = 8;
    n3->leftChild = NULL;
    n3->rightChild = NULL;

    n4->data = 1;
    n4->leftChild = NULL;
    n4->rightChild = NULL;

    n5->data = 4;
    n5->leftChild = NULL;
    n5->rightChild = NULL;

    return n1;
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

int equal(treePointer first, treePointer second) {
    // 두 이진트리가 동일하면 TRUE, 그렇지 않으면 FALSE 반환한다
    return ((!first && !second) || (first && second &&
            (first->data == second->data) &&
            equal(first->leftChild, second->leftChild) &&
            equal(first->rightChild, second->rightChild)));
}

treePointer copy (treePointer original) {
    treePointer temp;

    if (original) {
        temp = (treePointer)malloc(sizeof(node));
        temp->leftChild = copy(original->leftChild);
        temp->rightChild = copy(original->rightChild);
        temp->data = original->data;

        return temp;
    }
    return NULL;
}

void swap(treePointer original) {
    treePointer temp;
    if (original == NULL) return;
    swap(original->leftChild);
    swap(original->rightChild);
    temp = original->leftChild;
    original->leftChild = original->rightChild;
    original->rightChild = temp;
}

int main() {
    treePointer A, B, C;

    A = make_tree_by_code();

    printf("트리 구성 (A = make_tree_by_code())\n");
    printf("트리 순회(A)\n");
    printf("Inorder(A) : ");
    inorder(A);
    printf("\nPreorder(A) : ");
    preorder(A);
    printf("\nPostorder(A) : ");
    postorder(A);

    B = copy(A);
    printf("\n\n트리 복사 (B = copy(A))");
    printf("\n트리순회(B)");
    printf("\nInorder(B) : ");
    inorder(B);
    printf("\nPreorder(B) : ");
    preorder(B);
    printf("\nPostorder(B) : ");
    postorder(B);

    printf("\n\n트리 동질성 검사 (equal(A, B))");
    printf("\nequal(A, B) : ");
    if (equal(A, B)) {
        printf("TRUE");
    }
    else printf("FALSE");

    swap(A);
    C = A;
    printf("\n\n트리 swap (C = swap(A))");
    printf("\n트리순회 (C)");
    printf("\nInorder(C) : ");
    inorder(C);
    printf("\nPreorder(C) : ");
    preorder(C);
    printf("\nPostorder(C) : ");
    postorder(C);


    return 0;
}