/*
 * Assignment: Singly Linked List Operations (student records)
 *
 * Complete every function marked TODO. Do NOT change main() or the
 * input/output format - your program is graded automatically.
 *
 * The list uses a header node: head->next is the first record,
 * head->next == NULL means the list is empty.
 *
 * INPUT: one command per line (no prompts are printed)
 *   C n                 create a new list from the next n lines "regno name"
 *                       (any existing list is freed first)
 *   I pos regno name    insert at position pos (1 = front, len+1 = end)
 *   D pos               delete the record at position pos (1..len)
 *   P                   print the list
 *   L                   print the number of records
 *   R                   reverse the list (by changing pointers)
 *   S                   sort ascending by regno (by relinking nodes,
 *                       NOT by swapping data)
 *   M n                 read n more records (already sorted by regno) and
 *                       merge them into the current (sorted) list
 *   Q                   quit
 *
 * OUTPUT:
 *   P  ->  "101:Asha -> 102:Ravi -> 105:Meera"   or   "EMPTY"
 *   L  ->  the length, e.g. "3"
 *   I / D with an invalid position print "INVALID"
 *   All other commands print nothing.
 *
 * Names contain no spaces and are at most 19 characters.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 20

typedef struct node {
    int regno;
    char name[NAME_LEN];
    struct node *next;
} node;

/* Allocate and return an empty list (header node, next = NULL). */
node *new_list(void)
{
    /* TODO */
    struct node* head = (struct node*)malloc(sizeof(struct node));
    head->next = NULL;
    return head;
}

/* Number of records in the list (header not counted). */
int length(node *head)
{
    /* TODO */
    int len = 0;
    struct node *ptr = head->next;
    while (ptr != NULL) {
    	len++;
    	ptr = ptr->next;
    }
    return len;
}

/* Free every record node; keep the header and leave the list empty. */
void clear_list(node *head)
{
    /* TODO */
}

/* Add a record at the end of the list. */
void append(node *head, int regno, const char *name)
{
    /* TODO */
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->regno = regno;
    strcpy(newnode->name, name);
    newnode->next = NULL;
    
    struct node *ptr = head;
    while (ptr->next != NULL) {
    	ptr = ptr->next;
    }
    
    ptr->next = newnode;
}

/* Insert at 1-based position pos. Return 1 on success, 0 if pos is invalid. */
int insert_at(node *head, int pos, int regno, const char *name)
{
    /* TODO */
    int len = length(head);
    if (pos > len + 1) {
    	printf("INVALID\n");
    	return 0;
    }
    
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->regno = regno;
    strcpy(newnode->name, name);
    newnode->next = NULL;
    
    struct node *ptr = head;
    int i = 1;
    
    while (ptr->next != NULL && i < pos) {
    	i++;
    	ptr = ptr->next;
    }
    
    newnode->next = ptr->next;
    ptr->next = newnode;
    
    return 1;
}

/* Delete record at 1-based position pos. Return 1 on success, 0 if invalid. */
int delete_at(node *head, int pos)
{
    /* TODO */
    int len = length(head);
    if (pos > len + 1) {
    	printf("INVALID\n");
    	return 0;
    }
    
    struct node *prev = head;
    struct node *ptr = head;
    int i = 1;
    
    while (ptr->next != NULL && i < pos) {
    	i++;
    	prev = ptr;
    	ptr = ptr->next;
    }
    struct node *temp = ptr;
    prev->next = ptr->next;
    ptr->next = NULL;
    free(temp)
    return 0;
}

/* Print the list in the exact format described above. */
void display(node *head)
{
    /* TODO */
    struct node* ptr = head->next;
    
    if (ptr == NULL) {
    	printf("EMPTY\n");
    	return;
    }
    while (ptr != NULL) {
    	printf("%d:%s", ptr->regno, ptr->name);
    	if (ptr->next != NULL)
    		printf(" -> ");
    	ptr = ptr->next;
    }
    printf("\n");
}

/* Reverse the list in place by changing next pointers. */
void reverse(node *head)
{
    /* TODO */
}

/* Sort ascending by regno by relinking nodes. */
void sort_list(node *head)
{
    /* TODO */
}

/* Merge sorted list head2 into sorted list head1 (result in head1).
 * Reuse the existing nodes; leave head2 empty afterwards. */
void merge(node *head1, node *head2)
{
    /* TODO */
}

/* ---------------- provided - do not modify ---------------- */
void read_records(node *head, int n)
{
    int i, regno;
    char name[NAME_LEN];

    for (i = 0; i < n; i++) {
        if (scanf("%d %19s", &regno, name) != 2)
            return;
        append(head, regno, name);
    }
}

int main(void)
{
    node *list = new_list(), *other = new_list();
    char cmd[4];
    int n, pos, regno;
    char name[NAME_LEN];

    while (scanf("%3s", cmd) == 1) {
        switch (cmd[0]) {
        case 'C':
            scanf("%d", &n);
            clear_list(list);
            read_records(list, n);
            break;
        case 'I':
            scanf("%d %d %19s", &pos, &regno, name);
            if (!insert_at(list, pos, regno, name))
                printf("INVALID\n");
            break;
        case 'D':
            scanf("%d", &pos);
            if (!delete_at(list, pos))
                printf("INVALID\n");
            break;
        case 'P': display(list); break;
        case 'L': printf("%d\n", length(list)); break;
        case 'R': reverse(list); break;
        case 'S': sort_list(list); break;
        case 'M':
            scanf("%d", &n);
            clear_list(other);
            read_records(other, n);
            merge(list, other);
            break;
        case 'Q':
            clear_list(list); clear_list(other);
            free(list); free(other);
            return 0;
        default:
            printf("UNKNOWN\n");
        }
    }
    clear_list(list); clear_list(other);
    free(list); free(other);
    return 0;
}
