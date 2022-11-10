#include <stdio.h>
#include <stdlib.h>
#define IS_FULL(ptr) ((!ptr))
#define COMPARE(x,y) (((x)<(y)) ? -1: ((x)==(y)) ? 0: 1)
#define FALSE 0
#define TRUE 1

typedef struct polyNode *polyPointer;
typedef struct polyNode {
    float coef;
    int expon;
    polyPointer link;
} polyNode;

static polyPointer avail;

void create_polynomial(polyPointer *c);
polyPointer get_node(void);
polyPointer cpadd(polyPointer a, polyPointer b);
polyPointer cpmul(polyPointer a, polyPointer b);
void attach(float coefficient, int exponent, polyPointer *ptr);
polyPointer attach_mul(polyPointer poly, float coefficient, int exponent, polyPointer *ptr);
void cerase(polyPointer *ptr);
void ret_node(polyPointer *ptr);
void print_poly(polyPointer head);
void print_poly2(polyPointer head);
void print_poly3(polyPointer head);

void create_polynomial(polyPointer *c) {
    int inputCoef, inputExpon;
    polyPointer temp, ptr;
    *c = get_node();
    ptr = *c; //빈 공백리스트를 만듬
    ptr->link = ptr; //원형 링크드리스트를 만듬 /* */
    while(1) {
        printf("다항식의 항을 입력하세요. (coef expon) : ");
        scanf("%d %d", &inputCoef, &inputExpon);

        if (inputCoef == -1 && inputExpon == -1) {break;}

        temp = get_node();
        temp->coef = inputCoef;
        temp->expon = inputExpon;
        ptr->link = temp; //끝 노드와 연결시킴
        ptr = ptr->link; //이 끝 노드를 가르치도록 함 /* ptr */
        ptr->link = *c; //원형 링크드 리스트를 만듬
    }
}

polyPointer cpadd(polyPointer a, polyPointer b) {
/* a b , 다항식 와 는 헤드 노드를 가진 단순 연결 원형 리스트이고
a b .*/ //와 가 합산된 다항식을 반환한다
    polyPointer front, d, rear;
    int sum, done = FALSE;
    front = a; //의 시작을 기록 /* a */
    a = a->link; //와 의 헤드 노드를 건너 뜀 /*a b */
    b = b->link;
    d = get_node(); //합산용 헤드 노드를 가져옴
    d->expon = -1;
    rear = d;
    do {
        switch(COMPARE(a->expon, b->expon)){
            case -1 : /* a->expon < b->expon */
                attach(b->coef, b->expon, &rear);
                b = b->link;
                break;
            case 0 : /* a->expon = b->expon */
                if(front == a) done = TRUE;
                else{
                    sum = a->coef + b->coef;
                    if(sum) attach(sum, a->expon, &rear);
                    a = a->link;
                    b = b->link;    
                    break;
                }
            case 1 : /* a->expon > b->expon */
                attach(a->coef, a->expon, &rear);
                a = a->link;
        }
    } while(!done);
    rear->link = d;
    return d;
}

polyPointer cpmul(polyPointer a, polyPointer b) {
    polyPointer p, q, r, c, d, result;
    int done = FALSE;

    q = b;
    c = NULL;
    d = get_node();
    d->expon = -1;
    r = d;
    do {
        p = a;
        r = NULL;
        result = NULL;
        do {
            result = attach_mul(result, p->coef * q->coef, p->expon + q->expon, &r);
            p = p->link;
        } while (!done && p != a);
        c = cpadd(c, result);
        q = q->link;
    } while (!done && q != b);
    r->link = d;
    return c;
}

void attach(float coefficient, int exponent, polyPointer *ptr) {
    polyPointer temp;
    temp = get_node();
    temp->coef = coefficient;
    temp->expon = exponent;
    (*ptr)->link = temp;
    *ptr = temp;
}

polyPointer attach_mul(polyPointer poly, float coefficient, int exponent, polyPointer *ptr) {
    polyPointer newNode;
    newNode = (polyPointer)malloc(sizeof(polyNode));
    newNode->coef = coefficient;
    newNode->expon = exponent;
    if (poly == NULL) {
        poly = newNode;
        *ptr = newNode;
    }
    else {
        (*ptr)->link = newNode;
        *ptr = newNode;
    }
    (*ptr)->link = NULL;
    return poly;
}

polyPointer get_node(void) { //사용할 노드를 제공 
    polyPointer node;
    if(avail) { //리스트에 쓸 수 있는 가 있을때 /* avail node */
        node = avail;
        avail = avail->link;
    }
    else { //리스트에 쓸 수 있는 가 없을때 /* avail node */
        node = (polyPointer)malloc(sizeof(polyNode));
        if(IS_FULL(node)) {
            fprintf(stderr, "The memory is full\n"); //메모리가 가득 찼습니다
            exit(1);
        }
    }
    return node;
}

void cerase(polyPointer *ptr) {
/* ptr */ //원형 리스트 을 제거
    polyPointer temp;
    if(*ptr) {
        temp = (*ptr)->link;
        (*ptr)->link = avail;
        avail = temp;
        *ptr = NULL;
    }
}

void ret_node(polyPointer *ptr) {
    (*ptr)->link = avail;;
    avail = (*ptr);
}

void print_poly(polyPointer head) {
    polyPointer ptr;
    ptr = head;
    ptr = ptr->link;
    do {
        if(ptr->coef < 0){ //계수가 음수 일때 출력
            printf("-");
            printf("%.1fx^%d ", -(ptr->coef), ptr->expon);
            ptr = ptr->link;
        }
        else {
            printf("+"); //계수가 양수 일때 출력
            printf("%.1fx^%d ", ptr->coef, ptr->expon);
            ptr = ptr->link;
        }
    } while (ptr->link != head);
    printf("\n");
}

void print_poly2(polyPointer head) {
    polyPointer ptr;
    ptr = head;
    ptr = ptr->link;
    ptr = ptr->link;
    do {
        if(ptr->coef < 0){ //계수가 음수 일때 출력
            printf("-");
            printf("%.1fx^%d ", -(ptr->coef), ptr->expon);
            ptr = ptr->link;
        }
        else {
            printf("+"); //계수가 양수 일때 출력
            printf("%.1fx^%d ", ptr->coef, ptr->expon);
            ptr = ptr->link;
        }
    } while (ptr->link != head);
    printf("\n");
}

void print_poly3(polyPointer head) {
    polyPointer ptr;
    ptr = head;
    ptr = ptr->link;
    printf("\tcoef   expon\n");
    do {
        printf("\t%.2f\t%d\n", ptr->coef, ptr->expon);
        ptr = ptr->link;
    } while (ptr->link != head);
    printf("\n");
}

int main () {
    polyPointer a, b, d, ptr;
    printf("다항식 A(x)\n");
    create_polynomial(&a);

    ptr = a;
    ptr = ptr->link;
    print_poly3(a);
    printf("\nA(X) = %.1fx^%d ", ptr->coef, ptr->expon);
    print_poly(ptr);
    
    
    printf("\n다항식 B(x)\n");
    create_polynomial(&b);

    ptr = b;
    ptr = ptr->link;
    print_poly3(b);
    printf("\nB(X) = %.1fx^%d ", ptr->coef, ptr->expon);
    print_poly(ptr);

    d = cpmul(a, b);

    ptr = d;
    ptr = ptr->link;
    printf("\nD(X) = %.1fx^%d ", ptr->coef, ptr->expon);
    print_poly2(d);
    print_poly3(d);

    cerase(&a);
    cerase(&b);
    cerase(&d);
}