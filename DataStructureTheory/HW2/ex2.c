#include <stdio.h>

#include <stdlib.h>

#include <windows.h>

#define MAXSIZE 1000

//------사용할 자료 구조 선언--------------------------------------

typedef struct _process {

           int pro_num, cpu_time, arr_t, pri, wait_t, ta_t, rem_t;

}

process;

           // 프로세스 식별번호

           // 프로세스가 CPU를 사용한 시간

           // 프로세스 우선순위

           //프로세스 대기시간

           //프로세스 전체 시간 , WT+BT

           //남은 동작 시간

 

//------------스케줄링 알고리즘 함수--------------------------------

int process_fcfs(process *pro, int n);

int process_srt(process *pro, int n);

int process_pri(process *pro, int n);

int process_rr(processs *pro, int n, int Q);

// 라운드 로빈은 타임 퀀텀도 같이 매개변수로 받는다.

int process_sjf(process *pro, int n);

int process_generate(process *pro, int n);

// -----------프로세스를 정렬 함수 ---------------------------------

void at_sort(process *pro, int n);

void resort(process *pro, int n);

 

 

//===========================================================================================

int main() {

           int i =0;

           int n =0;

           int Q =0;

           int index=0;

           float tat;

           FILE *fp;

           fp=fopen("proc.txt","r");

           process ready_queue[MAXSIZE];

           printf("파일읽기 시작\n");

           while(!feof(fp)) {

                     fscanf(fp, "%d", &ready_queue[i].pro_num);

                     fscanf(fp, "%d", &ready_queue[i].cpu_time);

                     fscanf(fp, "%d", &ready_queue[i].arr_t);

                     fscanf(fp, "%d", &ready_queue[i].pri);

                     ready_queue[i].rem_t=ready_queue[i].cpu_time;

                     index=index+1;

                     printf("%d\n",index);

                     i++;

           }

           fclose(fp);

           printf("파일읽기 끝\n");

           n=index-1;

           printf("%d\n",n);

           printf("\n=================Main Menu====================\n\n1. Read processes from proc.txt\n2. Generate random processes\n3. First come first Serve (FCFS)\n4. Shortest Job First (SJF)\n5. Shortest Remaining time First (SRTF)\n6. Priority\n7. Round Robin (RR)\n8. Exit\n==============================================\n");

           while(1){

                                 int ch = 0;

                                 printf("메뉴를 선택해주세요.\n");

                                 scanf("%d", &ch);         

                                 float tat=0.0;

                                 switch(ch){

                                                                            case 1:

                                  printf("1. Read processes from proc.txt\n====================PROC======================\n");

                                  printf("P#       BT        AT        Pri\n");

                                  for(i=0; i<n; i++) {

                                           printf("%d     %d       %d       %d\n",ready_queue[i].pro_num, ready_queue[i].cpu_time, ready_queue[i].arr_t, ready_queue[i].pri);

                                  }

                                  printf("==============================================\n");

                                  continue;

                                  break;

                             case 2:

                                  printf("2. Generate random processes\n");

                                  process_generate(ready_queue, n);

                                  printf("\n\n==================생성완료===================\n");

                                  n++;

                                  continue;

                                  break;

                             case 3:                 //fcfs

                                  at_sort(ready_queue, n);

                                  process_fcfs(ready_queue, n);

                                  resort(ready_queue, n);

                                  printf("3. First come first Serve (FCFS)\n====================FCFS======================\n");

                                               printf("P#       BT        AT        Pri        WT       TAT\n");

                                               for(i=0; i<n; i++) {

                                           tat=tat+ready_queue[i].ta_t;

                                                               printf("%d          %d       %d       %d       %d       %d\n",ready_queue[i].pro_num, ready_queue[i].cpu_time, ready_queue[i].arr_t, ready_queue[i].pri, ready_queue[i].wait_t, ready_queue[i].ta_t);

                                  }

                                               printf("average turnaround time: %.2f\n",tat/n);

                                               printf("==============================================\n");

                                               continue;

                                               break;

                            case 4:                  //sjf

                                 at_sort(ready_queue, n);

                                 printf("1");

                                 process_sjf(ready_queue, n);

                                 printf("2");

                                                                                      resort(ready_queue, n);

                                                                                      printf("3");

                                 printf("4. Shortest Job First (SJF)\n====================SJF=======================\n");

                                 printf("P#         BT        AT        Pri        WT       TAT\n");

                                 for(i=0; i<n; i++) {

                                          tat=tat+ready_queue[i].ta_t;

                                          printf("%d      %d       %d       %d       %d       %d\n",ready_queue[i].pro_num, ready_queue[i].cpu_time, ready_queue[i].arr_t, ready_queue[i].pri, ready_queue[i].wait_t, ready_queue[i].ta_t);

                                 }

                                 printf("average turnaround time: %.2f\n",tat/n);

                                              printf("==============================================\n");

                                              continue;

                                              break;

                           case 5:                    //srt

                                              at_sort(ready_queue, n);

                                              process_srt(ready_queue, n);

                                              resort(ready_queue, n);

                    

                                              printf("5. Shortest Remaining time First (SRTF)\n====================SRTF======================\n");

                                              printf("P#        BT        AT        Pri        WT       TAT\n");

                                              for(i=0; i<n; i++) {

                                          tat=tat+ready_queue[i].ta_t;

                                          printf("%d      %d       %d       %d       %d       %d\n",ready_queue[i].pro_num, ready_queue[i].cpu_time, ready_queue[i].arr_t, ready_queue[i].pri, ready_queue[i].wait_t, ready_queue[i].ta_t);

                                 }

                                 printf("average turnaround time: %.2f\n",tat/n);

                                              printf("==============================================\n");

                                              continue;

                                              break;

                           case 6:                    //pri

                                at_sort(ready_queue, n);

                                process_pri(ready_queue, n);

                                             resort(ready_queue, n);

                    

                                printf("6. Priority\n====================PRI=======================\n");

                                             printf("P#          BT        AT        Pri        WT       TAT\n");

                                             for(i=0; i<n; i++) {

                                         tat=tat+ready_queue[i].ta_t;

                                         printf("%d        %d       %d       %d       %d       %d\n",ready_queue[i].pro_num, ready_queue[i].cpu_time, ready_queue[i].arr_t, ready_queue[i].pri, ready_queue[i].wait_t, ready_queue[i].ta_t);

                                }

                                             printf("average turnaround time: %.2f\n",tat/n);

                                             printf("==============================================\n");

                                             continue;

                                             break;

                            case 7:                  //RR

                                 printf("퀀텀 입력\n");

                                 scanf("%d",&Q);

                                 at_sort(ready_queue, n);

                                 process_rr(ready_queue, n, Q);

                                 resort(ready_queue, n);

                                 printf("7. Round Robin (RR)\n====================RR========================\n");

                                 printf("P#         BT        AT        Pri        WT       TAT\n");

                                 for(i=0; i<n; i++) {

                                          tat=tat+ready_queue[i].ta_t;

                                          printf("%d      %d       %d       %d       %d       %d\n",ready_queue[i].pro_num, ready_queue[i].cpu_time, ready_queue[i].arr_t, ready_queue[i].pri, ready_queue[i].wait_t, ready_queue[i].ta_t);

                                 }

                                 printf("average turnaround time: %.2f\n",tat/n);

                                 printf("==============================================\n\n");

                                 ent_key=0;

                                 continue;

                                 break;

                            case 8:

                                              printf("\n\n====================EXIT======================\n");

                                              exit(0);

                                              break;

                                 }

                           }

  }      

          

          

          

