#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
#define MAX_DEGREE 101
#define MAX_TERMS 100
#define _CRT_SECURE_NO_WARNINGS

typedef struct {
    float coef;
    int expon;
} polynomial;

polynomial *terms = (polynomial*)malloc(sizeof(polynomial)*10);