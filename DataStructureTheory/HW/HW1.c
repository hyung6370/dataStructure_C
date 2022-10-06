#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double pointX;
    double pointY;
} Point;

Point *terms = 0;

int main() {
    int num;
    // double pointX, pointY;
    scanf("%d", &num);

    terms = (Point*)malloc(sizeof(Point)*(num))

    for (int i = 1; i <= num; i++) {
        scanf("%lf %lf", &pointX, &pointY);
        printf("%lf %lf\n", pointX, pointY);
    }

}