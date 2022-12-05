#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 6

void allcosts(int cost[][MAX_VERTICES], int distance[][MAX_VERTICES], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            distance[i][j] = cost[i][j];
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (distance[i][k] + distance[k][j] < distance[i][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
}

int main() {
    int cost[][MAX_VERTICES] = 
        {{ 0, 50, 45, 10, 99999, 99999},
        { 99999, 0, 10, 15, 99999, 99999},
        { 99999, 99999, 0, 99999, 30, 99999},
        { 20, 99999, 99999, 0, 15, 99999},
        { 99999, 20, 35, 99999, 0, 99999},
        { 99999, 99999, 99999, 99999, 3, 0}};

    int distance[MAX_VERTICES][MAX_VERTICES], n = MAX_VERTICES;

    allcosts(cost, distance, n);
    printf("최단 경로 (모든 경로)\n");
    printf("All Path Distance : \n");
    printf("\t");
    for (int i = 0; i < MAX_VERTICES; i++) {
        printf("\t[ %d]", i);
    }
    printf("\n");
    for (int i = 0; i < MAX_VERTICES; i++) {
        printf("\t[ %d]\t", i);
        for (int j = 0; j < MAX_VERTICES; j++) {
            printf(" %d\t", distance[i][j]);
        }
        printf("\n");
    }
}