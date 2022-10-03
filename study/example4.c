#include <stdio.h>

int main() {
    const char* arr[3];
    
    arr[0] = "ash";
    arr[1] = "island";
    arr[2] = "emptyhead";

    for (int i = 0; i < 3; i++) {
        printf("arr[%d] -> %s\n", i, arr[i]);
    }
    return 0;
}