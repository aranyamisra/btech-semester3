#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define SIZE 10
#define LENGTH 10

// 2D STACK 

int top = -1;
char stk[SIZE][LENGTH];

bool isFull() {
	return top == SIZE - 1;
}

bool isEmpty() {
	return top == -1;
}

void push(char str[]) {
	if (isFull()) {
		printf("Stack Overflow\n");
		return;
	}
	top++;
	strcpy(stk[top], str);
}

char* pop() {
	if (isEmpty()) {
		printf("Stack Underflow\n");
		return NULL;
	}
	char* deleted = stk[top];
	top--;
	return deleted;
}

char* peek() {
	return stk[top];
}


// POSTFIX TO INFIX

void post_in(char postfix[], char infix[]) {
	for (int i = 0; postfix[i] != '\0'; i++) {
		char ch[2] = {postfix[i], '\0'};
		
		if (isalnum(ch[0])) {
			push(ch);
		}
		else {
			char *op2 = pop();
			char *op1 = pop();
			char exp[20];
			strcpy(exp, "(");
			strcat(exp, op1);
			strcat(exp, ch);
			strcat(exp, op2);
			strcat(exp, ")");
			push(exp);
		}
	}
	char *result = pop();
	if (result != NULL) {
		strcpy(infix, result);
	}
}

// POSTFIX TO PREFIX

void post_pre(char postfix[], char prefix[]) {
	for (int i = 0; postfix[i] != '\0'; i++) {
		char ch[2] = {postfix[i], '\0'};
		
		if (isalnum(ch[0])) {
			push(ch);
		}
		else {
			char *op2 = pop();
			char *op1 = pop();
			char exp[20];
			strcpy(exp, ch);
			strcat(exp, op1);
			strcat(exp, op2);
			push(exp);
		}
	}
	char *result = pop();
	if (result != NULL) {
		strcpy(prefix, result);
	}
}

// PREFIX TO INFIX

void revstring(char str[]) {
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

void pre_in(char prefix[], char infix[]) {

	char temp_prefix[20];
	strcpy(temp_prefix, prefix);
	revstring(temp_prefix);

	for (int i = 0; temp_prefix[i] != '\0'; i++) {
		char ch[2] = {temp_prefix[i], '\0'};
		
		if (isalnum(ch[0])) {
			push(ch);
		}
		else {
			char *op1 = pop();
			char *op2 = pop();
			char exp[20];
			strcpy(exp, "(");
			strcat(exp, op1);
			strcat(exp, ch);
			strcat(exp, op2);
			strcat(exp, ")");
			push(exp);
		}
	}
	char *result = pop();
	if (result != NULL) {
		strcpy(infix, result);
	}
}

// PREFIX TO POSTFIX

void pre_post(char prefix[], char postfix[]) {

	char temp_prefix[20];
	strcpy(temp_prefix, prefix);
	revstring(temp_prefix);

	for (int i = 0; temp_prefix[i] != '\0'; i++) {
		char ch[2] = {temp_prefix[i], '\0'};
		
		if (isalnum(ch[0])) {
			push(ch);
		}
		else {
			char *op1 = pop();
			char *op2 = pop();
			char exp[20];
			strcpy(exp, op1);
			strcat(exp, op2);
			strcat(exp, ch);
			push(exp);
		}
	}
	char *result = pop();
	if (result != NULL) {
		strcpy(postfix, result);
	}
}

// PRINT EXPRESSION

void printexp(char exp[]) {
    int i = 0;

    while (exp[i] != '\0') {
        printf("%c", exp[i]);
        i++;
    }

    printf("\n");
}

// MAIN FUNCTION

int main() {
	printf("Choices:\n");
	printf("1. Postfix to Infix\n");
	printf("2. Postfix to Prefix\n");
	printf("3. Prefix to Infix\n");
	printf("4. Prefix to Postfix\n");
	printf("5. Exit\n");
	
	while (1) {
		int choice;
		printf("\nEnter choice: ");
		scanf("%d", &choice);
		
		switch(choice) {
			case 1: {
				char postfix[20], infix[20];
				
				printf("Enter a postfix expression: ");
				scanf("%s", postfix);

				post_in(postfix, infix);

				printf("Infix expression: ");
				printexp(infix);

				break;
			}
			case 2: {
				char postfix[20], prefix[20];
				
				printf("Enter a postfix expression: ");
				scanf("%s", postfix);

				post_pre(postfix, prefix);

				printf("Prefix expression: ");
				printexp(prefix);

				break;
			}
			case 3: {
				char prefix[20], infix[20];
				
				printf("Enter a prefix expression: ");
				scanf("%s", prefix);

				pre_in(prefix, infix);

				printf("Infix expression: ");
				printexp(infix);

				break;
			}
			case 4: {
				char prefix[20], postfix[20];
				
				printf("Enter a prefix expression: ");
				scanf("%s", prefix);

				pre_post(prefix, postfix);

				printf("Postfix expression: ");
				printexp(postfix);

				break;
			}
			case 5:
				printf("Program ended.\n");
				return 0;
			default:
				printf("Invalid choice.\n");
		}
	}
}


