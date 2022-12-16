#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct node *treePointer;
typedef struct node {
    int key;
    char value;
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
treePointer iterSearch(treePointer root, int key);
void deleteNode(treePointer root, int key);

int inputKey;

int main() {
    int inputNumOfNodes;
    treePointer A = NULL;
    int countNode;
    int countDepth;
    int countLeaf;

    printf("  문제 1. 이진 검색 트리 \n");
    printf("트리 생성 후 검색, 삭제 연산이 가능합니다!\n\n");

    printf("n개의 노드를 가진 이진 검색 트리 생성 (n) : ");
        scanf("%d", &inputNumOfNodes);
        
        A = make_bst(inputNumOfNodes);

        countNode = count_node(A);
        printf("이진검색트리 B의 노드 수 : %d\n", countNode);

        countDepth = count_depth(A);
        printf("이진검색트리 B의 높이(깊이) : %d\n", countDepth);

        countLeaf = count_leaf(A);
        printf("이진검색트리 B의 단말노드 수 : %d\n\n", countLeaf);

    while (1) {
        int choiceMenu;
        printf("1. 검색, 2. 삭제, -1.종료 : ");
        scanf("%d", &choiceMenu);
        if (choiceMenu == -1) {
            printf("\n종료합니다!\n");
            break;
        }
        if (choiceMenu == 1) {
            printf("생성된 이진 검색 트리에서 key값을 활용한 검색\n\n");
            printf("찾고자 하는 key 값을 입력하세요. : ");
            scanf("%d", &inputKey);
            if (inputKey == -1) {
                printf("\n종료합니다!\n");
                break;
            }
            iterSearch(A, inputKey);
        }
        else if (choiceMenu == 2) {
            printf("생성된 이진 검색 트리에서 key값을 활용한 삭제\n\n");
            printf("제거할 key 값을 입력하세요. : ");
            scanf("%d", &inputKey);
            if (inputKey == -1) {
                printf("\n종료합니다!\n");
                break;
            }
            deleteNode(A, inputKey);
        }     
    }
}

treePointer iterSearch(treePointer ptr, int key) {
    int count = 0;
    while (ptr) {
        if (key == ptr->key) {
            printf("count : %d, key : %d의 value : %c\n\n", count, inputKey, ptr->value);
            return ptr;
        }
        if (key < ptr->key) {
            count++;
            ptr = ptr->lchild;
        }
        else {
            count++;
            ptr = ptr->rchild;
        }
        
    }
    printf("key : %d 노드가 없습니다.\n\n", inputKey);
    return NULL;
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

void deleteNode(treePointer root, int key) {
    treePointer parent, p, succ, succ_parent;
    treePointer child;
    parent = NULL;
    p = root;

    while ((p != NULL) && (p->key != key)) {
        parent = p;
        if (key < p->key) p = p->lchild;
        else p = p->rchild;
    }

    if (p == NULL) {
        printf("삭제하려는 key가 트리에 없습니다.\n");
    }

    if ((p->lchild == NULL) && (p->rchild == NULL)) {
        if (parent != NULL) {
            if (parent->lchild == p) parent->lchild = NULL;
            else parent->rchild = NULL;
        }
        else {
            root = NULL;
        }
        printf("Key %d 삭제 완료\n", key);
    }
    else if ((p->lchild == NULL) || (p->rchild == NULL)) {
        if (p->lchild != NULL) child = p->lchild;
        else child = p->rchild;

        if (parent != NULL) {
            if (parent->lchild == p) parent->lchild = child;
            else parent->rchild = child;
        }
        else root = child;

        printf("Key %d 삭제 완료\n", key);
    }
    else {
        succ_parent = p;
        succ = p->lchild;
        
        while (succ->rchild != NULL) {
            succ_parent = succ;
            succ = succ->rchild;
        }
        
        if (succ_parent->lchild == succ) succ_parent->lchild = succ->lchild;
        else succ_parent->rchild = succ->lchild;
        p->key = succ->key;
        p = succ;

        printf("Key %d 삭제 완료\n", key);
    }
    free(p);
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
    char *values = (char *)malloc(sizeof(char) * n);

    int inputKey;
    char inputData;

    printf("\n");
    for (int i = 0; i < n; i++) {
        printf(" Key, Data 입력 : ");
        scanf("%d %c", &inputKey, &inputData);
        keys[i] = inputKey;
        values[i] = inputData;

        for (int j = 0; j < i; j++) {
            if (keys[i] == keys[j] || values[i] == values[j]) {
                i--;
                printf("\nkey 또는 data에 중복된 값이 있습니다!\n");
                printf("다시 입력해주세요.\n");
                break;
            }
        }
    }
    

    treePointer A = NULL;
    treePointer head = NULL;

    printf("\n");
    printf("(Key,\tData\n");
    for (int i = 0; i < n; i++) {
        head = newNode(keys[i], values[i]);
        insert(&A, head->key, head->value);
        
        printf("(%d,\t%c)\n", head->key, head->value);
    }
    return A;
}