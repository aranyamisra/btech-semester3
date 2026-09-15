#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

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

int icp_post(char ch) {
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

int isp_post(char ch) {
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
					while(!isEmpty() && isp_post(s[top]) >= icp_post(ch)) {
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

int icp_pre(char ch) {
	if (ch == '+' || ch == '-')
		return 1;
	if (ch == '*' || ch == '/' || ch == '%')
		return 2;
	if (ch == '^')
		return 3;
	if (ch == '(')
		return 5;
	else
		return 0;
}

int isp_pre(char ch) {
	if (ch == '+' || ch == '-')
		return 1;
	if (ch == '*' || ch == '/' || ch == '%')
		return 2;
	if (ch == '^')
		return 4;
	else
		return 0;
}

void revstring(char* str) {
    int i = 0;
    int j = strlen(str) - 1;
    
    char temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

void in_pre(char infix[], char prefix[]) {
	char temp_infix[20];
	strcpy(temp_infix, infix);
	
	revstring(temp_infix);
	
	int k = 0, i = 0;
	char ch = temp_infix[i];
	
	while (ch != '\0') {
		if (isalpha(ch)) {
			prefix[k] = temp_infix[i];
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
					while(!isEmpty() && isp_pre(s[top]) > icp_pre(ch)) {
						prefix[k] = pop();
						k++;
					}
					push(ch);
				}
			}
		}
		i++;
		ch = temp_infix[i];
	}
	while (!isEmpty()) {
		prefix[k] = pop();
		k++;
	}
	prefix[k] = '\0';
	
	revstring(prefix);
}

void printexp(char exp[]) {
	int i = 0;
	while (exp[i] != '\0') {
	    printf("%c", exp[i]);
	    i++;
	}
	printf("\n");
}

int main(void) {
	char infix[20], postfix[20], prefix[20];
	
	printf("Enter an infix expression: ");
	scanf("%s", infix);
	
	printf("\nChoices:\n");
	printf("1. Infix to postfix\n");
	printf("2. Infix to prefix\n");
	printf("3. Exit\n");
	
	while (1) {
		int choice;
		printf("\nEnter choice: ");
		scanf("%d", &choice);
		
		switch(choice) {
			case 1: {
				in_post(infix, postfix);
				printf("Postfix expression: ");
				printexp(postfix);
				break;
			}
			case 2: {
				in_pre(infix, prefix);
				printf("Prefix expression: ");
				printexp(prefix);
				break;
			}
			case 3:
				printf("Program ended.\n");
				return 0;
			default:
				printf("Invalid choice. Please try again.\n");
				break;
		}
	}		
	
}
			
