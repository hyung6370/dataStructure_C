#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 6
#define INT_MAX 100000

int choose(int distance[], int n, short int found[]) {
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void shortestPath(int v, int cost[][MAX_VERTICES], int distance[], int n, short int found[]) {
    int i, u, w;
    for (i = 0; i < n; i++) {
        found[i] = FALSE;
        distance[i] = cost[v][i];
    }
    found[v] = TRUE;
    distance[v] = 0;
    for (i = 0; i < n-2; i++) {
        u = choose(distance, n, found);
        found[u] = TRUE;
        for (w = 0; w < n; w++) {
            if (!found[w]) {
                if (distance[u] + cost[u][w] < distance[w]) {
                    distance[w] = distance[u] + cost[u][w];
                }
            }
        }
    }
}

int main() {
    int startNode;
    int cost[][MAX_VERTICES] = 
        {{ 0, 50, 45, 10, 99999, 99999},
        { 99999, 0, 10, 15, 99999, 99999},
        { 99999, 99999, 0, 99999, 30, 99999},
        { 20, 99999, 99999, 0, 15, 99999},
        { 99999, 20, 35, 99999, 0, 99999},
        { 99999, 99999, 99999, 99999, 3, 0}};

    int distance[MAX_VERTICES], n = MAX_VERTICES;
    short int found[MAX_VERTICES];

    printf("최단 경로 (단일 출발점)\n");
    while (1) {
        printf("시작 노드 (v) : ");
        scanf("%d", &startNode);
        if (startNode == -1) { 
            printf("종료합니다!\n");
            break;
        }
        printf("Distance : ");
        shortestPath(startNode, cost, distance, n, found);
        for (int i = 0; i < MAX_VERTICES; i++) {
            printf("%d  ", distance[i]);
        }
        printf("\n");
    }
}