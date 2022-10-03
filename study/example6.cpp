#include<iostream>
#define MAX 100

//다항식 구조체 생성
struct Polynomial {
public:
	int exp;
	double coef;
};
int start1, start2, resultS;
int finish1, finish2, resultF;
int degree1, degree2;
int avail;
//구조체 배열 생성
Polynomial p[MAX];

using namespace std;

//다항식 출력 함수
void show(int start,int finish,Polynomial p[]) {
	//첫째항 출력
	cout << p[start].coef << "x^" << p[start].exp;

	for (int i = start+1; i < finish; i++) {
		cout << "+" << p[i].coef << "x^" << p[i].exp;
	}
	cout << "\n";
}

//비교함수 생성
int compare(int a, int b) {
	if (a > b) return 1; //a>b 이면 1 반환
	else if (a < b) return -1; //a<b 이면 -1 반환
	else return 0;	//a=b 이면 0 반환
}

//결과값 저장 함수 생성
void attach(double coef, int exp) {
	//다항식을 저장하는 공간이 배열의 범위를 초과했을때 종료
	if (avail >= MAX) {
		cout << "다항식의 항이 많습니다.\n";
		exit(1);
	}

	//결과를 저장공간에 저장
	p[avail].coef = coef;
	p[avail++].exp = exp;
}

//다항식 덧셈 함수 생성
void add(int start1, int finish1, int start2, int finish2, int& resultS, int& resultF) {

	
	resultS = avail;	//결과 공간의 첫번째 위치

	//두개의 다항식 모두 비교값이 존재 할때,
	while (start1 <= finish1 && start2 <= finish2) {
		//두개의 다항식 비교하기
		switch (compare(p[start1].exp, p[start2].exp)) {
			//다항식1의 차수가 더 큰 경우
		case 1:
			attach(p[start1].coef, p[start1].exp);	//다항식1의 차수를 결과 공간에 저장
			start1++; break;	//차수 감소

			//다항식2의 차수가 더 큰 경우
		case -1:
			attach(p[start2].coef, p[start2].exp);	//다항식2의 차수를 결과 공간에 저장
			start2 ++; break;	//차수 감소

			//다항식의 차수가 같은 경우
		case 0:
			double sum = p[start1].coef + p[start2].coef;	//다항식1과 다항식2를 더함
			attach(sum, p[start1].exp);	//더한값을 결과 공간에 저장
			start1++;	//차수 감소
			start2++;	//차수 감소
			break;
		}
	}

	//남은 다항식의 값들을 결과 공간에 저장

	for (int i = start1; i < finish1; i++) {
		attach(p[i].coef, p[i].exp);
	}
	for (int i = start2; i < finish2; i++) {
		attach(p[i].coef, p[i].exp);
	}

	resultF = avail - 1;	//결과 공간의 마지막 위치
}



//메인 함수
int main() {

	cout << "다항식1의 차수를 입력하세요:";
	cin >> degree1;

	//다항식1의 첫번째 위치
	start1 = 0;
	//다항식1의 마지막 위치
	finish1 = degree1 + 1;

	for (int i = 0; i <= degree1; i++) {
		//다항식1 차수 저장 
		p[i].exp = degree1 - i;
		cout << "x^(" << degree1 - i << ") 의 상수를 입력하세요:";
		//다항식1 상수 저장
		cin >> p[i].coef;
		
	}
	
	cout << "\n다항식2의 차수를 입력하세요:";
	cin >> degree2;

	//다항식2의 첫번째 위치
	start2 = finish1 + 1;
	//다항식2의 마지막 위치
	finish2 = start2 + degree2 + 1;

	for (int i = 0; i <= degree2; i++) {
		//다항식1 차수 저장 
		p[start2+i].exp = degree2 - i;

		cout << "x^(" << degree2 - i << ") 의 상수를 입력하세요:";
		//다항식1 상수 저장
		cin >> p[start2+i].coef;
	}
	//결과값을 저장할 시작 위치
	avail = finish2 + 1;

	//다항식1 출력
	cout << "\n다항식1: ";
	show(start1, finish1, p);
	//다항식2 출력
	cout << "다항식2: ";
	show(start2, finish2, p);

	cout << "\n다항식의 덧셈 결과:\n";
	add(start1, finish1, start2, finish2, resultS, resultF);

   //덧셈 결과 출력
	show(resultS, resultF, p);

}
