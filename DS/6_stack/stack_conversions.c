#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define SIZE 10
#define LENGTH 10

int top = -1;

bool isFull() {
    return (top == SIZE - 1);
}

bool isEmpty() {
    return (top == -1);
}

// 1D STACK
char s[SIZE];

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

// 2D STACK 
char stk[SIZE][LENGTH];

void push2d(char str[]) {
	if (isFull()) {
		printf("Stack Overflow\n");
		return;
	}
	top++;
	strcpy(stk[top], str);
}

char* pop2d() {
	if (isEmpty()) {
		printf("Stack Underflow\n");
		return NULL;
	}
	char* deleted = stk[top];
	top--;
	return deleted;
}

char* peek2d() {
	return stk[top];
}

// INFIX TO POSTFIX

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
            postfix[k] = ch;
            k++;
        }
        else {
            if (ch == '(') {
                push('(');
            }
            else if (ch == ')') {
                while (!isEmpty() && (ch = pop()) != '(') {
                    postfix[k] = ch;
                    k++;
                }
            }
            else {
                while (!isEmpty() &&
                       isp_post(s[top]) >= icp_post(ch)) {
                    postfix[k] = pop();
                    k++;
                }
                push(ch);
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

// INFIX TO PREFIX 

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

// Reverse a string
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

void in_pre(char infix[], char prefix[]) {

    char temp_infix[20];

    strcpy(temp_infix, infix);

    revstring(temp_infix);

    int k = 0, i = 0;
    char ch = temp_infix[i];

    while (ch != '\0') {

        if (isalpha(ch)) {
            prefix[k] = ch;
            k++;
        }
        else {
        	if (ch == ')') {
                push(')');
            }
            else if (ch == '(') {
                while (!isEmpty() && (ch = pop()) != ')') {
                    prefix[k] = ch;
                    k++;
                }
            }
            else {
                while (!isEmpty() &&
                       isp_pre(s[top]) > icp_pre(ch)) {
                    prefix[k] = pop();
                    k++;
                }
                push(ch);
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

// POSTFIX TO INFIX

void post_in(char postfix[], char infix[]) {
	for (int i = 0; postfix[i] != '\0'; i++) {
		char ch[2] = {postfix[i], '\0'};
		
		if (isalnum(ch[0])) {
			push2d(ch);
		}
		else {
			char *op2 = pop2d();
			char *op1 = pop2d();
			char exp[20];
			strcpy(exp, "(");
			strcat(exp, op1);
			strcat(exp, ch);
			strcat(exp, op2);
			strcat(exp, ")");
			push2d(exp);
		}
	}
	char *result = pop2d();
	if (result != NULL) {
		strcpy(infix, result);
	}
}

// POSTFIX TO PREFIX

void post_pre(char postfix[], char prefix[]) {
	for (int i = 0; postfix[i] != '\0'; i++) {
		char ch[2] = {postfix[i], '\0'};
		
		if (isalnum(ch[0])) {
			push2d(ch);
		}
		else {
			char *op2 = pop2d();
			char *op1 = pop2d();
			char exp[20];
			strcpy(exp, ch);
			strcat(exp, op1);
			strcat(exp, op2);
			push2d(exp);
		}
	}
	char *result = pop2d();
	if (result != NULL) {
		strcpy(prefix, result);
	}
}

// PREFIX TO INFIX

void pre_in(char prefix[], char infix[]) {

	char temp_prefix[20];
	strcpy(temp_prefix, prefix);
	revstring(temp_prefix);

	for (int i = 0; temp_prefix[i] != '\0'; i++) {
		char ch[2] = {temp_prefix[i], '\0'};
		
		if (isalnum(ch[0])) {
			push2d(ch);
		}
		else {
			char *op1 = pop2d();
			char *op2 = pop2d();
			char exp[20];
			strcpy(exp, "(");
			strcat(exp, op1);
			strcat(exp, ch);
			strcat(exp, op2);
			strcat(exp, ")");
			push2d(exp);
		}
	}
	char *result = pop2d();
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
			push2d(ch);
		}
		else {
			char *op1 = pop2d();
			char *op2 = pop2d();
			char exp[20];
			strcpy(exp, op1);
			strcat(exp, op2);
			strcat(exp, ch);
			push2d(exp);
		}
	}
	char *result = pop2d();
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
	printf("1. Infix to Postfix\n");
	printf("2. Infix to Prefix\n");
	printf("3. Postfix to Infix\n");
	printf("4. Postfix to Prefix\n");
	printf("5. Prefix to Infix\n");
	printf("6. Prefix to Postfix\n");
	printf("7. Exit\n");
	
	while (1) {
		int choice;
		printf("\nEnter choice: ");
		scanf("%d", &choice);
		
		switch(choice) {
			case 1: {
				char infix[20], postfix[20];

				printf("Enter an infix expression: ");
				scanf("%s", infix);

				in_post(infix, postfix);

				printf("Postfix expression: ");
				printexp(postfix);

				break;
			    }
			    case 2: {
				char infix[20], prefix[20];

				printf("Enter an infix expression: ");
				scanf("%s", infix);

				in_pre(infix, prefix);

				printf("Prefix expression: ");
				printexp(prefix);

				break;
			    }
			case 3: {
				char postfix[20], infix[20];
				
				printf("Enter a postfix expression: ");
				scanf("%s", postfix);

				post_in(postfix, infix);

				printf("Infix expression: ");
				printexp(infix);

				break;
			}
			case 4: {
				char postfix[20], prefix[20];
				
				printf("Enter a postfix expression: ");
				scanf("%s", postfix);

				post_pre(postfix, prefix);

				printf("Prefix expression: ");
				printexp(prefix);

				break;
			}
			case 5: {
				char prefix[20], infix[20];
				
				printf("Enter a prefix expression: ");
				scanf("%s", prefix);

				pre_in(prefix, infix);

				printf("Infix expression: ");
				printexp(infix);

				break;
			}
			case 6: {
				char prefix[20], postfix[20];
				
				printf("Enter a prefix expression: ");
				scanf("%s", prefix);

				pre_post(prefix, postfix);

				printf("Postfix expression: ");
				printexp(postfix);

				break;
			}
			case 7:
				printf("Program ended.\n");
				return 0;
			default:
				printf("Invalid choice.\n");
		}
	}
}


