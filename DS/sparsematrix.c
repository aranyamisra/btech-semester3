#include <stdio.h>
#include <stdbool.h>
#include <time.h>

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

void displaycompact(int a[][3], int r, int c) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
}

void compact(int a[10][10],  int m, int n, int comp[][3]) {
	comp[0][0] = m;
	comp[0][1] = n;
	
	int k = 1;
	
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] != 0) {
				comp[k][0] = i;
				comp[k][1] = j;
				comp[k][2] = a[i][j];
				k++;
			}
		}
	}
	
	comp[0][2] = k - 1;
}

void simpletranspose(int compact[][3], int simple[][3]) {
	int m = compact[0][0];
	int n = compact[0][1];
	int t = compact[0][2];
	
	simple[0][0] = n;
	simple[0][1] = m;
	simple[0][2] = t;
	
	if (t <= 0)
		return;
		
	int q = 1;
	
	for (int col = 0; col < n; col++) {
		for (int p = 1; p <= t; p++) {
			if (compact[p][1] == col) {
				simple[q][0] = compact[p][1];
				simple[q][1] = compact[p][0];
				simple[q][2] = compact[p][2];
				q++;
			}
		}
	}
}

void fasttranspose(int compact[][3], int fast[][3]) {
    int m = compact[0][0];
    int n = compact[0][1];
    int t = compact[0][2];

    fast[0][0] = n;
    fast[0][1] = m;
    fast[0][2] = t;

    if (t <= 0)
        return;

    int S[n], T[n];

    for (int i = 0; i < n; i++)
        S[i] = 0;

    // non-zero elements in each column
    for (int i = 1; i <= t; i++)
        S[compact[i][1]]++;

    // starting positions
    T[0] = 1;
    for (int i = 1; i < n; i++)
        T[i] = T[i - 1] + S[i - 1];

    for (int i = 1; i <= t; i++) {
        int col = compact[i][1];
        int pos = T[col];

        fast[pos][0] = compact[i][1];
        fast[pos][1] = compact[i][0];
        fast[pos][2] = compact[i][2];

        T[col]++;
    }
}

void add(int a[][3], int b[][3], int sum[][3]) {

	int t1 = a[0][2], t2 = b[0][2];
	
	if (a[0][0] == b[0][0] && a[0][1] == b[0][1]) {
		if (t1 == 0 && t2 == 0)
			return;
		sum[0][0] = a[0][0];
		sum[0][1] = a[0][1];
	}
	
	int i = 1, j = 1, k = 1;
	
	while (i <= t1 && j <= t2) {
		if (a[i][0] == b[j][0]) {
			if (a[i][1] == b[j][1]) {
				int temp = a[i][2] + b[j][2];
				if (temp != 0) {
					sum[k][0] = a[i][0];
					sum[k][1] = a[i][1];
					sum[k][2] = temp;
					k++;
				}
				i++;
				j++;
			}
			else if (a[i][1] < b[j][1]) {
				sum[k][0] = a[i][0];
				sum[k][1] = a[i][1];
				sum[k][2] = a[i][2];
				k++;
				i++;
			}
			else {
				sum[k][0] = b[j][0];
				sum[k][1] = b[j][1];
				sum[k][2] = b[j][2];
				k++;
				j++;
			}
		}
		else if (a[i][0] < b[j][0]) {
			sum[k][0] = a[i][0];
			sum[k][1] = a[i][1];
			sum[k][2] = a[i][2];
			k++;
			i++;
		}
		else {
			sum[k][0] = b[j][0];
			sum[k][1] = b[j][1];
			sum[k][2] = b[j][2];
			k++;
			j++;
		}
	}
	
	while (i <= t1) {
		sum[k][0] = a[i][0];
		sum[k][1] = a[i][1];
		sum[k][2] = a[i][2];
		k++;
		i++;
	}
	
	while (j <= t2) {
		sum[k][0] = b[j][0];
		sum[k][1] = b[j][1];
		sum[k][2] = b[j][2];
		k++;
		j++;
	}
	
	sum[0][2] = k - 1;
} 


void subtract(int a[][3], int b[][3], int diff[][3]) {

	int t1 = a[0][2], t2 = b[0][2];
	
	if (a[0][0] == b[0][0] && a[0][1] == b[0][1]) {
		if (t1 == 0 && t2 == 0)
			return;
		diff[0][0] = a[0][0];
		diff[0][1] = a[0][1];
	}
	
	int i = 1, j = 1, k = 1;
	
	while (i <= t1 && j <= t2) {
		if (a[i][0] == b[j][0]) {
			if (a[i][1] == b[j][1]) {
				int temp = a[i][2] - b[j][2];
				if (temp != 0) {
					diff[k][0] = a[i][0];
					diff[k][1] = a[i][1];
					diff[k][2] = temp;
					k++;
				}
				i++;
				j++;
			}
			else if (a[i][1] < b[j][1]) {
				diff[k][0] = a[i][0];
				diff[k][1] = a[i][1];
				diff[k][2] = a[i][2];
				k++;
				i++;
			}
			else {
				diff[k][0] = b[j][0];
				diff[k][1] = b[j][1];
				diff[k][2] = b[j][2];
				k++;
				j++;
			}
		}
		else if (a[i][0] < b[j][0]) {
			diff[k][0] = a[i][0];
			diff[k][1] = a[i][1];
			diff[k][2] = a[i][2];
			k++;
			i++;
		}
		else {
			diff[k][0] = b[j][0];
			diff[k][1] = b[j][1];
			diff[k][2] = b[j][2];
			k++;
			j++;
		}
	}
	
	while (i <= t1) {
		diff[k][0] = a[i][0];
		diff[k][1] = a[i][1];
		diff[k][2] = a[i][2];
		k++;
		i++;
	}
	
	while (j <= t2) {
		diff[k][0] = b[j][0];
		diff[k][1] = b[j][1];
		diff[k][2] = b[j][2];
		k++;
		j++;
	}
	
	diff[0][2] = k - 1;
} 
	 
