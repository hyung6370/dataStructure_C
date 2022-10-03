#include <stdio.h>

int main(void) { 
    int data[10] = { 1, 3, 4, 6, 8, 10, 13, 14, 15, 16 }; //정렬된 데이터. 
    int keyValue; //찾고 싶은 값.

    int startNum;
    int endNum;
    int midNum;

    while (1) { //무한 루프 계속 탐색을 위해.  
        for (int i = 0; i < 10; i++) {
            printf("%d ", data[i]);
            }
        printf("\n어떤 값을 찾고싶나요? : ");
        scanf("%d", &keyValue);

        startNum = 0;
        endNum = 9; //동적 할당 시엔 배열의 마지막 자리.  
        while (1) { //찾을 때까지 무한루프..
            midNum = (startNum + endNum) / 2;
            if (startNum < endNum) {
                if (data[midNum] < keyValue) {
                    startNum = midNum + 1;
                }
                else if (data[midNum] > keyValue) {
                    endNum = midNum - 1;
                }
                else {
                    printf("Key값(%d)은 data[%d]에 있습니다.\n\n", keyValue, midNum);
                    break;
                }
            }
            else {
                if (data[midNum] != keyValue) {
                    printf("Key값(%d)은 data 배열에 존재하지 않습니다.\n\n", keyValue);
                }
                else {
                    printf("Key값(%d)은 data[%d]에 있습니다.\n\n", keyValue, midNum);
                }
                break;
            }
        }
    }
    return 0;
}


