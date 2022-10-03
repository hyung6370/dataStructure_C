#include <stdio.h>
#define MAX_SIZE 100

float sum(float[], int);
float input[MAX_SIZE], answer;

float sum(float list[], int n) {
    float tempsum = 0;
    for (int i = 0; i < n; i++)
        tempsum += list[i];
    return tempsum;
}

int main() {
    for (int i = 0; i < MAX_SIZE; i++) {
        input[i] = i;
    }

    answer = sum(input, MAX_SIZE);
    printf("The Sum is : %f\n", answer);
}