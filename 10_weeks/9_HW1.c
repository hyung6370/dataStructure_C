#include <stdio.h>
#include <stdlib.h>

typedef struct node *treePointer;
typedef struct node {
    int key;
    double value;
    treePointer lchild;
    treePointer rchild;
} node;

node* modified_search(node* tree, int key);
treePointer iterSearch(treePointer root, int key);
void preorder (treePointer ptr);
void inorder (treePointer ptr);
void insert(treePointer *root, int key, float value);

int inputKey;

int main() {
    treePointer n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12;
    treePointer head = NULL;
    
    n1 = (treePointer)malloc(sizeof(node));
    n1->key = 15;
    n1->value = 1 / (float)n1->key;
    insert(&head, n1->key, n1->value);

    n2 = (treePointer)malloc(sizeof(node));
    n2->key = 5;
    n2->value = 1 / (float)n2->key;
    insert(&head, n2->key, n2->value);

    n3 = (treePointer)malloc(sizeof(node));
    n3->key = 2;
    n3->value = 1 / (float)n3->key;
    insert(&head, n3->key, n3->value);

    n4 = (treePointer)malloc(sizeof(node));
    n4->key = 20;
    n4->value = 1 / (float)n4->key;
    insert(&head, n4->key, n4->value);

    n5 = (treePointer)malloc(sizeof(node));
    n5->key = 16;
    n5->value = 1 / (float)n5->key;
    insert(&head, n5->key, n5->value);

    n6 = (treePointer)malloc(sizeof(node));
    n6->key = 8;
    n6->value = 1 / (float)n6->key;
    insert(&head, n6->key, n6->value);

    n7 = (treePointer)malloc(sizeof(node));
    n7->key = 14;
    n7->value = 1 / (float)n7->key;
    insert(&head, n7->key, n7->value);

    n8 = (treePointer)malloc(sizeof(node));
    n8->key = 17;
    n8->value = 1 / (float)n8->key;
    insert(&head, n8->key, n8->value);

    n9 = (treePointer)malloc(sizeof(node));
    n9->key = 33;
    n9->value = 1 / (float)n9->key;
    insert(&head, n9->key, n9->value);

    n10 = (treePointer)malloc(sizeof(node));
    n10->key = 4;
    n10->value = 1 / (float)n10->key;
    insert(&head, n10->key, n10->value);

    n11 = (treePointer)malloc(sizeof(node));
    n11->key = 22;
    n11->value = 1 / (float)n11->key;
    insert(&head, n11->key, n11->value);

    n12 = (treePointer)malloc(sizeof(node));
    n12->key = 6;
    n12->value = 1 / (float)n12->key;
    insert(&head, n12->key, n12->value);

    while (1) {
        printf("생성된 이진 검색 트리에서 key값을 활용한 검색\n");
        printf("찾고자 하는 key 값을 입력하세요. : ");
        scanf("%d", &inputKey);
        if (inputKey == -1) {
            printf("\n종료합니다!\n");
            break;
        }
        iterSearch(head, inputKey);     
    }
}

node* modified_search(node* tree, int key) {
    for (node* ptr = tree; ptr != NULL;) {
        if (ptr->key == key)
            return NULL;
        
        if (key < ptr->key) {
            if (ptr->lchild == NULL) {
                return ptr;
            }
            else ptr = ptr->lchild;
        }
        else {
            if (ptr->rchild == NULL) {
                return ptr;
            }
            else ptr = ptr->rchild;
        }
    }
    return NULL;
}

treePointer iterSearch(treePointer root, int key) {
    int count = 0;
    while (root) {
        if (key == root->key) {
            printf("count : %d, key : %d의 value : %f\n\n", count, inputKey, root->value);
            return root;
        }
        if (key < root->key) {
            count++;
            root = root->lchild;
        }
        else {
            count++;
            root = root->rchild;
        }
        
    }
    printf("key : %d 노드가 없습니다.\n\n", inputKey);
    return NULL;
}

void preorder (treePointer ptr) {
    if (ptr) {
        printf("%d ", ptr->key);
        preorder(ptr->lchild);
        preorder(ptr->rchild);
    }
}

void inorder (treePointer ptr) {
    if (ptr) {
        inorder(ptr->lchild);
        printf("%d ", ptr->key);
        inorder(ptr->rchild);
    }
}

void insert(treePointer *root, int key, float value) {
    treePointer ptr;
    treePointer temp = modified_search(*root, key);

    if (temp || !(*root)) {
        ptr = (treePointer)malloc(sizeof(*ptr));
        ptr->key = key;
        ptr->value = value;
        ptr->lchild = ptr->rchild = NULL;

        if (*root) {
            if (key < temp->key)
                temp->lchild = ptr;
            else
                temp->rchild = ptr;
        }
        else *root = ptr;
    }
}

