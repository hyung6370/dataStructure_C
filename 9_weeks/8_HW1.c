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

int main() {
    treePointer a;
    a = make_tree_by_code();
    printf("Inorder : ");
    inorder(a);

    printf("\nPreorder : ");
    preorder(a);

    printf("\nPostorder : ");
    postorder(a);

    return 0;
}