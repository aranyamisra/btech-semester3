#include <stdio.h>
#include <math.h>

int main(void) {

    int m;
    printf("Enter no. of data bits: ");
    scanf("%d", &m);

    int data[m];
    printf("Enter data bits: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &data[i]);
    }

    int r = 0;
    while(pow(2, r) < m+r+1) {
        r++;
    }

    int total_len = m + r;
    int code[total_len + 1];

    int dataidx = 0;
    int parityidx = 0;

    for (int i = 1; i <= total_len; i++) {
        if(i == (int)pow(2, parityidx)) {
            code[i] = -1;
            parityidx++;
        }
        else {
            code[i] = data[dataidx];
            dataidx++;
        }
    }

    for (int i = 0; i < r; i++) {
        int pos = (int)pow(2, i); // r position
        int count = 0; // no. of ones
    
        for (int j = pos; j <= total_len; j += 2 * pos) {
            for (int k = j; k < j + pos && k <= total_len; k++) {
                if (k == pos)
                    continue;    
                if (code[k] == 1)
                    count++;
            }
        }
        code[pos] = count % 2; // if even, r = 0, else 1
    }

    printf("Code word: ");
    for (int i = total_len; i >= 1; i--) {
        printf("%d", code[i]);
    }
    printf("\n");

    // Error Detection
    int received[total_len + 1];
    printf("Enter received code word: ");
    for (int i = total_len; i >= 1; i--) {
        scanf("%d", &received[i]);
    }

    int s[r], ridx = r-1;
    int error = 0;
    
    for (int i = 0; i < r; i++) {
        int pos = (int)pow(2, i);
        int ones = 0;

        for (int j = pos; j <= total_len; j+= 2 * pos) {
            for (int k = j; k < j + pos && k <= total_len; k++) {
                if(received[k] == 1)
                    ones++;
            }
        }
        if (ones % 2 != 0) {
            s[ridx] = 1;
            error += pos;
        }
        else 
            s[ridx] = 0;

        ridx--;
    }

    printf("Syndrome: ");
    for (int i = 0; i < r; i++) 
        printf("%d", s[i]);
    printf("\n");

    if (error != 0) 
        printf("Error detected at position: %d\n", error);
    else
        printf("No error detected.\n");
}