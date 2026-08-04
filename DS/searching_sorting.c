#include <stdio.h>
#include <string.h>

struct student {
	int rno;
	char name[20];
	float marks;
};

void selection_sort_rno(struct student s[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;

        for (int j = i + 1; j < n; j++) {
            if (s[j].rno < s[min].rno)
                min = j;
        }

        if (min != i) {
            struct student temp = s[i];
            s[i] = s[min];
            s[min] = temp;
        }
    }
}

void accept(struct student s[], int n) {
	printf("Enter student details (roll no., name and marks): \n");
	for (int i = 0; i < n; i++) {
		printf("Student %d: ", i + 1);
		scanf("%d%s%f", &s[i].rno, s[i].name, &s[i].marks);
	}
}

void displayall(struct student s[], int n) {
    printf("Student Database Details\n");
    printf("%-10s %-20s %-10s\n", "Roll No.", "Name", "Marks");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-20s %-10.2f\n", s[i].rno, s[i].name, s[i].marks);
    }
}

void displayentry(struct student s[], int i) {
	printf("Roll No.: %d\n", s[i].rno);
	printf("Name: %s\n", s[i].name);
	printf("Marks: %.2f\n", s[i].marks);
}

int acceptkey() {
	int key;
	printf("Enter roll no. to search: ");
	scanf("%d", &key);
	return key;
}

void linear_search(struct student s[], int n, int key) {	
	for (int i = 0; i < n; i++) {
		if (s[i].rno == key) {
			printf("Entry found:\n");
			displayentry(s, i);
			return;
		}
	}
	printf("Entry not found.\n");
}

void normal_binary_search(struct student s[], int low, int high, int key) {	
	selection_sort_rno(s, high + 1);
	while (low <= high) {
		int mid = (low + high) / 2;
		
		if (s[mid].rno == key) {
			printf("Entry found:\n");
			displayentry(s, mid);
			return;
		}
		else if (s[mid].rno < key) 
			low = mid + 1;
		else
			high = mid - 1;
	}
	printf("Entry not found.\n");
}

void recursive_binary_search(struct student s[], int low, int high, int key) {
	if (low <= high) {
		int mid = (low + high) / 2;
		
		if (s[mid].rno == key) {
			printf("Entry found:\n");
			displayentry(s, mid);
			return;
		}
		else if (s[mid].rno < key) 
			return recursive_binary_search(s, mid + 1, high, key);
		else
			return recursive_binary_search(s, low, mid - 1, key);
	}
	printf("Entry not found.\n");
}

void selection_sort(struct student s[], int n) {
	
	for (int i = 0; i < n - 1; i++) {
		int minpos = i;
		for (int j = i + 1; j < n; j++) {
			if (s[j].marks < s[minpos].marks) {
				minpos = j;
			}
		}
		if (minpos != i) {
			struct student temp = s[i];
			s[i] = s[minpos];
			s[minpos] = temp;
		}

		printf("\nAfter pass %d:\n", i + 1);
		displayall(s, n);
	}
}

void insertion_sort(struct student s[], int n) {
	for (int i = 1; i < n; i++) {
		struct student key = s[i];
		int j = i - 1;
		
		while (j >= 0 && s[j].marks > key.marks) {
			s[j + 1] = s[j];
			j--;
		}
		s[j + 1] = key;

		printf("\nAfter pass %d:\n", i);
		displayall(s, n);
	}
}

void insertion_sort_name(struct student s[], int n) {
    for (int i = 1; i < n; i++) {
        struct student key = s[i];
        int j = i - 1;

        while (j >= 0 && strcmp(s[j].name, key.name) > 0) {
            s[j + 1] = s[j];
            j--;
        }

        s[j + 1] = key;
    }
}

void shell_sort(struct student s[], int n) {
    int swapped;
    int pass = 1;

    for (int gap = n / 2; gap > 0; gap /= 2) {
        do {
            swapped = 0;

            for (int i = 0; i < n - gap; i++) {
                if (s[i].marks > s[i + gap].marks) {
                    struct student temp = s[i];
                    s[i] = s[i + gap];
                    s[i + gap] = temp;
                    swapped = 1;
                }
            }

            printf("\nAfter Pass %d (Gap = %d):\n", pass++, gap);
            displayall(s, n);

        } while (swapped == 1);
    }
}

int main(void) {
	printf("Choices:\n");
	printf("1. Linear Search\n");
	printf("2. Normal Binary Search\n");
	printf("3. Recursive Binary Search\n");
	printf("4. Selection Sort (based on marks)\n");
	printf("5. Insertion Sort (based on marks)\n");
	printf("6. Shell sort (based on marks)\n");
	printf("7. Insertion Sort (based on name)\n");
	printf("8. Exit\n");

	int n;
	printf("\nEnter the number of students: ");
	scanf("%d", &n);
	
	struct student s[n];
	
	while (1) {
		int choice;
		printf("\nEnter choice: ");
		scanf("%d", &choice);
		
		switch (choice) {
			case 1: {
				accept(s, n);
				displayall(s, n);
				int key = acceptkey();
				linear_search(s, n, key);
				break;
			}
			case 2: {
				accept(s, n);
				displayall(s, n);
				int key = acceptkey();
				normal_binary_search(s, 0, n - 1, key);
				break;
			}
			case 3: {
				accept(s, n);
				displayall(s, n);
				int key = acceptkey();
				selection_sort_rno(s, n); 
				recursive_binary_search(s, 0, n - 1, key);
				break;
			}
			case 4: {
				accept(s, n);
				selection_sort(s, n);
				break;
			}
			case 5: {
				accept(s, n);
				insertion_sort(s, n);
				break;
			}
			case 6: {
				accept(s, n);
				shell_sort(s, n);
				break;
			}
			case 7: {
				accept(s, n);
				insertion_sort_name(s, n);
				printf("Students sorted based on name:\n");
				displayall(s, n);
				break;
			}
			case 8:
				printf("Program ended.\n");
				return 0;
			default:
				printf("Invalid choice.\n");
				break;
		}
	}
	return 0;
}

