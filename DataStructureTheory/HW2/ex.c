#include <stdio.h>
#define MAX_SIZE 100    // Heap 의 최대 원소 개수 
 
typedef struct element{    // Heap 의  노드 
    int key;    // Heap 의 key
    /* 여기에 데이터 추가 가능 ex) int data */ 
}element;    
 
typedef struct Heap{    // Heap 자료구조 
    element heap[MAX_SIZE];     
    int size;
}Heap;


 
 
void max_heap_insert(Heap* h, element item){
    int i;
    i = ++(h->size);    // 마지막 위치(마지막 원소의 index+1) 
    
    /* 루트노드가 아니고, 삽입할 값이 적절한 위치를 찾을 때까지*/
    while( (i != 1) && (item.key > h->heap[i/2].key) ){
        h->heap[i] = h->heap[i/2];    // 자식 노드와 부모노드 교환 
        i /= 2;    // 한 레벨 위로 올라감 
    }
    
    h->heap[i] = item;    // 새로운 노드 삽입     
}
 
element max_heap_delete(Heap* h){
    int parent, child;
    element item, temp;
    
    item = h->heap[1];    // 반환할 노드 저장
    temp = h->heap[(h->size)--];    // 마지막 노드 temp 에 저장, 사이즈 1감소
    parent = 1;     
    child = 2; 
    
    while(child <= h->size){
        /* 왼쪽 자식 노드와 오른쪽 자식 노드 중 더 큰 자식 노드*/
        if( (child < h->size) && ((h->heap[child].key) < h->heap[child+1].key )){
            child++;    // 오른쪽 자식 노드 선택
        }
        
        /* 마지막 노드가 자식 노드보다 크면 종료 */
        if(temp.key >= h->heap[child].key){
            break;
        } 
        
        /* 부모노드와 자식노드 교환 */
        h->heap[parent] = h->heap[child];
        
        /* 한 레벨 아래로 이동 */ 
        parent = child;
        child *= 2;
    }
    
    /* 마지막 노드를 재설정한 위치에 삽입 */ 
    h->heap[parent] = temp;
    
    /* 최댓값 노드 반환 */ 
    return item;    
    
} 
 
 
int main(){
    Heap max_heap;
    element item;
    item.key = 9;
    max_heap_insert(&max_heap, item);
    item.key = 7;
    max_heap_insert(&max_heap, item);
    item.key = 6;
    max_heap_insert(&max_heap, item);
    item.key = 4;
    max_heap_insert(&max_heap, item);
    item.key = 5;
    max_heap_insert(&max_heap, item);
    item.key = 1;
    max_heap_insert(&max_heap, item);
    item.key = 3;
    max_heap_insert(&max_heap, item);
    item.key = 8;
    max_heap_insert(&max_heap, item);
    
    while(max_heap.size > 0){
        item = max_heap_delete(&max_heap);
        printf("%d ", item.key);
    }
        
    return 0;
} 
