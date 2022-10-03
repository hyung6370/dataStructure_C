#include <stdio.h>
#include <stdlib.h>

void add(int*, int**);

int main(void){
    int size = 5;
    int* arr = (int*)malloc(sizeof(int)*size); //길이가 5인 배열 생성     
    int i = 0;

     //-1이 입력될 때 까지 무한루프    
    while (1){
        printf("정수를 입력하세요 : ");
        scanf("%d", &arr[i]);

          //사용자 입력값이 -1이면 반복문 탈출          
        if (arr[i] == -1)
            break;
          //i+1번째가 size와 같으면 add함수를 호출          
        if (i + 1 == size)
            add(&size, &arr);

        i++;
    }

    for (int j = 0; j < i; j++)
        printf("%d 인덱스의 값 : %d\n", j, arr[j]);

    free(arr);
    return 0;
}

//배열의 크기를 증가시키는 함수
void add(int* s, int** ar){
    int newsize = *s + 3; //size의 크기를 3 증가시킴
     //main의 arr보다 길이가 3긴 배열 생성     
    int* temp = (int*)malloc(sizeof(int)*newsize);

     //ar의 값을 temp에 복사     
    for (int i = 0; i < *s; i++)
    temp[i] = (*ar)[i];

    free(*ar); //이전 배열 삭제
    *ar = temp;
    *s += 3; //main의 size를 3증가시킴
    }