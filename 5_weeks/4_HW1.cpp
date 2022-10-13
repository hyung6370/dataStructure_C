#include <iostream>
#include <cstdlib>
#define MAX_STACK_SIZE 1000
#define MAX_QUEUE_SIZE 1000
using namespace std;

class Stack {
    int top;
    int data_stack[MAX_STACK_SIZE];
public:
    Stack() { top = -1; } 
    ~Stack() {}
    bool stackEmpty() { return top == -1; }   
    bool stackFull() { return top == MAX_STACK_SIZE-1; }  
    void push(int item) {
        if (stackFull())   
            exit(1);
        data_stack[++top] = item;    
    } 
    int pop() {
        if (stackEmpty())    
                exit(1);
        return data_stack[top--];    
    }
    int peek() {
        if (stackEmpty())    
                exit(1);
        return data_stack[top];    
    }
    void printStack() {   
        cout << "    index : item" << endl;
        for (int i = 0; i <= top; i++) {
            cout << "\t" << i << " :  "  << data_stack[i] << "\n";
        }
        cout << "\n";
    }
};

class Queue {
    int rear;
    int front;
    int data_queue[MAX_QUEUE_SIZE];
public:
    Queue() { front = -1; rear = -1;}
    ~Queue() {}
    bool queueFull() { return front == rear; }
    bool queueEmpty() { return front == rear; }
    void addQueue(int item) {
        rear = (rear+1) % MAX_QUEUE_SIZE;
        if (front == rear) {
            queueFull();
        }
        else {
            data_queue[rear] = item;
        }
    }
    int deleteQueue() {
        if (front == rear) {
            return queueEmpty();
        }
        else {
            front = (front+1) % MAX_QUEUE_SIZE;
            return data_queue[front];
        }
    }
    void printQueue() {
        cout << "    index : item" << endl;
        for (int i = front+1; i <= rear; i++) {
            cout << "\t" << i << " :  " << data_queue[i] << "\n";
        }
        cout << "\n";
    }
};


int main() {
    int firstChoiceNum;
    int choiceNum;
    int pushItem;
    int popItem;
    int addQItem;
    int deleteQItem;

    Stack s;
    Queue q;

    cout << "선택 - 1.스택 2.큐 : ";
    cin >> firstChoiceNum;

    if (firstChoiceNum == 1) {
        while(1) {
            cout << "스택 - 1.push 2.pop -1.exit : ";
            cin >> choiceNum;
            if (choiceNum == 1) {
                cout << "push item : ";
                cin >> pushItem;
                s.push(pushItem);
                s.printStack();
            }
            else if (choiceNum == 2) {
                cout << "pop item : ";
                cin >> popItem;
                s.pop();
                s.printStack();
            }
            else if (choiceNum == -1) {
                cout << "\n- 종료합니다.-\n\n";
                cout << "현재 스택 데이터\n";
                s.printStack();
                break;
            }
        }
    }
    else if (firstChoiceNum == 2) {
        while(1) {
            cout << "큐 - 1.addQ 2.deleteQ -1.exit : ";
            cin >> choiceNum;
            if (choiceNum == 1) {
                cout << "addQ item : ";
                cin >> addQItem;
                q.addQueue(addQItem);
                q.printQueue();
            }
            else if (choiceNum == 2) {
                cout << "deleteQ item : ";
                cin >> deleteQItem;
                q.deleteQueue();
                q.printQueue();
            }
            else if (choiceNum == -1) {
                cout << "\n- 종료합니다.-\n\n";
                cout << "현재 큐 데이터\n";
                q.printQueue();
                break;
            }
        }
    }
}