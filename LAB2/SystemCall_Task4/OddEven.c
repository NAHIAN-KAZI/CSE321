#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isEven(int num) {
    return num % 2 == 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <number1> <number2> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        int num = atoi(argv[i]);
        printf("%d is %s\n", num, isEven(num) ? "even" : "odd");
    }

    return 0;
}