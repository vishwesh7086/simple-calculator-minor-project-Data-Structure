#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char ch) {
    stack[++top] = ch;
}

char pop() {
    return stack[top--];
}

int precedence(char ch) {
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    return 0;
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

void infixToPostfix(char infix[], char postfix[]) {
    int i, j = 0;
    char ch;
    for (i = 0; infix[i] != '\0'; i++) {
        ch = infix[i];
        if (isdigit(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(ch);
        } else if (ch == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = pop();
            }
            pop();
        } else if (isOperator(ch)) {
            while (top != -1 && precedence(stack[top]) >= precedence(ch)) {
                postfix[j++] = pop();
            }
            push(ch);
        }
    }
    while (top != -1) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

int evaluatePostfix(char postfix[]) {
    int valStack[MAX];
    int topVal = -1;
    int i, a, b;
    for (i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i])) {
            valStack[++topVal] = postfix[i] - '0';
        } else {
            b = valStack[topVal--];
            a = valStack[topVal--];
            switch (postfix[i]) {
                case '+': valStack[++topVal] = a + b; break;
                case '-': valStack[++topVal] = a - b; break;
                case '*': valStack[++topVal] = a * b; break;
                case '/': valStack[++topVal] = a / b; break;
            }
        }
    }
    return valStack[topVal];
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter infix expression (no spaces): ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    printf("Result: %d\n", evaluatePostfix(postfix));
    return 0;
}
