#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define size 10

int top = -1;

char s[size];

bool isFull() {
	return (top == size - 1);
}

bool isEmpty() {
	return (top == -1);
}

void push(char elem) {
	top++;
	s[top] = elem;
}

char pop() {
	char deleted = s[top];
	top--;
	return deleted;
}

char peek() {
	return s[top];
}

int icp(char ch) {
	if (ch == '+' || ch == '-')
		return 1;
	if (ch == '*' || ch == '/' || ch == '%')
		return 2;
	if (ch == '^')
		return 4;
	if (ch == '(')
		return 5;
	else
		return 0;
}

int isp(char ch) {
	if (ch == '+' || ch == '-')
		return 1;
	if (ch == '*' || ch == '/' || ch == '%')
		return 2;
	if (ch == '^')
		return 3;
	else
		return 0;
}

void in_post(char infix[], char postfix[]) {
	int k = 0, i = 0;
	char ch = infix[i];
	
	while (ch != '\0') {
		if (isalpha(ch)) {
			postfix[k] = infix[i];
			k++;
		}
		else {
			if (ch == '(') {
				push('(');
			}
			else {
				if (ch == ')') {
					while ((ch = pop()) != '(') {
						postfix[k] = ch;
						k++;
					}
				}
				else {
					while(!isEmpty() && isp(s[top]) >= icp(ch)) {
						postfix[k] = pop();
						k++;
					}
					push(ch);
				}
			}
		}
		i++;
		ch = infix[i];
	}
	while (!isEmpty()) {
		postfix[k] = pop();
		k++;
	}
	postfix[k] = '\0';
}

int main(void) {
	char infix[20], postfix[20];
	
	printf("Enter an infix expression: ");
	scanf("%s", infix);
	
	in_post(infix, postfix);
	
	printf("Postfix expression: ");
	int i = 0;
	while (postfix[i] != '\0') {
	    printf("%c ", postfix[i]);
	    i++;
	}
	printf("\n");
}
			
