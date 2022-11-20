#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct node *treePointer;
typedef struct node {
    int key;
    double value;
    treePointer lchild;
    treePointer rchild;
} node;

int count_node (treePointer ptr);
int count_depth (treePointer ptr);
int count_leaf (treePointer ptr);
node* modified_search(node* tree, int key);
void insert(treePointer *root, int key, float value);
treePointer newNode(int key, float value);
treePointer make_bst(int n);

int main() {
    int inputNumOfNodes;
    treePointer A = NULL;
    int countNode;
    int countDepth;
    int countLeaf;

    while (1) {
        time_t start = time(NULL);
        printf("n개의 노드를 가진 이진검색 트리 생성 (n) : ");
        scanf("%d", &inputNumOfNodes);

        if (inputNumOfNodes == -1) {
            printf("\n종료합니다!\n");
            break;
        }

        printf("이진검색트리 B : \n");
        printf("(key,\t\tvalue)\n");

        A = make_bst(inputNumOfNodes);

        time_t end = time(NULL);    
        printf("이진검색트리 B의 생성시간 : %lf\n", (double)(end - start));

        countNode = count_node(A);
        printf("이진검색트리 B의 노드 수 : %d\n", countNode);

        countDepth = count_depth(A);
        printf("이진검색트리 B의 높이(깊이) : %d\n", countDepth);

        countLeaf = count_leaf(A);
        printf("이진검색트리 B의 단말노드 수 : %d\n\n", countLeaf);
    }
}

int count_node (treePointer ptr) {
    int count = 0;
    if (ptr != NULL) {
        count = 1 + count_node(ptr->lchild) + count_node(ptr->rchild);
    }
    return count;
}

int count_depth (treePointer ptr) {
    int depth = 0;
    if (ptr != NULL) {
        depth = 1 + MAX(count_depth(ptr->lchild), count_depth(ptr->rchild));
    }
    return depth;
}

int count_leaf (treePointer ptr) {
    int count = 0;
    if (ptr == NULL) {
        return 0;
    }
    else if (ptr->lchild == NULL && ptr->rchild == NULL) {
        return 0;
    }
    else {
        count += 1 + count_leaf(ptr->lchild) + count_leaf(ptr->rchild);
    }
    return count;
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

treePointer newNode(int key, float value) {
    treePointer temp = (treePointer)malloc(sizeof(node));
    temp->key = key;
    temp->value = value;
    temp->lchild = temp->rchild = NULL;
    return temp;
}

treePointer make_bst(int n) {
    int *keys = (int *)malloc(sizeof(int) * n);
    float *values = (float *)malloc(sizeof(float) * n);

    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        keys[i] = ((rand() % n + 1) / (0x7fff * 1.0)) * 100000000;
        for (int j = 0; j < i; j++) {
            if (keys[i] == keys[j]) {
                i--;
                break;
            }
        }
        values[i] = 1 / (float)keys[i];
    }

    treePointer A = NULL;
    treePointer head = NULL;

    for (int i = 0; i < n; i++) {
        head = newNode(keys[i], values[i]);
        insert(&A, head->key, head->value);
        
        printf("(%d,\t\t%f)\n", head->key, head->value);
    }
    return A;
}