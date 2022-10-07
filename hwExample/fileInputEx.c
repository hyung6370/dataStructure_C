#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1500

struct point {
    int num;
    double pointX[MAX_SIZE];
    double pointY[MAX_SIZE];
};

struct point p;	

void file_read();

void op_distance(double pointX, double pointY) {
    int init_cPoint;
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
    printf("%d\n", p.num);
    for (int i = 1; i <= p.num; i++) {
        printf("%lf %lf\n", p.pointX[i], p.pointY[i]);
    }

    // op_distance(p.pointX[1], p.pointY[1]);
}



int main() {
    char file_name[30];
    int kNum;

    printf("파일 이름과 k 값을 입력하세요: ");
    scanf("%s", file_name, sizeof(file_name));    
    scanf(" %d", &kNum);
	file_read();
    printf("\n\n");
    printf("pointX[1] pointY[1] : %lf %lf\n", p.pointX[1], p.pointY[1]);
}
