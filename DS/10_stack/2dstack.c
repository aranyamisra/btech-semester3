#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define SIZE 10
#define LENGTH 10

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

int main() {
	push("hello");
	push("world");
	
	printf("Top element = %s\n", peek());
	
	char* deleted = pop();
	printf("Deleted element = %s\n", deleted);
}
