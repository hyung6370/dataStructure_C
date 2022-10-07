#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 1500
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

struct point {
    int num;
    double pointX[MAX_SIZE];
    double pointY[MAX_SIZE];
};

struct point p;

void file_read();
double op_distance(double x1, double y1, double x2, double y2);
void find_center_points(double x1, double y1, double x2, double y2);

int main() {

    char file_name[30];
    int kNum;
 
    double init_xy_distance;

    double distance[1000];
    double farthest = distance[0];
    double second_pointX;
    double second_pointY;

    printf("파일 이름과 k 값을 입력하세요: ");
    scanf("%s", file_name, sizeof(file_name));    
    scanf(" %d", &kNum);
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


    printf("\n\n");
    printf("C0_x C0_y : %lf %lf\n", init_pointX, init_pointY);
    printf("C1_x C1_y : %lf %lf\n", second_pointX, second_pointY);
    printf("\n\n");

    find_center_points(init_pointX, init_pointY, second_pointX, second_pointY);
}


void init_find_center_point() {
    // for (int i = 1; i <= p.num; i++) {
    //     for (int j = i+1; j <= p.num; j++) {
    //         xy_distance = sqrt(pow(p.pointX[j] - p.pointX[i], 2) + pow(p.pointY[j] - p.pointY[i], 2));
    //         printf("xy_distance[%d]-[%d] : %lf\n", i, j, xy_distance);
    //     }
    // }  
}

double op_distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void find_center_points(double x1, double y1, double x2, double y2) {
    double close[1000];
    double close_X;
    double close_Y;
    double closet;
    
    for (int i = 0; i < p.num; i++) {
        double diff = fabs(op_distance(p.pointX[i], p.pointY[i], x2, y2) - op_distance(p.pointX[i], p.pointY[i], x1, y1));
        close[i] = diff;       
    }
    closet = close[0];
    for (int i = 0; i < p.num; i++) {
        if (close[i] < closet) {
            closet = close[i];
            close_X = p.pointX[i];
            close_Y = p.pointY[i];
        }
    }
    printf("closet : %lf\n", closet);
    printf("좌표 : %lf %lf\n\n", close_X, close_Y);

}

// void vv(double pointX, double pointY) {


//     double sum_pointXs = 0;
//     double sum_pointYs = 0;

//     for (int i = 1; i <= p.num; i++) {
//         sum_pointXs += p.pointX[i];
//         sum_pointYs += p.pointY[i];
//     }
//     printf("sum_pointXs : %lf\n", sum_pointXs);
//     printf("sum_pointYs : %lf\n", sum_pointYs);
// }

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
    printf("%d\n", p.num);
    for (int i = 1; i <= p.num; i++) {
        printf("%lf %lf\n", p.pointX[i], p.pointY[i]);
    }

    // init_find_center_point();
}





