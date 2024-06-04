#include <stdio.h>

int isPerfect(int num) {
    int sum = 0;
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    return (sum == num);
}


void printPerfectNumbers(int start, int end) {
    printf("Perfect numbers between %d and %d:\n", start, end);
    for (int i = start; i <= end; i++) {
        if (isPerfect(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int start, end;
    printf("Enter the start and end intervals: ");
    scanf("%d %d", &start, &end);
    printPerfectNumbers(start, end);
    return 0;
}