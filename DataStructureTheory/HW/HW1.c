#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 1500

struct point {
    int num;
    int kNum;
    int count;
    double pointX[MAX_SIZE];
    double pointY[MAX_SIZE];
    double center_point_X[MAX_SIZE];
    double center_point_Y[MAX_SIZE];
};

struct point p;

void file_read();
double op_distance(double x1, double y1, double x2, double y2);
void find_center_points(double x1, double y1, double x2, double y2);

int main() {
    char file_name[30];
    p.count = 0;

    double init_xy_distance;
    double distance[1000];
    double farthest = distance[0];
    double second_pointX;
    double second_pointY;

    printf("파일 이름과 k 값을 입력하세요: ");
    scanf("%s", file_name, sizeof(file_name));    
    scanf(" %d", &p.kNum);
	file_read();

    double init_pointX = p.pointX[1];
    double init_pointY = p.pointY[1];

    for (int i = 1; i <= p.num; i++) {
        init_xy_distance = sqrt(pow(p.pointX[i] - init_pointX, 2) + pow(p.pointY[i] - init_pointY, 2));
        distance[i] = init_xy_distance;
        if (distance[i] > farthest) {
            farthest = distance[i];
            second_pointX = p.pointX[i];
            second_pointY = p.pointY[i];
        }
    }
    p.center_point_X[0] = init_pointX;
    p.center_point_Y[0] = init_pointY;
    p.center_point_X[1] = second_pointX;
    p.center_point_Y[1] = second_pointY;

    printf("초기 클러스터 구성:\n");
    for (int i = 0; i < p.kNum; i++) {
        find_center_points(p.center_point_X[i], p.center_point_Y[i], p.center_point_X[i+1], p.center_point_Y[i+1]);
        p.count++;
        printf("\t클러스터 %d: 중심점 = (%lf, %lf)\n", i, p.center_point_X[i], p.center_point_Y[i]);
    }
}


double op_distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void find_center_points(double x1, double y1, double x2, double y2) {
    double means[1000];
    double mean_max_X;
    double mean_max_Y;
    double mean_max;

    if (p.count % 2 == 0) {
        for (int i = 0; i < p.num; i++) {
            double mean = fabs(op_distance(p.pointX[i], p.pointY[i], x2, y2) - op_distance(p.pointX[i], p.pointY[i], x1, y1));
            means[i] = mean;       
        }

        mean_max = means[0];
    
        for (int i = 0; i < p.num; i++) {
            if (means[i] < mean_max) {
                mean_max = means[i];
                mean_max_X = p.pointX[i];
                mean_max_Y = p.pointY[i];
            }
        }
        p.center_point_X[p.count+2] = mean_max_X;
        p.center_point_Y[p.count+2] = mean_max_Y;
    }
    else if (p.count % 2 == 1) {
        for (int i = 0; i < p.num; i++) {
            double mean = fabs(op_distance(p.pointX[i], p.pointY[i], x2, y2) + op_distance(p.pointX[i], p.pointY[i], x1, y1))/2;
            means[i] = mean;       
        }

    
    
        mean_max = means[0];
        for (int i = 0; i < p.num; i++) {
            if (means[i] > mean_max) {
                mean_max = means[i];
                mean_max_X = p.pointX[i];
                mean_max_Y = p.pointY[i];
            }
        }
        p.center_point_X[p.count+2] = mean_max_X;
        p.center_point_Y[p.count+2] = mean_max_Y;
    }
}

void file_read() {
    FILE *f;	
    f = fopen("p1.txt","r");		
    fscanf(f, "%d", &p.num);	
    for (int i = 1; i <= p.num; i++) {
        fscanf(f, "%lf %lf", &*p.pointX, &*p.pointY);
        p.pointX[i] = *p.pointX;
        p.pointY[i] = *p.pointY;
    }
    fclose(f);	
}





