#include <stdio.h>
#include <stdlib.h>

struct node {
	int regno;
	char name[20];
	struct node *next;
};

void createll(struct node* head) {
	struct node *temp = head;
	
	char choice;
	
	printf("Creating a singly linked list:\n");
	do {
		struct node* newnode = (struct node*)malloc(sizeof(struct node));
		
		printf("\nEnter registration no.: ");
		scanf("%d", &newnode->regno);
		printf("Enter name: ");
		scanf("%s", newnode->name);

		newnode->next = NULL;
		
		temp->next = newnode;
		temp = newnode;
		
		printf("Do you want to add more nodes? (y/n): ");
		scanf(" %c", &choice);
		
	} while (choice == 'y');
}

void display(struct node* head) {
	struct node* curr = head->next;
	
	if (curr == NULL) {
		printf("The linked list is empty.\n");
		return;
	}

	printf("\nStudent details: \n");
	printf("%-10s %-20s\n", "Reg No.", "Name");
	while(curr != NULL) {
		printf("%-10d %-20s\n", curr->regno, curr->name);
		curr = curr->next;
	}
}

int length(struct node* head) {
	int len = 0;
	struct node *curr = head->next;
	while (curr != NULL) {
		len++;
		curr = curr->next;
	}
	return len;
}	

void insertByPos(struct node *head, int pos) {
	int len = length(head);
	if (pos < 1 || pos > len + 1) {
		printf("Invalid position. Please enter a position between 1 and %d.\n", len + 1);
		return;
	}

	struct node* newnode = (struct node*)malloc(sizeof(struct node));
		
	printf("Enter registration no.: ");
	scanf("%d", &newnode->regno);
	printf("Enter name: ");
	scanf("%s", newnode->name);

	newnode->next = NULL;

	struct node *curr = head;
	int i = 1;
	while (curr->next != NULL && i < pos) {
		curr = curr->next;
		i++;
	}
	
	newnode->next = curr->next;
	curr->next = newnode;
}

void deleteByPos(struct node *head, int pos) {
	int len = length(head);
	if (pos < 1 || pos > len) {
		printf("Invalid position. Please enter a position between 1 and %d.\n", len);
		return;
	}

	struct node *prev = head;
	struct node *curr = head->next;
	int i = 1;

	while (curr != NULL && i < pos) {
		prev = curr;
		curr = curr->next;
		i++;
	}
	
	prev->next = curr->next;
	curr->next = NULL;
	free(curr);
}

void sortList(struct node *head) {
	int len = length(head);
	if (len < 2) {
		return; // no need to sort if the list has less than 2 nodes
	}

	struct node *prev, *curr;

	for (int i = 0; i < len - 1; i++) {
		prev = head;
		curr = head->next;
		for (int j = 0; j < len - i - 1; j++) {
			struct node *temp = curr->next;

			if (curr->regno > temp->regno) {
				prev->next = temp;
				curr->next = temp->next;
				temp->next = curr;
				prev = temp;
			} 
			else {
				prev = curr;
				curr = curr->next;
			}
		}
	}
}

void reverseList(struct node *head) {
	struct node *prev = NULL;
	struct node *curr = head->next;
	struct node *future = NULL;

	while (curr != NULL) {
		future = curr->next;
		curr->next = prev;
		prev = curr;
		curr = future;
	}
	head->next = prev;
}

int main(void)
{
	struct node* head = (struct node*)malloc(sizeof(struct node));
	createll(head);
	display(head);

	printf("\nChoices: \n");
	printf("1. Insert a node at a specific position\n");
	printf("2. Delete a node at a specific position\n");
	printf("3. Sort the linked list by registration number\n");
	printf("4. Reverse the linked list\n");
	printf("5. Display the linked list\n");
	printf("6. Exit\n");

	while(1) {
		int choice;
		printf("\nEnter your choice: ");
		scanf("%d", &choice);

		switch(choice) {
			case 1: {
				int pos;
				printf("Enter the position to insert the node: ");
				scanf("%d", &pos);
				insertByPos(head, pos);
				break;
			}
			case 2: {
				int pos;
				printf("Enter the position to delete the node: ");
				scanf("%d", &pos);
				deleteByPos(head, pos);
				break;
			}
			case 3:
				sortList(head);
				printf("The linked list has been sorted.\n");
				break;
			case 4:
				reverseList(head);
				printf("The linked list has been reversed.\n");
				break;
			case 5:
				display(head);
				break;
			case 6:
				printf("Exiting...\n");
				return 0;
			default:
				printf("Invalid choice. Please try again.\n");
		}
	}
}
