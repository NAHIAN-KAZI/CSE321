#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int main(int argc, char *argv[]) {
    int num_elements = argc - 1;
    int arr[num_elements];

    for (int i = 0; i < num_elements; i++)
        arr[i] = atoi(argv[i + 1]);

    qsort(arr, num_elements, sizeof(int), compare_ints);

    for (int i = 0; i < num_elements; i++)
        printf("%d ", arr[i]);

    printf("\n");
    return 0;
}