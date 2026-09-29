#include <stdio.h>
#include <stdlib.h>

struct studentnode {
	int regno;
	char name[20];
	struct studentnode *next;
};

void createll(struct studentnode* head) {
	struct studentnode *prev = (struct studentnode*)malloc(sizeof(struct studentnode));
	prev = head;
	
	char choice;
	
	printf("Creating a singly linked list:\n");
	do {
		struct studentnode* newnode = (struct studentnode*)malloc(sizeof(struct studentnode));
		
		newnode->next = NULL;
		
		printf("\nEnter registration no.: ");
		scanf("%d", &newnode->regno);
		printf("Enter name: ");
		scanf("%s", newnode->name);
		
		prev->next = newnode;
		prev = newnode;
		
		printf("Do you want to add more nodes? (y/n): ");
		scanf(" %c", &choice);
		
	} while (choice == 'y');
	
}

void display(struct studentnode* head) {
	struct studentnode* ptr = head->next;
	
	printf("\nStudent details: \n");
	while(ptr != NULL) {
		printf("Registration no.: %d\n", ptr->regno);
		printf("Name: %s\n", ptr->name);
		ptr = ptr->next;
	}
}

int length(struct studentnode* head) {
	int len = 0;
	struct studentnode *ptr = head->next;
	while (ptr != NULL)
}	

int main(void)
{
	struct studentnode* head = (struct studentnode*)malloc(sizeof(struct studentnode));
	createll(head);
	display(head);
}