void at_sort(process *pro, int n) {

// arival time 순으로 프로세스를 정렬 시켜 준다. 

           process temp;

           int i,j;

           for (i=n-1; i>0;i--) {

                     for (j=0;j<i;j++) {

                                // i 가 n-1부터 시작해서 0 부터 n 까지 process를 비교하고, 그다음  i가 n-2 가 되면 맨 앞에껄 두고 그 다음 부터 마지막까지 비교 한다. 

                                if(pro[j].arr_t>pro[j+1].arr_t) {

                                           temp=pro[j+1];

                                           pro[j+1]=pro[j];

                                           pro[j]=temp;

                                } else if(pro[j].arr_t==pro[j+1].arr_t&&pro[j].pro_num>pro[j+1].pro_num) {

                                           //동시에 왔으면 프로세스 번호 순으로 정렬한다. 작은 번호가 먼저 나온다. 

                                           temp=pro[j+1];

                                           pro[j+1]=pro[j];

                                           pro[j]=temp;

                                }

                     }

           }

}

 

void resort(process *pro, int n) {

//프로세스 구조체

// i 가 n-1부터 시작해서 0 부터 n 까지 process를 비교하고, 그다음  i가 n-2 가 되면 맨 앞에껄 두고 그 다음 부터 마지막까지 비교 한다. 

//도착한 순서대로 정렬된 프로세스 구조체를 가져와서 CPU_time과 대기시간 WT를 더해 준다.

           process temp;

           int i,j;

           for (i=n-1; i>0;i--) {

                     for (j=0;j<i;j++) {

                                if(pro[j].pro_num>pro[j+1].pro_num) {

                                           temp=pro[j+1];

                                           pro[j+1]=pro[j];

                                           pro[j]=temp;

                                }

                     }

           }

}

 

