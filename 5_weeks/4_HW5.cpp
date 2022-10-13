#include <iostream>
#include <cstdlib>
#include <string>
#define MAX_STACK_SIZE 10000
using namespace std;

template <typename T>

class Stack {
private:
    T data[MAX_STACK_SIZE];
    int top;

public:
    Stack() {
        top = -1;
    }
    ~Stack();
    void push(T inputStack) {
        data[top + 1] = inputStack;
        top += 1;
    }
    T pop() {
        T res = data[top];
        top -= 1;
        return res;
    }
    int size() {
        return top+1;
    }
    bool empty() {
        return size() == 0 ? true : false;
    }
    T top_p() {
        T res = data[top];
        return res;
    }
};

int main() {

}