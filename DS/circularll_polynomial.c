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
	char choice;
	
	do {
		int temp_coef, temp_exp;
		printf("\nEnter coefficient and exponent: ");
		scanf("%d%d", &temp_coef, &temp_exp);
		
        if (temp_coef == 0) {
			printf("Coefficient is 0. Term not added.\n");
		}
        else {
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
                struct node *prev = head;
                while (prev->next != head && prev->next->exp > temp_exp) {
                    prev = prev->next;
                }
                
                struct node* newnode = (struct node*)malloc(sizeof(struct node));
                newnode->coef = temp_coef;
                newnode->exp = temp_exp;
                
                newnode->next = prev->next;
                prev->next = newnode;
            }
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
	
	struct node *curr = head->next;
    bool first = true;
	while (curr != head) {
		if (curr->coef == 0) {
			curr = curr->next;
			continue;
		}

		// handling +/-
		if (!first) {
			if (curr->coef > 0) printf(" + ");
			else printf(" - ");
		} 
        else {
			if (curr->coef < 0) printf("-");
			first = false;
		}

		int abs_coef = abs(curr->coef);

		// handle coefficients
		if (abs_coef != 1 || curr->exp == 0) { // dont print coef only if coef is 1
			printf("%d", abs_coef);
		}

		// handle exponents
		if (curr->exp == 1) {
			printf("x");
		} 
        else if (curr->exp != 0) {
			printf("x^%d", curr->exp);
		}
        
		curr = curr->next;
	}
	printf("\n");
}

void addpoly(struct node *head1, struct node *head2, struct node *head3)
{
    struct node *t1 = head1->next;
    struct node *t2 = head2->next;
    struct node *t3 = head3;

    while(t1 != head1 && t2 != head2) {
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

    while (t1 != head1) {
        struct node *tempnode = (struct node*)malloc(sizeof(struct node));
        tempnode->coef = t1->coef;
        tempnode->exp = t1->exp;
        tempnode->next = t3->next;
        t3->next = tempnode;
        t3 = tempnode;
        t1 = t1->next;
    }

    while (t2 != head2) {
        struct node *tempnode = (struct node*)malloc(sizeof(struct node));
        tempnode->coef = t2->coef;
        tempnode->exp = t2->exp;
        tempnode->next = t3->next;
        t3->next = tempnode;
        t3 = tempnode;
        t2 = t2->next;
    }
}

int main(void) {
    printf("Polynomials addition using circular linked list:\n");

    printf("\nFor polynomial 1:");
	struct node *head1 = (struct node*)malloc(sizeof(struct node));
	head1->next = head1;
	createll(head1);

    printf("\nFor polynomial 2:");
    struct node *head2 = (struct node*)malloc(sizeof(struct node));
	head2->next = head2;
	createll(head2);

    printf("\nPolynomial 1 = ");
	display(head1);
    printf("Polynomial 2 = ");
	display(head2);

    struct node *head3 = (struct node*)malloc(sizeof(struct node));
	head3->next = head3;

    addpoly(head1, head2, head3);

    printf("\nResultant polynomial = ");
    display(head3);
}