int process_fcfs(process *pro, int n) {

//i는 0부터,1, 2, 3, 4, 5, n-1 까지

// j는 i값에 따라서(i,j)로 표현 하면

// (0,0) (1,0) (2,(0,1)), (3,(0,1,2)),

//...(n-1, (0,1,2,3,..,n-2))이런식으로

//process의 cpu_time을 temp에 누적한다.

//만약 첫번째 것만 도착했으면, 첫번째 프로세스의 cpu_time

//그 뒤로 

// 대기시간은 = 전체 CPU 사용 시간에서, k가 먼저 왔으니까,

// i가 도착한 시간을 뺴고, 거기에 k의 도착시간을 더하면, 기다린 시간이다.

// 대기 시간이 없는 경우 바로 수행하기 때문에

// 남은 동작 시간을 매시간 계산하여 가장 짧은 남은 동작을 가진 프로세스 먼저 하며,

//선점 형으로 동 작

           int temp;

           int wt=0;

           int i,j,k=0;

           for (i=0;i<n;i++) {

                     temp=0;

                     for (j=k;j<i;j++) {

                                temp=temp+pro[j].cpu_time;

                     }

                     wt=temp-pro[i].arr_t+pro[k].arr_t;

                     if(wt<=0) {

                                k=i;

                                pro[i].wait_t=0;

                                pro[i].ta_t=pro[i].cpu_time + pro[i].wait_t;

                     } else {

                                pro[i].wait_t=wt;

                                pro[i].ta_t=pro[i].cpu_time + pro[i].wait_t;

                     }

           }

}

