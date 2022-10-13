#include <iostream>
#include <cstdlib>
using namespace std;

inline void error(char* message)   // 에러메세지를 포인터로 받아서 출력하는 함수
{
    cout << message << endl;
    exit(1);
}

const int MAX_STACK_SIZE = 20;

class Stack
{
    int top;
    int data[MAX_STACK_SIZE];
public:
    Stack() { top = -1; }   // 비어있는 스택의 생성자
    ~Stack() {}
    bool isEmpty() { return top == -1; }   // 스택이 비어있으면 true, 아니면 false를 반환
    bool isFull() { return top == MAX_STACK_SIZE-1; }   // 가득 차있으면 true, 아니면 false를 반환
    void push(int n)
    {
            if (isFull())    // 만약 스택이 가득 차있다면 error함수 호출 -> 프로그램 종료
                error((char*)"스택 포화 에러");
            data[++top] = n;    // 아니면 top값을 하나 증가시킨 후, 받은 값을 대입
    }
    int pop()
    {
            if (isEmpty())    // 만약 스택이 비어있다면 error함수 호출 -> 프로그램 종료
                    error((char*)"스택 공백 에러");
            return data[top--];    // 아니면 현재 top인 값을 내보낸 후, top값을 하나 감소
    }
    int peek()
    {
            if (isEmpty())    // 만약 스택이 비어있다면 error함수 호출 -> 프로그램 종료
                    error((char*)"스택 공백 에러");
            return data[top];    // 아니면 top값 반환, but pop과 달리 top값을 줄이지는 않음
    }
    void display()    // 현재 스택의 항목 수와 요소를 모두 출력
    {
            cout << "    index : item" << endl;

            for (int i = 0; i <= top; i++) {
                cout << "\t" << i << " :  "  << data[i] << "\n";
            }
            cout << "\n";
            }
};

int main()
{
    // ArrayStack stack;

    // stack.push(45);
    // stack.push(30);
    // stack.display();
    // cout << endl;

    // cout << stack.peek() << endl;
    // stack.display();
    // cout << endl;

    // stack.pop();
    // stack.display();
    // cout << endl;
    int choiceNum;
    int pushItem;
    int popItem;

    Stack s;

    while(1) {
        cout << "스택 - 1.push 2.pop -1.exit : ";
        cin >> choiceNum;
        if (choiceNum == 1) {
            cout << "push item : ";
            cin >> pushItem;
            s.push(pushItem);
            s.display();
        }
        else if (choiceNum == 2) {
            cout << "pop item : ";
            cin >> popItem;
            s.pop();
            s.display();
        }
        else if (choiceNum == -1) {
            cout << "\n- 종료합니다.-\n\n";
            cout << "현재 스택 데이터\n";
            s.display();
            break;
        }
    }
}