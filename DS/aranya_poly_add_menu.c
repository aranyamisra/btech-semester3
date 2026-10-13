/*
 * Assignment: Polynomial Addition using a Circular Singly Linked List
 *             (terms entered one at a time)
 *
 * Complete every function marked TODO. Do NOT change main(), print_poly(),
 * the lines marked "provided", or the input/output format - your program is
 * graded automatically.
 *
 * INPUT: for the first polynomial, then for the second one, the program keeps
 * asking "Do you want to enter a term?":
 *   1                  yes -> the next line is "coef exp" (a new term)
 *   0                  no  -> this polynomial is finished, go to the next part
 * Terms can come in ANY order; exponents are >= 0. Answering 0 straight away
 * gives a polynomial with no terms.
 *
 * Example (P1 = 3x^2 + 5, P2 = 4x^2):
 *   1
 *   3 2
 *   1
 *   5 0
 *   0
 *   1
 *   4 2
 *   0
 *
 * OUTPUT (exactly three lines):
 *   P1 = <poly>
 *   P2 = <poly>
 *   SUM = <poly>
 *
 * <poly> lists terms in DESCENDING order of exponent as "%+dx^%d" separated
 * by one space, e.g. "+3x^2 -5x^0". A polynomial with no terms prints "0".
 *
 * Rules:
 *   - Terms with the same exponent (even inside one polynomial) are combined.
 *   - Terms whose coefficient becomes 0 must be removed.
 *   - The list is circular with a header node; head->next == head when empty.
 *
 * PROMPT(...) works like printf, but only prints when you compile with
 *     gcc -DINTERACTIVE poly_add_menu.c -o poly
 * so you see the questions while testing. The grader compiles WITHOUT
 * -DINTERACTIVE, so prompts are hidden there. Never print prompts with printf.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef INTERACTIVE
#define PROMPT(...) printf(__VA_ARGS__)
#else
#define PROMPT(...)
#endif

typedef struct node {
    int coef;
    int exp;
    struct node *next;
} pnode;

/* Create an empty circular list (header node only) and return the header. */
pnode *new_poly(void)
{
    /* TODO */
    struct node *head = (struct node*)malloc(sizeof(struct node));
    head->next = head;
    head->exp = -1;
    return head;
}

/* Insert a term keeping the list in descending exponent order.
 * Combine with an existing term of the same exponent; remove it if the
 * resulting coefficient is 0. Ignore terms whose coefficient is 0. */
void insert_term(pnode *head, int coef, int exp)
{
    /* TODO */
	if (coef != 0) {
	    	struct node *curr = head->next;
	    	struct node *prev = head;
	    	bool found = false;

	    	while (curr != head) {
			if (curr->exp == exp) {
			    found = true;
			    int temp = 0;
			    temp = curr->coef + coef;
			    if (temp != 0) {
			    	curr->coef = temp;
			    }
			    else {
			    	prev->next = curr->next;
			    	curr->next = NULL;
			    	free(curr);
			    }
			    break;
			}
			prev = curr;
			curr = curr->next;
	    	}
	    
	    	if (!found) {
			struct node *prev = head;
			while (prev->next != head && prev->next->exp > exp) {
			    prev = prev->next;
			}
			
			struct node* newnode = (struct node*)malloc(sizeof(struct node));
			newnode->coef = coef;
			newnode->exp = exp;
			
			newnode->next = prev->next;
			prev->next = newnode;
	    	}
	}
}

/* Read one polynomial: keep asking for terms until the answer is not 1. */
pnode *read_poly(void)
{
    pnode *head = NULL;
    int ch, c, e;

    /* TODO: create the empty polynomial (header node) */
    head = new_poly();

    while (1) {
        PROMPT("Do you want to enter a term? (1 = yes, 0 = no): ");   // provided
        if (scanf("%d", &ch) != 1 || ch != 1)                        // provided
            break;                                                   // provided
        PROMPT("Enter coefficient and exponent: ");                   // provided
        if (scanf("%d %d", &c, &e) != 2)                             // provided
            break;                                                   // provided

        /* TODO: add the term c x^e to the polynomial */
        insert_term(head, c, e);
    }
    return head;
}

/* Return a NEW polynomial equal to h1 + h2. Do not modify h1 or h2. */
pnode *poly_add(pnode *h1, pnode *h2)
{
    /* TODO */
    struct node *t1 = h1->next;
    struct node *t2 = h2->next;
    
    struct node *h3 = new_poly();
    struct node *t3 = h3;

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
    return h3;
}

/* Release every node including the header. */
void free_poly(pnode *head)
{
    /* TODO */
    struct node *curr = head->next;
    while (curr != head) {
    	struct node *temp = curr;
    	curr = curr->next;
    	free(temp);
    }
    head->next = NULL;
    free(head);
}

/* ---------------- provided - do not modify ---------------- */
void print_poly(pnode *head)
{
    pnode *p = head->next;

    if (p == head) {
        printf("0\n");
        return;
    }
    while (p != head) {
        printf("%+dx^%d", p->coef, p->exp);
        p = p->next;
        if (p != head)
            printf(" ");
    }
    printf("\n");
}

int main(void)
{
    PROMPT("Enter the first polynomial\n");
    pnode *p1 = read_poly();
    PROMPT("Enter the second polynomial\n");
    pnode *p2 = read_poly();
    pnode *sum = poly_add(p1, p2);

    printf("P1 = ");  print_poly(p1);
    printf("P2 = ");  print_poly(p2);
    printf("SUM = "); print_poly(sum);

    free_poly(p1);
    free_poly(p2);
    free_poly(sum);
    return 0;
}
