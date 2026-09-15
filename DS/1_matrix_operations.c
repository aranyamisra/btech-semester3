#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INT_MIN -100
#define INT_MAX 100

void accept(int a[10][10], int r, int c) {
	printf("Enter the elements of the matrix: \n");
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			scanf("%d", &a[i][j]);
		}
	}
}

void display(int a[10][10], int r, int c) {
	printf("Elements of the matrix: \n");
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
}

void add(int a[10][10], int b[10][10], int r1, int c1) {
	int result[10][10];
	
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			result[i][j] = a[i][j] + b[i][j];
		}
	}
	printf("After addition: \n");
	display(result, r1, c1);
}

void subtract(int a[10][10], int b[10][10], int r1, int c1) {
	int result[10][10];
	
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			result[i][j] = a[i][j] - b[i][j];
		}
	}
	printf("After subtraction: \n");
	display(result, r1, c1);
}
	
void multiply(int a[10][10], int b[10][10], int r1, int c1, int c2) {
    int result[10][10];

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;

            for (int k = 0; k < c1; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    printf("After multiplication:\n");
    display(result, r1, c2);
}

void transpose(int a[10][10], int r, int c) {
	int result[10][10];

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			result[j][i] = a[i][j];
		}
	}

	printf("After transpose:\n");
	display(result, c, r);
}

void saddlepoint(int a[10][10], int r, int c) {
	int rowarr[r], colarr[c];
	
	for (int i = 0; i < r; i++) {
		int max = INT_MIN;
		for (int j = 0; j < c; j++) {
			if (a[i][j] > max) {
				max = a[i][j];
			}
		}
		rowarr[i] = max;
	}
	
	for (int j = 0; j < c; j++) {
		int min = INT_MAX;
		for (int i = 0; i < r; i++) {
			if (a[i][j] < min) {
				min = a[i][j];
			}
		}
		colarr[j] = min;
	}
	
	int minrow = INT_MAX, maxcol = INT_MIN;
	for (int i = 0; i < r; i++) {
		if (rowarr[i] < minrow)
			minrow = rowarr[i];
	}
	
	for (int j = 0; j < c; j++) {
		if (colarr[j] > maxcol)
			maxcol = colarr[j];
	}
	
	if (minrow == maxcol) {
		printf("Saddle point of matrix: %d\n", minrow);
	}
	else
		printf("No saddle point present.\n");
				
}


int main(void) {

	int m1, n1;
	printf("Enter number of rows and columns for matrix 1: ");
	scanf("%d%d", &m1, &n1);
	
	int m2, n2;
	printf("Enter number of rows and columns for matrix 2: ");
	scanf("%d%d", &m2, &n2);
	
	int a[10][10], b[10][10];
	
	accept(a, m1, n1);
	accept(b, m2, n2);
	
	display(a, m1, n1);
	display(b, m2, n2);
	
	printf("\nChoices: ");
	printf("\n1. Addition ");
	printf("\n2. Subratction ");
	printf("\n3. Multiplication ");
	printf("\n4. Transpose ");
	printf("\n5. Saddle point");
	printf("\n6. Exit \n");

	while(1) {
		int choice;
		printf("\nEnter choice: ");
		scanf("%d", &choice);
		
		switch(choice) {
			case 1:
				if (m1 != m2 || n1 != n2) {
					printf("Dimensions of the matrices are not equal.\n");
					break;
				}
				add(a, b, m1, n1);
				break;
			case 2:
				if (m1 != m2 || n1 != n2) {
					printf("Dimensions of the matrices are not equal.\n");
					break;
				}
				subtract(a, b, m1, n1);
				break;
			case 3:
				if (n1 != m2) {
					printf("Incorrect dimensions for multiplication.\n");
					break;
				}
				multiply(a, b, m1, n1, n2);
				break;
			case 4:
				transpose(a, m1, n1);
				transpose(b, m2, n2);
				break;
			case 5:
				saddlepoint(a, m1, n1);
				break;
			case 6:
				printf("Program ended.\n");
				return 0;
			default:
				printf("Enter valid choice.\n");
				break;
		}
	}
}

	