int process_srt(process *pro, int n) {

//남은 프로세스 수

// 현재 시간

// for문에서 선택 되는 현재 process의 도착 시간이 now같거나 작고

// i가 n보다 작을 때 까찌, 증감시키면서

//해당 프로세스의 남은 시간이 최소값 보다 작고, 양수이면

// 지금 실행할 프로세스를 i로 잡는다. 

//그리고 현재 프로세스의 남은 시간을 최소 값으로 잡니다.

// 반복문을 돌면서 이 값은 최소값이 된다. 

// 남은 시간값이 현재 now_p보다 작지 않을 때, 

//시간을 증가시킨다.

//temp[0]의 값이 process[0] cpu_time 시간과 다 때, 

// temp에다가 n개 만큼의 남은 시간을 채워 넣는다. 

// 시간이 지날 수록 현재 사용하고 있는 프로세스의

// 남은 동작 시간 카운트를 감소 시킨다. 

// 남은 동작시간이 0일 때 새로운 프로세스를 재선택 하는 과정

// 남은 프로세스를 감소시켜준다. 

// 스케줄링 완료한 값이 temp에 각각의 index에 담겨 있었는데 이를 다시

//process의 remain_t에다 저장해 준다. 

// 우선순위대로 스케쥴링 작을 수록 우선순위 높은거

           int remain, min, now_p, i, temp[150];

           int now, wt=0;

           remain=n;

           now=pro[0].arr_t;

           while(remain>0) {

                     min=5000;

                     for (i=0; pro[i].arr_t<=now && i<n; i++) {

                                if(pro[i].rem_t<min && pro[i].rem_t>0) {

                                           now_p=i;

                                           min=pro[i].rem_t;

                                }

                     }

                     now++;

                     if(temp[0] !=pro[0].cpu_time) {

                                for (i=0; i<n; i++) {

                                           temp[i]=pro[i].rem_t;

                                }

                     }

                     pro[now_p].rem_t--;

                     if(pro[now_p].rem_t==0) {

                                pro[now_p].wait_t=now-pro[now_p].arr_t-pro[now_p].cpu_time;

                                pro[now_p].ta_t=pro[now_p].cpu_time + pro[now_p].wait_t;

                                wt=wt+pro[now_p].wait_t;

                                remain--;

                     }

           }

           for (i=0; i<n; i++) {

                     pro[i].rem_t=temp[i];

           }

}

int process_pri(process *pro, int n) {

// 우선 남은 시간을 다 해당 process의 cpu_time으로 채워준다.

//현재 시간을 process[0]이 도착한 시간으로 잡는다. 

//남은 프로세스 의 수

// temp에다 process들의 남은 시간을 채워준다.

// 새로 들어오는 애들로 부터

//끝난 프로세스가 아닌데 현재 min보다 우선순위값이 작은 프로세스면

//그 프로세스 번호가 num이 되고 

// 그 프로세스의 우선순위가 최소 값이 되며

//flag를 1로 바꿔준다.

//시간을 증가 시킨다. 

//pro[num]을 다 수행하고 시간에다가 추가해주는 것이다.

           int flag = 0;

           int i,time,remain,num, min, temp[150];

           for (i=0; i<n; i++) {

                     pro[i].rem_t = pro[i].cpu_time;

           }

           time = pro[0].arr_t;

           remain = n;

           if(temp[0] !=pro[0].cpu_time) {

                     for (i=0; i<n; i++) {

                                temp[i]=pro[i].rem_t;

                     }

           }

           while(remain>0) {

                     min = 9999;

                     for (i=0; pro[i].arr_t <= time && i<n; i++) {

                                if(pro[i].rem_t != 0 && pro[i].pri<min && pro[i].cpu_time>0) {

                                           num = i;

                                           min = pro[i].pri;

                                           flag = 1;

                                }

                     }

                     if(flag ==1) {

                                pro[num].rem_t = 0;

                                pro[num].wait_t = time - pro[num].arr_t;

                                remain--;

                                time += pro[num].cpu_time;

                     } else {

                                time ++;

                     }

                     flag = 0;

           }

           for (i=0; i<n; i++) {

                     pro[i].ta_t = pro[i].wait_t + pro[i].cpu_time;

           }

           for (i=0; i<n; i++) {

                     pro[i].rem_t=temp[i];

           }

}

