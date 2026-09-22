#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define size 10

int top = -1;

int s[size];

bool isFull() {
	return (top == size - 1);
}

bool isEmpty() {
	return (top == -1);
}

void push(int elem) {
	top++;
	s[top] = elem;
}

int pop() {
	int deleted = s[top];
	top--;
	return deleted;
}

int peek() {
	return s[top];
}

int calculate(int op1, int op2, char operator) {
	switch (operator) {
	case '+':
		return op1 + op2;
	case '-':
		return op1 - op2;
	case '*':
		return op1 * op2;
	case '/':
		return op1 / op2;
	case '%':
		return op1 % op2;
	case '^': 
		return pow(op1, op2);
	default:
		printf("Invalid operator: %c\n", operator);
		return 0;
	}
}

void post_eval(char postfix[]) {
	for (int i = 0; postfix[i] != '\0'; i++) {
		char ch = postfix[i];

		if (isalpha(ch)) {
			int value;
			printf("Enter the value of %c: ", ch);
			scanf("%d", &value);
			push(value);
		} 
		else {
			int op2 = pop();
			int op1 = pop();
			int result = calculate(op1, op2, ch);
			push(result);
		}
	}
	printf("Result of postfix evaluation: %d\n", s[top]);
}

int main() {
	char postfix[20];

	printf("Enter a postfix expression: ");
	scanf("%s", postfix);

	post_eval(postfix);

	return 0;
}
