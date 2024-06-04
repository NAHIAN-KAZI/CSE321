#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void sort(int array[], int size);
void oddeven(int arr[], int num);

int main() {
    int elements[] = {104, 144, 24442, 11, 3, 77};
    int count = sizeof(elements) / sizeof(elements[0]);
    pid_t child_process;

    child_process = fork();

    if (child_process == 0) {
        printf("sorted array in descending order: \n");
        sort(elements, count);
    } else if (child_process > 0) {
        wait(NULL);
        printf("Odd-even: \n");
        oddeven(elements, count);
    }

    return 0;
}

void sort(int numbers[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (numbers[j] < numbers[j+1]) {
                temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

void oddeven(int arr[], int num) {
    for (int i = 0; i < num; i++) {
        if (arr[i] % 2 == 0)
            printf("%d - even\n", arr[i]);
        else
            printf("%d - odd\n", arr[i]);
    }
}