bool isSparse(int a[10][10], int m, int n) {
	int zeros = 0;
	
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] == 0)
				zeros++;
		}
	}
	
	int nonzeros = (m*n - zeros);
	
	if (zeros < nonzeros) 
		return false;
		
	return true;
}

int nonzeros_count (int a[10][10], int m, int n) {
	int zeros = 0;
	
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] == 0)
				zeros++;
		}
	}
	
	return (m*n - zeros);
}
	

int main(void) {
	int a[10][10], m, n;
	
	printf("Enter the number of rows and columns: ");
	scanf("%d%d", &m, &n);
	
	accept(a, m, n);
	display(a, m, n);
	
	if (!isSparse(a, m, n)) {
		printf("It is not a sparse matrix\n");
		return 0;
	}
	int nonzeros = nonzeros_count(a, m, n);
	
	int compactmatrix[nonzeros + 1][3];
	
	compact(a, m, n, compactmatrix);
	
	printf("Elements of the compact matrix: \n");
	displaycompact(compactmatrix, nonzeros+1, 3);
	
	printf("\nChoices:");
	printf("\n1. Simple Transpose");
	printf("\n2. Fast Transpose");
	printf("\n3. Add sparse matrices");
	printf("\n4. Subtract sparse matrices");
	printf("\n5. Exit\n");
	
	int simple[nonzeros + 1][3];
	int fast[nonzeros + 1][3];
	
	while(1) {
		int choice;
		printf("\nEnter choice: ");
		scanf("%d", &choice);
		
		switch(choice) {
			case 1: {
				clock_t start, end;
				double cpu_time_used;
				
				start = clock();
				simpletranspose(compactmatrix, simple);
				end = clock();
				
				printf("Elements of the simple transpose matrix: \n");
				displaycompact(simple, nonzeros + 1, 3);
				
				cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    				printf("CPU time used: %f seconds\n", cpu_time_used);
				break;
			}
			case 2: {
				clock_t start, end;
				double cpu_time_used;
				
				start = clock();
				fasttranspose(compactmatrix, fast);
				end = clock();
				
				printf("Elements of the fast transpose matrix: \n");
				displaycompact(fast, nonzeros + 1, 3);
				
				cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    				printf("CPU time used: %f seconds\n", cpu_time_used);
				break;
			}
			case 3: {
			    int m2, n2, b[10][10];

			    printf("Enter number of rows and columns for the matrix to be added: ");
			    scanf("%d%d", &m2, &n2);

			    accept(b, m2, n2);
			    display(b, m2, n2);

			    if (!isSparse(b, m2, n2)) {
				printf("It is not a sparse matrix\n");
				break;
			    }

			    int nonzerosB = nonzeros_count(b, m2, n2);

			    int compactmatrixB[nonzerosB + 1][3];

			    compact(b, m2, n2, compactmatrixB);

			    printf("Elements of the second compact matrix:\n");
			    displaycompact(compactmatrixB, nonzerosB + 1, 3);

			    int sum[nonzeros + nonzerosB + 1][3];

			    add(compactmatrix, compactmatrixB, sum);

			    printf("Sum of sparse matrices:\n");
			    displaycompact(sum, sum[0][2] + 1, 3);

			    break;
			}
			case 4: {
			    int m2, n2, b[10][10];

			    printf("Enter number of rows and columns for the matrix to be subtracted: ");
			    scanf("%d%d", &m2, &n2);

			    accept(b, m2, n2);
			    display(b, m2, n2);

			    if (!isSparse(b, m2, n2)) {
				printf("It is not a sparse matrix\n");
				break;
			    }

			    int nonzerosB = nonzeros_count(b, m2, n2);

			    int compactmatrixB[nonzerosB + 1][3];

			    compact(b, m2, n2, compactmatrixB);

			    printf("Elements of the second compact matrix:\n");
			    displaycompact(compactmatrixB, nonzerosB + 1, 3);

			    int diff[nonzeros + nonzerosB + 1][3];

			    subtract(compactmatrix, compactmatrixB, diff);

			    printf("Difference of sparse matrices:\n");
			    displaycompact(diff, diff[0][2] + 1, 3);

			    break;
			}
			case 5:
				printf("Program ended.\n");
				return 0;
			default:
				printf("Invalid choice. Please try again.\n");
				break;
		}
	}
}
