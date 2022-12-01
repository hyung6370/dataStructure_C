#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 100
short int visited[MAX_VERTICES];

typedef struct node {
	int vertex;
	struct node *link;
} node;
typedef struct node *nodePointer;
nodePointer graph[MAX_VERTICES];

// 노드가 저장되는 리스트를 정의할 구조체
typedef struct type {
    int num;
    node* adj_list[MAX_VERTICES];
} type;

typedef struct queue {
	int element[MAX_VERTICES];
	int front, rear;
	int size;
} queue;

void init_queue(queue* q) {
	q->size = 0;
	q->front = -1;
	q->rear = -1;
	for (int i = 0; i < MAX_VERTICES; i++) {
		q->element[i] = 0;
	}
}

void addq(queue* q, int item) {
	q->element[++(q->rear)] = item;
	q->size++;
}

int deleteq(queue* q) {
	int item;
	item = q->element[++(q->front)];
	q->size--;
	return item;
}

void dfs(type* g, int v) {
	node *w;
	visited[v] = TRUE;
	printf("%d ", v);
	for (w = g->adj_list[v]; w; w = w->link) {
		if (!visited[w->vertex]) {
			dfs(g, w->vertex);
		}
	}
}

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
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

void bfs(type* g, int v) {
	node *w;
	queue q;
	init_queue(&q);
	visited[v] = TRUE;
	printf("%d ", v);

	addq(&q, v);
	while(q.size != 0) {
		v = deleteq(&q);
		for (w = g->adj_list[v]; w; w = w->link) {
			if (!visited[w->vertex]) {
				visited[w->vertex] = TRUE;
				printf("%d ", w->vertex);
				addq(&q, w->vertex);
			}
		}
	}
}

void print_adj_list(type* w, int i) {
	node *temp;

	printf("\n\n");
	printf("%d 노드의 인접리스트 : ", i);

	for (temp = w->adj_list[i]; temp; temp = temp->link) {
		printf("%d -> ", temp->vertex);
	}
}

int main() {
	type graph;
	init(&graph);
	for (int i = 0; i < 7; i++) {
		insert_vertex(&graph, i);
	}

	insert_edge(&graph, 0, 1);
	insert_edge(&graph, 5, 0);
	insert_edge(&graph, 3, 4);
	insert_edge(&graph, 5, 4);
	insert_edge(&graph, 2, 5);
	insert_edge(&graph, 1, 2);
	insert_edge(&graph, 5, 1);
	insert_edge(&graph, 1, 3);
	insert_edge(&graph, 2, 3);
	insert_edge(&graph, 3, 5);
	insert_edge(&graph, 0, 4);
	int choiceMenu;
	printf("탐색 알고리즘(1.DFS, 2.BFS) 선택 : ");
	scanf("%d", &choiceMenu);
	printf("\n");
	if (choiceMenu == 1) {
		int startDFS;
		printf("깊이 우선 탐색 (DFS)\n");
		printf("시작 노드 번호 입력 : ");
		scanf("%d", &startDFS);
		dfs(&graph, startDFS);
	}
	else if (choiceMenu == 2) {
		int startBFS;
		printf("깊이 우선 탐색 (BFS)\n");
		printf("시작 노드 번호 입력 : ");
		scanf("%d", &startBFS);
		bfs(&graph, startBFS);
	}
	else {
		printf("잘못 입력하셨습니다!\n");
		printf("종료합니다\n");
	}
}

