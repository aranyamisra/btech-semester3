#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define size 10

int top = -1;
char s[size];

// stack

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

// for infix to postfix
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

void in_pre(char infix[], char prefix[]) {
	strrev(infix);
	int k = 0, i = 0;
	char ch = infix[i];
	
	while (ch != '\0') {
		if (isalpha(ch)) {
			prefix[k] = infix[i];
			k++;
		}
		else {
			if (ch == ')') {
				push(')');
			}
			else {
				if (ch == '(') {
					while ((ch = pop()) != ')') {
						prefix[k] = ch;
						k++;
					}
				}
				else {
					while(!isEmpty() && isp(s[top]) > icp(ch)) {
						prefix[k] = pop();
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
		prefix[k] = pop();
		k++;
	}
	prefix[k] = '\0';
	
	strrev(prefix);
}

// menu driven

int main(void) {
	printf("Choices:\n");
	printf("1. Push element\n");
	printf("2. Pop element\n");
	printf("3. View top element\n");
	printf("4. Check if full\n");
	printf("5. Check if empty\n");
	printf("6. Convert Infix to Postfix\n");
	printf("7. Convert Infix to Prefix\n");
	printf("8. Exit\n");

	while (1) {
		int choice;
		printf("\nEnter choice: ");
		scanf("%d", &choice);
		
		switch(choice) {
			case 1: {
				if (isFull()) {
					printf("Stack is full. Element cannot be inserted.\n");
				}
				else {
					char elem;
					printf("Enter character: ");
					scanf(" %c", &elem);
					push(elem);
				}
				break;
			}
			case 2: {
				if(isEmpty()) {
					printf("Stack is empty. No element to be deleted.\n");
				}
				else {
					char deleted = pop();
					printf("Element deleted = %c\n", deleted);
				}
				break;
			}
			case 3: {
				if (isEmpty()) {
					printf("Stack is empty.\n");
					break;
				}
				printf("Top element: %c\n", peek());
				break;
			}
			case 4: {
				if (isFull()) 
					printf("Stack is full.\n");
				else 
					printf("Stack is not full. %d of %d elements present.\n", top + 1, size);
				break;
			}
			case 5: {
				if (isEmpty()) 
					printf("Stack is empty.\n");
				else 
					printf("Stack is not empty. %d of %d elements present.\n", top + 1, size);
				break;
			}
			case 6: {
				char infix[20], postfix[20];

				top = -1; 

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
				break;
			}
			case 7: {
				char infix[20], prefix[20];

				top = -1; 

				printf("Enter an infix expression: ");
				scanf("%s", infix);

				in_post(infix, prefix);

				printf("Prefix expression: ");
				int i = 0;
				while (prefix[i] != '\0') {
					printf("%c ", prefix[i]);
					i++;
				}
				printf("\n");
				break;
			}
			case 8:
				printf("Program ended.\n");
				return 0;
			default:
				printf("Invalid choice.\n");
		}
	}
}

