#include <stdio.h>
#include <stdlib.h>
#define IS_FULL(ptr) ((!ptr))
#define COMPARE(x,y) (((x)<(y)) ? -1: ((x)==(y)) ? 0: 1)
#define _CRT_SECURE_NO_WARNINGS

typedef struct polyNode *polyPointer;
typedef struct polyNode {
    float coef;
    int expon;
    polyPointer link;
} polyNode;

static polyPointer avail;

polyPointer get_node(void);
polyPointer create_polynomial();
polyPointer padd(polyPointer a, polyPointer b);
polyPointer pmul(polyPointer a, polyPointer b);
void attach(float coefficient, int exponent, polyPointer *ptr);
polyPointer attach_mul(polyPointer poly, float coefficient, int exponent, polyPointer *ptr);
void cerase(polyPointer *ptr);
void ret_node(polyPointer *ptr);
void print_poly(polyPointer front);

polyPointer get_node(void) { //사용할 노드를 제공 
    polyPointer node;
    if (avail) { //리스트에 쓸 수 있는 가 있을때
        node = avail;
        avail = avail->link;
    }
    else { //리스트에 쓸 수 있는 가 없을때
        node = (polyPointer)malloc(sizeof(polyNode));
        if (IS_FULL(node)) {
            fprintf(stderr, "The memory is full\n"); //메모리가 가득 찼습니다
            exit(1);
        }
    }
    return node;
}

polyPointer create_polynomial() {
    polyPointer temp, front, rear;
    int i = 1;
    int key;
    int inputCoef, inputExpon;

    // rear = (polyPointer)malloc(sizeof(polyNode));
    rear = get_node();

    front = rear;
    rear->link = NULL;
    while (1) {
        printf("다항식의 항을 입력하세요. (coef expon) : ");
        scanf("%d %d", &inputCoef, &inputExpon);

        if (inputCoef == -1 && inputExpon == -1) {break;}
        if (i != 1) {
            while (rear->link && key) {
                temp = rear->link;
                switch (COMPARE(temp->expon, inputExpon)) {
                    case -1:
                        attach(inputCoef, inputExpon, &rear);
                        rear->link = temp;
                        key = 0;
                        break;
                    
                    case 0:
                        temp->coef += inputCoef;
                        if (!temp->coef) {
                            rear->link = temp->link;
                        }
                        key = 0;
                        break;

                    case 1:
                        rear = temp;
                }
            }
        }
        if (i == 1 || key) {
            attach(inputCoef, inputExpon, &rear);
        }
        key = 1;
        rear = front;
        i++;        
    }
    temp = front;
    front = front->link;

    free(temp);
    return front;
}


polyPointer padd(polyPointer a, polyPointer b) {
    // a와 b가 합산된 다항식을 반환
    polyPointer front, rear, temp;
    int sum;
    rear = (polyPointer)malloc(sizeof(polyNode));
    front = rear;
    while (a && b) {
        switch(COMPARE(a->expon, b->expon)) {
			case -1 : attach(b->coef, b->expon, &rear);
						b=b->link;
						break ;
			case 0	: sum = a->coef + b->coef;
					if (sum) attach(sum, a->expon, &rear);
                    a = a->link;
                    b = b->link;
					break;
			case 1  : attach(a->coef ,a->expon, &rear);
					a = a->link;
		}
    }
    // 리스트 a와 리스트 b의 나머지를 복사
        for (; a; a = a->link) attach(a->coef, a->expon, &rear);
        for (; b; b = b->link) attach(b->coef, b->expon, &rear);
        rear->link = NULL;

        // 필요없는 처음 노드를 삭제
        temp = front;
        front = front->link;
        free(temp);
        return front;
}

polyPointer pmul(polyPointer a, polyPointer b) {
    polyPointer p, q, r, c, result;
    q = b;
    c = NULL;
    while (q != NULL) {
        p = a;
        r = NULL;
        result = NULL;
        while (p != NULL) {
            result = attach_mul(result, p->coef * q->coef, p->expon + q->expon, &r);
            p = p->link;
        }
        c = padd(c, result);
        q = q->link;
    }
    return c;
}

void attach(float coefficient, int exponent, polyPointer *ptr) {
    // coef = coefficient이고 expon = exponent인 새로운 노드를 생성하고, 그것을 ptr에 의해 참조
    // 되는 노드에 첨가한다. ptr을 갱신하여 이 새로운 노드를 참조하도록 한다.
    polyPointer temp;
    temp = (polyPointer)malloc(sizeof(polyNode));
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

void cerase(polyPointer *ptr) {
    //원형 리스트 을 제거
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

void print_poly(polyPointer front)  {
    while (front != NULL) {
        printf("%.1fx^%d", front->coef, front->expon);
        front = front->link;
        if (front != NULL && front->coef > 0) printf("+");
    }
    printf("\n");
}

void print_poly2(polyPointer front) {
    printf("\tcoef   expon\n");
    while (front != NULL) {
        printf("\t%.2f\t%d\n", front->coef, front->expon);
        front = front->link;
    }
    printf("\n");
}

int main() {
    polyPointer a, b, d;

    printf("singul_mul - C1(x)\n");
    a = create_polynomial();
    printf("\nsingul_mul - C1(x)\n");
    print_poly2(a);
    printf("C1(x) = ");
    print_poly(a);

    printf("\nsingul_mul - C2(x)\n");
    b = create_polynomial();
    printf("\nsingul_mul - C2(x)\n");
    print_poly2(b);
    printf("C2(x) = ");
    print_poly(b);

    d = pmul(a, b);

    printf("\n 다항식 곱셈 결과 : D(x) \n");
    print_poly2(d);
    printf("D(x) = ");
    print_poly(d);

    cerase(&a);
    cerase(&b);
    cerase(&d);
}