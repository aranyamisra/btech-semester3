#include <stdio.h>
#include <stdbool.h>

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
	printf("Element inserted.\n");
}

char pop() {
	char deleted = s[top];
	top--;
	return deleted;
}

char peek() {
	return s[top];
}

int main(void) {
	printf("Choices:\n");
	printf("1. Push element\n");
	printf("2. Pop element\n");
	printf("3. View top element\n");
	printf("4. Check if full\n");
	printf("5. Check if empty\n");
	printf("6. Exit\n");
	
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
			
			case 6:
				printf("Program ended.\n");
				return 0;
			default:
				printf("Invalid choice.\n");
		}
	}
}
