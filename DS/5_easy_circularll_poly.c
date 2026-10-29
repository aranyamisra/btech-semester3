#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Polynomial term
struct node {
	int coef;
	int exp;
	struct node *next;
};

void createll(struct node *head) {
    char ch;
    do {
        struct node *newnode = malloc(sizeof(struct node));
        printf("\nEnter coefficient and exponent: ");
        scanf("%d%d", &newnode->coef, &newnode->exp);

        struct node *curr = head;
        while (curr->next != head && curr->next->exp > newnode->exp)
            curr = curr->next;

        newnode->next = curr->next;
        curr->next = newnode;

        printf("Add more? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y');
}

void display(struct node *head) {
    struct node *curr = head->next;

    while (curr != head) {
        printf("%dx^%d", curr->coef, curr->exp);
        if (curr->next != head)
            printf(" + ");
        curr = curr->next;
    }
    printf("\n");
}

void addpoly(struct node *head1, struct node *head2, struct node *head3)
{
    struct node *t1 = head1->next;
    struct node *t2 = head2->next;
    struct node *t3 = head3;

    while(t1->exp != -1 || t2->exp != -1) {
        if (t1->exp == t2->exp) {
            int temp = t1->coef + t2->coef;
            if (temp != 0) {
				struct node *tempnode = (struct node*)malloc(sizeof(struct node));
				tempnode->coef = temp;
				tempnode->exp = t1->exp;
				tempnode->next = t3->next;
				t3->next = tempnode;
				t3 = tempnode;
            }
            t1 = t1->next;
            t2 = t2->next;
        }
        else if (t1->exp > t2->exp) {
            struct node *tempnode = (struct node*)malloc(sizeof(struct node));
            tempnode->coef = t1->coef;
            tempnode->exp = t1->exp;
            tempnode->next = t3->next;
            t3->next = tempnode;
            t3 = tempnode;
            t1 = t1->next;
        }
        else {
            struct node *tempnode = (struct node*)malloc(sizeof(struct node));
            tempnode->coef = t2->coef;
            tempnode->exp = t2->exp;
            tempnode->next = t3->next;
            t3->next = tempnode;
            t3 = tempnode;
            t2 = t2->next;
        }
    }
}

int evaluatepoly(struct node *head) {
	int result = 0;
	
	int x;
	printf("\nEnter the value of x: ");
	scanf("%d", &x);
	
	struct node *curr = head->next;
	while(curr != head) {
		result += (curr->coef * pow(x, curr->exp));
		curr = curr->next;
	}
	
	return result;
}

int main(void) {
	printf("Polynomials using circular linked list:\n");

	printf("Choices: \n");
	printf("1. Addition of two polynomials.\n");
	printf("2. Evaluation of a polynomial\n");
	printf("3. Exit\n");
	
	while(1) {
		int choice;
		printf("\nEnter choice: ");
		scanf("%d", &choice);
		
		switch(choice) {
			case 1: {
				printf("\nFor polynomial 1:");
				struct node *head1 = (struct node*)malloc(sizeof(struct node));
				head1->next = head1;
				head1->exp = -1;
				createll(head1);
				
				printf("\nFor polynomial 2:");
				struct node *head2 = (struct node*)malloc(sizeof(struct node));
				head2->exp = -1;
				head2->next = head2;
				createll(head2);

				printf("\nPolynomial 1 = ");
				display(head1);
				printf("Polynomial 2 = ");
				display(head2);

				struct node *head3 = (struct node*)malloc(sizeof(struct node));
				head3->exp = -1;
				head3->next = head3;

				addpoly(head1, head2, head3);

				printf("\nResultant polynomial = ");
				display(head3);
				
				break;
			}
			
			case 2: {
				printf("\nEnter polynomial:");
				struct node *head = (struct node*)malloc(sizeof(struct node));
				head->next = head;
				createll(head);
				
				printf("\nPolynomial = ");
				display(head);
				
				int ans = evaluatepoly(head);
				printf("\nPolynomial evaluation result = %d\n", ans);
				break;
			}
			
			case 3: 
				printf("Program ended.\n");
				return 0;
			default:
				printf("Invalid choice.\n");
		}
	}
}