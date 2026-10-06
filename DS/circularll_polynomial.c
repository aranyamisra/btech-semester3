#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Polynomial term
struct node {
	int coef;
	int exp;
	struct node *next;
};

void createll(struct node* head) {
	struct node *prev = head;
	
	char choice;
	
	printf("Creating a polynomial using circular singly linked list:\n");
	do {
		int temp_coef, temp_exp;
		printf("\nEnter coefficient and exponent: ");
		scanf("%d%d", &temp_coef, &temp_exp);
		
		struct node *curr = head->next;
		bool found = false;

		while (curr != head) {
			if (curr->exp == temp_exp) {
				curr->coef += temp_coef;
				printf("Exponent %d already exists. Added coefficients.\n", temp_exp);
				found = true;
				break;
			}
			curr = curr->next;
		}
		
		if (!found) {
			prev = head;
			while (prev->next != head) {
				prev = prev->next;
			}
			
			struct node* newnode = (struct node*)malloc(sizeof(struct node));
			newnode->coef = temp_coef;
			newnode->exp = temp_exp;
			newnode->next = head;
			
			prev->next = newnode;
			prev = newnode;
		}
		
		printf("Do you want to add more nodes? (y/n): ");
		scanf(" %c", &choice);
		
	} while (choice == 'y');	
}

void display(struct node *head) {
	if (head == NULL || head->next == head) {
		printf("Polynomial is empty.\n");
		return;
	}
	
	printf("\nPolynomial = ");
	struct node *curr = head->next;
	while (curr != head) {
		printf("(%dx^%d)", curr->coef, curr->exp);
		if (curr->next != head) {
			printf (" + ");
		}
		curr = curr->next;
	}
	printf("\n");
}

int main(void) {
	struct node *head = (struct node*)malloc(sizeof(struct node));
	head->next = head;
	createll(head);
	display(head);
}