int process_sjf(process *pro, int n) {

           int flag = 0;

           int i,time,remain,num, min, temp[150];

           for (i=0; i<n; i++) {

                     pro[i].rem_t = pro[i].cpu_time;

           }

           time = pro[0].arr_t;

           remain = n;

           if(temp[0] !=pro[0].cpu_time) {

                     for (i=0; i<n; i++) {

                                temp[i]=pro[i].rem_t;

                     }

           }

           while(remain>0) {

                     min = 9999;

                     for (i=0; pro[i].arr_t <= time && i<n; i++) {

                                if(pro[i].rem_t != 0 && pro[i].cpu_time<min && pro[i].cpu_time>0) {

                                           num = i;

                                           min = pro[i].cpu_time;

                                           flag = 1;

                                }

                     }

                     if(flag ==1) {

                                pro[num].rem_t = 0;

                                pro[num].wait_t = time - pro[num].arr_t;

                                remain--;

                                time += pro[num].cpu_time;

                     } else {

                                time ++;

                     }

                     flag = 0;

           }

           for (i=0; i<n; i++) {

                     pro[i].ta_t = pro[i].wait_t + pro[i].cpu_time;

           }

           for (i=0; i<n; i++) {

                     pro[i].rem_t=temp[i];

           }

}

int process_rr(process *pro, int n, int Q) {

// temp에다 값저장 temp2에다는 process들의 특정 값 저장

//int i , count 그리고 totaltime

//초기화 절차

// process들의 남은 시간을 temp2 배열에 넣어준다.

//무한 루프

// 현재 임시 값은 quantom

// 만약 process i의 남은 시간이 없다면, 

// count를 증가 시키고, 

//i를 증가 시켜 다른 process로 간다. 

// 만약 남은 시간이 퀀텀보다 크다면, 그 값을 빼준다음 다시 저장

// 남은시간이 0이거나 퀀텀보다 크다면,

// temp에다가 남은 시간 저장해주고,

// 실행했으니까, pro[i].remain_t는 0으로

// 전체 시간은 수행한 시간, 왜냐하면 위에서

//퀀텀보다 작을 때, 그 값을 total time에 넣어 주었다.

//process[i]의 전체 시간은 tt

// 다 돌았을 때,

//while문 여기 까지

// 이제 그동안 temp에 모았던거 reamin_t로 넣어준다.

// wait 시간은 전체 시간 - cpu시간

           int temp, temp2[150];

           int i, count;

           int tt =0;

           //tt에 쓰레기 값이 들어가면 않된다.

           if(temp2[0] !=pro[0].cpu_time) {

                     for (i=0; i<n; i++) {

                                temp2[i]=pro[i].rem_t;

                     }

           }

           while(1) {

                     for (i=0,count=0;i<n;i++) {

                                temp=Q;

                                if(pro[i].rem_t==0) {

                                           count++;

                                           continue;

                                }

                                if(pro[i].rem_t>Q)

                                                                           pro[i].rem_t=pro[i].rem_t-Q; else if(pro[i].rem_t>=0) {

                                           temp=pro[i].rem_t;

                                           pro[i].rem_t=0;

                                }

                                tt=tt+temp;

                                pro[i].ta_t=tt;

                     }

                     if(n==count)

                                                     break;

           }

           for (i=0;i<n;i++) {

                     pro[i].rem_t=temp2[i];

                     pro[i].wait_t=pro[i].ta_t-pro[i].cpu_time;

           }

}

int process_generate(process *pro, int n) {

           // 랜덤 프로세스 생성, 

           FILE *fp2;

           int j, found;

           fp2=fopen("proc.txt","a+");

           int i=n;

           //프로세스 개수, 현재 마지막 프로세스가 몇개인지 파악하는 데 사용된다.

           int bt =(rand()%25)+1;

           pro[i].pro_num=i+1;

           pro[i].cpu_time=bt;

           while(1) {

                     pro[i].pri=rand()%50;

                     found=0;

                     for (j=0;j<i;++j) {

                                if(pro[j].pri==pro[i].pri) {

                                           found=1;

                                           break;

                                }

                     }

                     if(!found) break;

           }

           while(1) {

                     pro[i].arr_t=rand()%50;

                     found=0;

                     for (j=0;j<i;++j) {

                                if(pro[j].arr_t==pro[i].arr_t) {

                                           found=1;

                                           break;

                                }

                     }

                     if(!found) break;

           }

           fprintf(fp2,"\r\n%d %d %d %d",pro[i].pro_num, pro[i].cpu_time, pro[i].arr_t, pro[i].pri);

           fclose(fp2);

}