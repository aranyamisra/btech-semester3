#include <stdio.h>
#include <stdbool.h>

#define size 5

struct job {
	int id;
	char title[20];
};

int front = -1, rear = -1;

bool isFull() {
	if (rear == size - 1)
		return true;
	return false;
}

bool isEmpty() {
	if (front == rear) 
		return true;
	return false;
}

void enqueue(struct job q[], struct job elem) {
	if (isFull())
		printf("Queue is full.\n");
	else {
		rear++;
		q[rear] = elem;
	}
}



void dequeue(struct job q[]) {
	if (isEmpty()) 
		printf("Queue is empty.\n");
	else {
		front++;
		struct job deleted = q[front];
		printf("Deleted element:\n");
		printf("Job ID: %d\n", deleted.id);
		printf("Job title: %s\n", deleted.title);
	}
}

struct job acceptelement() {
	struct job elem;
	printf("Enter element to add:\n");
	printf("Enter job id and title: ");
	scanf("%d%s", &elem.id, elem.title);
	return elem;
}


void display(struct job q[]) {
    printf("Job Details\n");
    printf("%-10s %-20s\n", "Job ID", "Title");
    for (int i = front + 1; i <= rear; i++) {
        printf("%-10d %-20s\n", q[i].id, q[i].title);
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
				struct job elem = acceptelement();
				enqueue(q, elem);
				break;
			}
			case 2: 
				dequeue(q);
				break;
			case 3: {
				if (isFull())
					printf("Queue is full.\n");
				else {
                    printf("Queue is not full.\n");
					int current = rear - front;
					printf("%d out of %d spaces filled in the queue.\n", current, size);
				}
				break;
			}
			case 4: {
				if (isEmpty())
					printf("Queue is empty.\n");
				else {
                    printf("Queue is not empty.\n");
					int current = rear - front;
					printf("%d out of %d spaces filled in the queue.\n", current, size);
				}
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