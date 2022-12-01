#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50

typedef struct node {
    int data; // 정점
    struct node *next;
} node;

// 노드가 저장되는 리스트를 정의할 구조체
typedef struct type {
    int num;
    node* adj_list[MAX_VERTICES];
} type;

// 그래프 초기화
void init(type* g) {
    g->num = 0;

    for (int v = 0; v < MAX_VERTICES; v++) {
        g->adj_list[v] = NULL;
    }
}

// 정점 삽입 연산
void insert_vertex(type* g, int v) {
    if (((g->num) + 1) > MAX_VERTICES) {
        fprintf(stderr, "그래프 최대 정점 개수 초과!\n");
        return;
    }
    g->num++;
}

// 간선 삽입 연산, 정점 v를 정점 u의 인접 리스트에 삽입함
void insert_edge(type* g, int u, int v) {
    node* node;

    // 정점 u의 번호나 정점 v의 번호가 그래프 정점의 개수 이상일 때
    // 그래프의 정점의 개수가 num이면 간선의 개수는 num-1이다.
    if (u >= g->num || v >= g->num) {
        fprintf(stderr, "그래프 정점 번호 오류!\n");
    }

    // 새로운 노드 동적 생성, node에는 시작 메모리 주소가 저장
    node = (struct node*)malloc(sizeof(node));
    node->data = v;
    node->next = g->adj_list[u];
    g->adj_list[u] = node;
}

void print_adj_list(type* g) {
    printf("\n인접 리스트를 이용하여 구성한 그래프\n");
    int max_degree = 0;
    int max_vertex = 0;
    for (int i = 0; i < g->num; i++) {
        int degree = 0;
        node* p = g->adj_list[i];
        printf("[%d]:  ", i);
        while (p != NULL) {
            printf("%d -> ", p->data);
            p = p->next;
            degree++;
        }
        if (max_degree < degree) {
            max_degree = degree;
            max_vertex = i;
        }
        printf("end");
        printf("\n");
    }
    printf("\n");
    printf("degree가 가장 큰 노드와 degree 값 : 노드 %d, degree %d\n", max_vertex, max_degree);
    printf("노드 %d와 연결된 노드들 : ", max_vertex);
    node* p = g->adj_list[max_vertex];
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("end");
    printf("\n");
}

int main() {
    type *graph;
    graph = (type *)malloc(sizeof(type));

    init(graph);

    int v_num;
    printf("노드 개수(n) : ");
    scanf("%d", &v_num);
    for (int i = 0; i < v_num; i++) {
        insert_vertex(graph, i);
    }

    while (1) {
        int x, y;
        printf("에지 정보(vi vj) : ");
        scanf("%d %d", &x, &y);
        if (x == -1 && y == -1) {
            break;
        }

        insert_edge(graph, x, y);
        insert_edge(graph, y, x);
    }
    print_adj_list(graph);
    free(graph);
    return 0;
}
