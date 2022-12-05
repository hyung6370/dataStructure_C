#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// 그래프 초기화
void init(GraphType* g) {
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX_VERTICES; r++) {
        for (c = 0; c < MAX_VERTICES; c++) {
           g->adj_mat[r][c] = 99999;
           if (r == c) {
            g->adj_mat[r][c] = 0;
           }
        }
    }
}

//정점 삽입
void insert_vertex(GraphType* g, int v) {
    if (((g->n) + 1) > MAX_VERTICES){
        fprintf(stderr, "overflow");
        return;
    }
    g->n++;
}

//간선 삽입
void insert_edge(GraphType* g, int from, int to, int weight) {
    if (from >= g->n || to >= g->n){
        fprintf(stderr, "vertex key error");
        return;
    }
    g->adj_mat[from][to] = weight;
}

// 인접 행렬 출력 함수
void print_adj_mat(GraphType* g) {
    printf("\n인접 행렬을 이용한 그래프의 구성 : \n");
    printf("\t");
    for (int i = 0; i < g->n; i++) {
        printf("\t[ %d]", i);
    }
    printf("\n");
    for (int i = 0; i < g->n; i++){
        printf("\t[ %d]\t", i);
        for (int j = 0; j < g->n; j++){
            printf(" %d\t", g->adj_mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int nodeCount;
    int from, to, weight;
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    init(g);
    printf("인접 행렬 형태의 방향성 그래프 생성\n");
    printf("노드 수 (n) : ");
    scanf("%d", &nodeCount);

    for (int i = 0; i < nodeCount; i++) {
       insert_vertex(g, i);
    }

    while (1) {
        printf("에지 정보 (from to weight) : ");
        scanf("%d %d %d", &from, &to, &weight);
        if (from == -1 && to == -1 && weight == -1) {
            break;
        }
        insert_edge(g, from, to, weight);
    }
    print_adj_mat(g);
    free(g);
}