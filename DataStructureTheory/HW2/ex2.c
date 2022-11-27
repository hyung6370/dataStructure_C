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
    double avg_exe_time;
    double avg_wait_time;
} FIFO_info;

typedef struct Priority_info {
    int total_end_time;
    int remain_work_amount;
    int exe_time;
    int wait_time;
    int temp;
    double avg_exe_time;
    double avg_wait_time;
} Priority_info;

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

void file_read() {
    char* fname = (char*)malloc(sizeof(char) * 50);

    printf("입력파일 이름? ");
    scanf("%s", fname);

    FILE* f = fopen(fname, "r");
    fscanf(f, "%d", &num_of_works);

    process_info = (Info*)malloc(sizeof(Info) * num_of_works);

    for (int i = 1; i <= num_of_works; i++) {
        fscanf(f, "%d %d %d", &process_info[i].arr_time, &process_info[i].work_amount, &process_info[i].priority_rank);
        //printf("%d %d %d\n", process_info[i].arr_time, process_info[i].work_amount, process_info[i].priority_rank);
    }

    fclose(f);
    free(fname);
}

void FIFO_ops() {
    FIFO_info* f_op = { 0 };
    f_op = (FIFO_info*)malloc(sizeof(FIFO_info));

    float exe_temp = 0;
    float wait_temp = 0;
    f_op[1].work_end_time = process_info[1].arr_time + process_info[1].work_amount;
    for (int i = 2; i <= num_of_works; i++) {
        f_op[i].work_end_time = f_op[i - 1].work_end_time + process_info[i].work_amount;
    }
    int end_time = f_op[num_of_works].work_end_time;

    for (int i = 1; i <= num_of_works; i++) {
        f_op[i].exe_time = f_op[i].work_end_time - process_info[i].arr_time;
        exe_temp += f_op[i].exe_time;
        f_op[i].wait_time = f_op[i].exe_time - process_info[i].work_amount;
        wait_temp += f_op[i].wait_time;
    }
    f_op->avg_exe_time = exe_temp / num_of_works;
    f_op->avg_wait_time = wait_temp / num_of_works;

    printf("FIFO Scheduling의 실행 결과:\n");
    printf("\t작업수 = %d, 종료시간 = %d, 평균 실행시간 = %.2f, 평균 대기시간 = %.2f\n", num_of_works, end_time, f_op->avg_exe_time, f_op->avg_wait_time);

    // free(f_op);
}

void PRI_ops() {
    Priority_info* p_op = { 0 };
    p_op = (Priority_info*)malloc(sizeof(Priority_info));

    int start = process_info[1].arr_time;
    p_op->total_end_time = 0;

    for (int i = 1; i <= num_of_works; i++) {
        p_op->total_end_time += process_info[i].work_amount;
        p_op[i].remain_work_amount = process_info[i].work_amount;
        
    }
    p_op->total_end_time = p_op->total_end_time + start;
    printf("%d\n", p_op->total_end_time);

    /*if (p_op[1].temp != process_info[1].work_amount) {
        for (int i = 1; i < num_of_works; i++) {
            p_op[i].temp = p_op[i].remain_work_amount;
        }
    }*/

    int i = 1;
    int check = 0;
    int save = 0;

    while (start <= p_op->total_end_time) {
        

        for (int j = 1; j < check+1; j++) {
            p_op[i].wait_time++;
        }

        
        printf("다음값 %d\n", process_info[i + 1].arr_time);
        if (start == process_info[i + 1].arr_time) {
            printf("%d\n", process_info[i + 1].priority_rank);
            if (process_info[i + 1].priority_rank >= process_info[i].priority_rank) {
                if (process_info[i + 1].priority_rank == process_info[i].priority_rank && process_info[i + 1].work_amount > process_info[i].work_amount) {
                    p_op[i+1].remain_work_amount--;
                    p_op[i+1].wait_time = 0;
                    check++;
                    i++;
                }
                else if (process_info[i + 1].priority_rank == process_info[i].priority_rank && process_info[i + 1].work_amount == process_info[i].work_amount && process_info[i + 1].arr_time < process_info[i].work_amount) {
                    p_op[i + 1].remain_work_amount--;
                    p_op[i+1].wait_time = 0;
                    check++;
                    i++;
                }
                else {
                    p_op[i + 1].remain_work_amount--;
                    p_op[i + 1].wait_time = 0;
                    check++;
                    i++;
                }
            }
            else {
                p_op[i].wait_time = 0;
            }
        }
        printf("시작점 %d %d %d\n", p_op[i].remain_work_amount,check , save);

        if (p_op[i].remain_work_amount == 0&& start == process_info[i + 1].arr_time) {
            i++;
        }

        if (p_op[i].remain_work_amount == 0) {
            if (check != 0) {
                check--;
                i--;
                save++;
            }         
            else if (check == 0) {
                i += save+1 ;
                save = 0;
            }
        }

        
        p_op[i].remain_work_amount--;
        start++;
        printf("도착점 %d\n", start);
    }

    for (int i = 1; i <= num_of_works; i++) {
        // printf("p_op[%d].exe_time : %d\n", i, p_op[i].exe_time);
        printf("wait time : %d\n", p_op[i].wait_time);
    }
}

int main() {
    file_read();
    FIFO_ops();
    PRI_ops();
    return 0;
}