#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 1500
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

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
void find_c_points();

int main() {
    char file_name[30];
    p.count = 0;

    printf("파일 이름과 k 값을 입력하세요: ");
    scanf("%s", file_name, sizeof(file_name));    
    scanf(" %d", &p.kNum);
	file_read();

    find_c_points();
    // printf("p.center_point_X[0] p.center_point_Y[0]: %lf %lf\n", p.center_point_X[0], p.center_point_Y[0]);
    // printf("p.center_point_X[1] p.center_point_Y[1]: %lf %lf\n", p.center_point_X[1], p.center_point_Y[1]);
    // printf("p.center_point_X[2] p.center_point_Y[2]: %lf %lf\n", p.center_point_X[2], p.center_point_Y[2]);
    // printf("p.center_point_X[3] p.center_point_Y[3]: %lf %lf\n", p.center_point_X[3], p.center_point_Y[3]);
    // printf("p.center_point_X[4] p.center_point_Y[4]: %lf %lf\n", p.center_point_X[4], p.center_point_Y[4]);
}

double op_distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void find_c_points() {
    double distance[6000];
    double first_pointX = p.pointX[1];
    double first_pointY = p.pointY[1];
    p.center_point_X[0] = first_pointX;
    p.center_point_Y[0] = first_pointY;
    
    double fsdistance[1000];
    double init_xy_distance;
    double farthest = fsdistance[0];
    double second_pointX;
    double second_pointY;

    for (int i = 1; i <= p.num; i++) {
        init_xy_distance = sqrt(pow(p.pointX[i] - first_pointX, 2) + pow(p.pointY[i] - first_pointY, 2));
        fsdistance[i] = init_xy_distance;
        if (fsdistance[i] > farthest) {
            farthest = fsdistance[i];
            second_pointX = p.pointX[i];
            second_pointY = p.pointY[i];
        }
    }
    p.center_point_X[1] = second_pointX;
    p.center_point_Y[1] = second_pointY;

    // for (int i = 0; i < p.kNum; i++) {
    //     for (int j = 1; j <= p.num; j++) {
    //         distance[i] = op_distance(p.pointX[i+1], p.pointY[i+1], p.center_point_X[i], p.center_point_Y[i]);
    //     }
    // }

    double col_max[1000];
    double col_max_X[1000];
    double col_max_Y[1000];
    double col_min[1000];
    double col_min_X[1000];
    double col_min_Y[1000];
    // double oneMax;
    // double oneMax_X;
    // double oneMax_Y;
    // double one_max[1000];
    // double one_max_X[1000];
    // double one_max_Y[1000];
    // double one_min[1000];
    // double one_min_X[1000];
    // double one_min_Y[1000];
    // double distanceMin[1000];
    double dis_max;
    double dis_max_X;
    double dis_max_Y;
    double dis_min;
    double dis_min_X;
    double dis_min_Y;

    for (int i = 1; i <= p.num; i++) {
        for (int j = 0; j < p.kNum; j++) {
            distance[j] = op_distance(p.pointX[i], p.pointY[i], p.center_point_X[j], p.center_point_Y[j]);
        }
        dis_max = distance[0];
        dis_min = distance[0];
        for (int j = 0; j < p.kNum; j++) {
            if (distance[j] > dis_max) {
                dis_max = distance[j];
                dis_max_X = p.pointX[i];
                dis_max_Y = p.pointY[i];
            }
            if (distance[j] < dis_min) {
                dis_min = distance[j];
                dis_min_X = p.pointX[i];
                dis_min_Y = p.pointY[i];
            }
        }
        col_max[i-1] = dis_max;
        col_max_X[i-1] = dis_max_X;
        col_max_Y[i-1] = dis_max_Y;
        col_min[i-1] = dis_min;
        col_min_X[i-1] = dis_min_X;
        col_min_Y[i-1] = dis_min_Y;



        // oneMax = col_max[0];
        // for (int j = 0; j < p.num; j++) {
        //     if (col_max[j] > oneMax) {
        //         oneMax = col_max[j];
        //         oneMax_X = col_max_X[j];
        //         oneMax_Y = col_max_Y[j];
        //     }
        // }

        // for (int j = 0; )
    }
    
    // printf("oneMax = %lf, oneMax_X = %lf, oneMax_Y = %lf\n", oneMax, oneMax_X, oneMax_Y);
    for (int i = 0; i < p.num; i++) {
        printf("col_min[%d] = %lf, col_min_X[%d] = %lf, col_min_Y[%d] = %lf\n", i, col_min[i], i, col_min_X[i], i, col_min_Y[i]);
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
    // printf("%d\n", p.num);
    // for (int i = 1; i <= p.num; i++) {
    //     printf("%lf %lf\n", p.pointX[i], p.pointY[i]);
    // }

    // init_find_center_point();
}