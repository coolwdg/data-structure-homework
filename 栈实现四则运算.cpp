#include<iostream>
#include <cstring>
using namespace std;
const int MAX_SIZE = 100;

bool isEmpty(int top) {
    return top == -1;
}

bool isFull(int top) {
    return top == MAX_SIZE - 1;
}

void push(int stack[], int& top, int item) {
    if (isFull(top)) {
        cout << "Stack overflow" << endl;
        return;
    }
    stack[++top] = item;
}

int pop(int stack[], int& top) {
    if (isEmpty(top)) {
        cout << "Stack underflow" << endl;
        return -1;
    }
    return stack[top--];
}

int peek(int stack[], int top) {
    if (isEmpty(top)) {
        cout << "Stack is empty" << endl;
        return -1;
    }
    return stack[top];
}

int getPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}
int q = 0;
int evaluateInfix(const string& expression) {
    int operandStack[MAX_SIZE];
    int operatorStack[MAX_SIZE];
    int operandTop = -1;
    int operatorTop = -1;
    
    if (expression[0] == '-' && expression[1] == '(')
    {
        q = 1;
    }
    for (int i = q; i < expression.length(); i++) {
        char ch = expression[i];
        if (isdigit(ch)) {
            int operand = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                operand = operand * 10 + (expression[i] - '0');
                i++;
            }
         push(operandStack, operandTop, operand); 
            i--;
        }
        else if (ch == '(') {
            push(operatorStack, operatorTop, ch);
        }
        else if (ch == ')') {
            while (!isEmpty(operatorTop) && peek(operatorStack, operatorTop) != '(') {
                int b = pop(operandStack, operandTop);
                int a = pop(operandStack, operandTop);
                char op = pop(operatorStack, operatorTop);
                int result;
                switch (op) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
                default:
                    result = 0;
                }
                push(operandStack, operandTop, result);
            }
            pop(operatorStack, operatorTop);
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!isEmpty(operatorTop) && getPrecedence(peek(operatorStack, operatorTop)) >= getPrecedence(ch)) {
                int b = pop(operandStack, operandTop);
                int a = pop(operandStack, operandTop);
                char op = pop(operatorStack, operatorTop);
                int result;
                switch (op) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
                default:
                    result = 0;
                }
                push(operandStack, operandTop, result);
            }
            push(operatorStack, operatorTop, ch);
        }
    }

    while (!isEmpty(operatorTop)) {
        int b = pop(operandStack, operandTop);
        int a = pop(operandStack, operandTop);
        char op = pop(operatorStack, operatorTop);
        int result;
        switch (op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        default:
            result = 0;
        }
        push(operandStack, operandTop, result);
    }

    return pop(operandStack, operandTop);
}

int main() {
    string a;
    cin >> a;
    int result = evaluateInfix(a);
    if (q == 1)
    {
        result = -result;
    }
    cout << "result=" << result << endl;

    return 0;
}
