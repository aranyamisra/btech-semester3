#include <stdio.h>
#include <stdbool.h>

#define size 5

struct job {
	int id;
	char title[20];
};

int front = 0, rear = 0;

bool isFull() {
	if ((rear + 1) % size == front)
		return true;
	return false;
}

bool isEmpty() {
	if (front == rear) 
		return true;
	return false;
}

void enqueue(struct job q[], struct job elem) {
	rear = (rear + 1) % size;
	q[rear] = elem;
}

void dequeue(struct job q[]) {
	front = (front + 1) % size;
	struct job deleted = q[front];
	printf("Deleted element:\n");
	printf("Job ID: %d\n", deleted.id);
	printf("Job title: %s\n", deleted.title);
}

struct job acceptelement() {
	struct job elem;
	printf("Enter job id and title for element to add: ");
	scanf("%d%s", &elem.id, elem.title);
	return elem;
}


void display(struct job q[]) {
	if (isEmpty())
		printf("Queue is empty.\n");

	else {
		printf("Job Details\n");
		printf("%-10s %-20s\n", "Job ID", "Title");
		
		int i = (front + 1) % size;
		while (1) {
			printf("%-10d %-20s\n", q[i].id, q[i].title);
			if (i == rear)
				break;
			i = (i + 1) % size;
		}
	}
}

int main (void) {
	struct job q[size];
	
	printf("Choices:\n");
	printf("1. Add an element at rear (enqueue)\n");
	printf("2. Delete element at front (dequeue)\n");
	printf("3. Check if queue is full\n");
	printf("4. Check if queue is empty\n");
	printf("5. Display elements\n");
	printf("6. Exit\n");
	
	while (1) {
		int choice;
		printf("\nEnter choice: ");
		scanf("%d", &choice);
		
		switch(choice) {
			case 1: {
				if (isFull()) {
					printf("Queue is full.\n");
					break;
				}
				struct job elem = acceptelement();
				enqueue(q, elem);
				break;
			}
			case 2: 
				if (isEmpty()) {
					printf("Queue is empty.\n");
					break;
				}
				dequeue(q);
				break;
			case 3: {
				if (isFull())
					printf("Queue is full.\n");
				else 
                    printf("Queue is not full.\n");
				break;
			}
			case 4: {
				if (isEmpty())
					printf("Queue is empty.\n");
				else
                    printf("Queue is not empty.\n");
				break;
			}
			case 5:
				display(q);
				break;
			case 6:
				printf("Program ended.\n");
				return 0;
			default:
				printf("Invalid choice.\n");
		}
	}
}
