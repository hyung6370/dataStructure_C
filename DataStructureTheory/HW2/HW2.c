#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct Info {
    int arr_time;
    int work_amount;
    int priority_rank;
} Info;

typedef struct FIFO_info {
    int work_end_time;
    int exe_time;
    int wait_time;
    float avg_exe_time;
    float avg_wait_time;
} FIFO_info;

typedef struct Priority_info {
    int pri_start_time;
    int pri_work_amount;
    int priority_A;
    int priority_B;
} Priority_info;

// typedef struct Queue {
//     Queue *heap;
// } Queue;

Info* process_info;

int num_of_works;

int priority_check(Info A, Info B) {
    if (A.priority_rank > B.priority_rank) return 1;
    if (A.priority_rank < B.priority_rank) return 0;
    if (A.work_amount < B.work_amount) return 1;
    if (A.work_amount > B.work_amount) return 0;
    if (A.arr_time < B.arr_time) return 1;
    if (A.arr_time > B.arr_time) return 0;
    return 0;
}

void PRI_ops() {
    Priority_info* p_op;
    p_op = (Priority_info*)malloc(sizeof(Priority_info));

    int start = process_info[1].arr_time;
    int end_time = 0;

    for (int i = 1; i <= num_of_works; i++) {
        end_time += process_info[i].work_amount;
    }
    end_time = end_time + start;
    int i = 1;
    while (start != end_time) {    
        if (start == process_info[i].arr_time) {

        }

        start++;
    }
}

void file_read() {
    char *fname = (char*)malloc(sizeof(char)*50);

    printf("입력파일 이름? ");
    scanf("%s", fname);

    FILE *f = fopen(fname, "r");
    fscanf(f, "%d", &num_of_works);

    process_info = (Info*)malloc(sizeof(Info)*num_of_works);

    for (int i = 1; i <= num_of_works; i++) {
        fscanf(f, "%d %d %d", &process_info[i].arr_time, &process_info[i].work_amount, &process_info[i].priority_rank);
    }

    fclose(f);
}

void FIFO_ops() {
    FIFO_info* f_op;
    f_op = (FIFO_info*)malloc(sizeof(FIFO_info));

    float exe_temp = 0;
    float wait_temp = 0;
    
    f_op[1].work_end_time = process_info[1].arr_time + process_info[1].work_amount;
    for (int i = 2; i <= num_of_works; i++) {
        f_op[i].work_end_time += f_op[i-1].work_end_time + process_info[i].work_amount;
    }
    int end_time = f_op[num_of_works].work_end_time;

    for (int i = 1; i <= num_of_works; i++) {
        f_op[i].exe_time += f_op[i].work_end_time - process_info[i].arr_time;
        exe_temp += f_op[i].exe_time;
        f_op[i].wait_time += f_op[i].exe_time - process_info[i].work_amount;
        wait_temp += f_op[i].wait_time;
    }
    f_op->avg_exe_time = exe_temp / num_of_works;
    f_op->avg_wait_time = wait_temp / num_of_works;

    printf("FIFO Scheduling의 실행 결과:\n");
    printf("\t작업수 = %d, 종료시간 = %d, 평균 실행시간 = %.2f, 평균 대기시간 = %.2f\n", num_of_works, end_time, f_op->avg_exe_time, f_op->avg_wait_time);
}

int main() {
    file_read();
    FIFO_ops();
    // PRI_ops();
    return 0;
}