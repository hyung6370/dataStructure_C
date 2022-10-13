#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
    int group;
    double distance;
} clust;

int Len;
clust *Data;
clust *clustCenterPoint;

void draw(int centerCnt) {
    for (int i = 0; i < centerCnt; i++) {
        printf("        클러스터 %d 중심점 = (%lf, %lf)\n", i, clustCenterPoint[i].x, clustCenterPoint[i].y);
    }
}

double distance(double x1, double y1, double x2, double y2) { return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)); }

void initializePoint(int centerCnt) {
    clust MaxDistancePoint = {0, 0, 0, 0};

    for (int i = 0; i < Len; i++) {
        Data[i].distance = 1e9;
        for (int centerIdx = 0; centerIdx < centerCnt; centerIdx++) {
            double tempDistance =
                    distance(Data[i].x, Data[i].y, clustCenterPoint[centerIdx].x, clustCenterPoint[centerIdx].y);
            Data[i].distance = (Data[i].distance > tempDistance) ? tempDistance : Data[i].distance;
        }
        MaxDistancePoint = (MaxDistancePoint.distance > Data[i].distance) ? MaxDistancePoint : Data[i];
    }
    clustCenterPoint[centerCnt] = MaxDistancePoint;
}

void clustering(int centerCnt) {
    for (int i = 0; i < centerCnt; i++) {
        clustCenterPoint[i].group = 0;
        clustCenterPoint[i].distance = 0;
    }
    for (int idx = 0; idx < Len; idx++) {
        Data[idx].distance = 1e9;
        for (int centerIdx = 0; centerIdx < centerCnt; centerIdx++) {
            double tempDistance =
                    distance(Data[idx].x, Data[idx].y, clustCenterPoint[centerIdx].x, clustCenterPoint[centerIdx].y);
            if (Data[idx].distance > tempDistance) {
                Data[idx].distance = tempDistance;
                Data[idx].group = centerIdx;
            }
        }
        clustCenterPoint[Data[idx].group].group += 1;
        if (clustCenterPoint[Data[idx].group].distance < Data[idx].distance) {
            clustCenterPoint[Data[idx].group].distance = Data[idx].distance;
        }
    }
}

int sameClustCenterPoint(clust *prev, clust *current, int clusterNum) {
    for (int i = 0; i < clusterNum; i++) {
        if ((prev[i].x != current[i].x) || (prev[i].y != current[i].y)) {
            return 0;
        }
    }
    return 1;
}

void relocationCenter(int centerCnt) {
    for (int i = 0; i < centerCnt; i++) {
        clustCenterPoint[i].x = 0;
        clustCenterPoint[i].y = 0;
    }
    for (int idx = 0; idx < Len; idx++) {
        clustCenterPoint[Data[idx].group].x += Data[idx].x;
        clustCenterPoint[Data[idx].group].y += Data[idx].y;
    }
    for (int i = 0; i < centerCnt; i++) {
        clustCenterPoint[i].x /= clustCenterPoint[i].group;
        clustCenterPoint[i].y /= clustCenterPoint[i].group;
    }
}

void readFile(char *FileName) {

    FILE *fp = fopen(FileName, "r");
    if (fp == NULL) {
        printf("Wrong Input : %s\n", FileName);
        return;
    }
    fscanf(fp, "%d", &Len);

    Data = (clust *)malloc(sizeof(clust) * Len);
    for (int i = 0; i < Len; i++) {
        fscanf(fp, "%lf %lf", &Data[i].x, &Data[i].y);
    }
    fclose(fp);
}

void solve(int centerClustNumber) {
    int clusterNum = centerClustNumber;
    clustCenterPoint = (clust *)malloc(sizeof(clust) * clusterNum);

    Data[0].group = 1;
    clustCenterPoint[0] = Data[0];
    for (int i = 1; i < clusterNum; i++) {
        initializePoint(i);
    }

    printf("초기 클러스터의 구성:\n");
    draw(clusterNum);
    clustering(clusterNum);

    int loopCnt = 1;
    clust *prev = (clust *)malloc(sizeof(clust) * clusterNum);

    while (1) {

        for (int i = 0; i < clusterNum; i++) {
            prev[i].x = clustCenterPoint[i].x;
            prev[i].y = clustCenterPoint[i].y;
        }
        relocationCenter(clusterNum);

        if (sameClustCenterPoint(prev, clustCenterPoint, clusterNum)) {
            break;
        }

        printf("%d번째 클러스터 구성:\n", ++loopCnt);
        draw(clusterNum);
        clustering(clusterNum);
    }

    printf("### 클러스터 구성 완료!! : 반복 횟수 = %d\n", loopCnt);
    for (int i = 0; i < clusterNum; i++) {
        printf("        클러스터 %d 중심점 = (%lf, %lf), point 수 = %d, 최장 거리 = %lf\n", i, clustCenterPoint[i].x,
               clustCenterPoint[i].y, clustCenterPoint[i].group, clustCenterPoint[i].distance);
    }

    free(prev);
}

int main() {
    char *FILENAME = (char *)malloc(sizeof(char) * 100);
    int clusterNum;

    printf("파일 이름과 k 값을 입력하세요: ");
    scanf("%s %d", FILENAME, &clusterNum);

    readFile(FILENAME);
    solve(clusterNum);

    free(FILENAME);
    free(Data);
    free(clustCenterPoint);
    return 0;
}