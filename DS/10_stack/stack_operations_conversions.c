#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define size 10

int top = -1;
char s[size];

// STACK OPERATIONS

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

// PRINT EXPRESSION

void printexp(char exp[]) {
    int i = 0;

    while (exp[i] != '\0') {
        printf("%c ", exp[i]);
        i++;
    }

    printf("\n");
}

// MAIN 

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

        switch (choice) {
            case 1: {
                if (isFull()) {
                    printf("Stack is full. Element cannot be inserted.\n");
                }
                else {
                    char elem;
                    printf("Enter character: ");
                    scanf(" %c", &elem);

                    push(elem);

                    printf("Element inserted = %c\n", elem);
                }
                break;
            }
            case 2: {
                if (isEmpty()) {
                    printf("Stack is empty. No element to be deleted.\n");
                }
                else {
                    char deleted = pop();
                    printf("Element deleted = %c\n", deleted);
                }
                break;
            }
            case 3: {
                if (isEmpty()) 
                    printf("Stack is empty.\n");
                else
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
                printexp(postfix);

                break;
            }
            case 7: {
                char infix[20], prefix[20];

                top = -1;

                printf("Enter an infix expression: ");
                scanf("%s", infix);

                in_pre(infix, prefix);

                printf("Prefix expression: ");
                printexp(prefix);

                break;
            }
            case 8:
                printf("Program ended.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}