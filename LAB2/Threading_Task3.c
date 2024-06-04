#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM_NAMES 3
#define MAX_NAME_LENGTH 100

struct NameData {
    char name[MAX_NAME_LENGTH];
    int asciiSum;
};

void* get_user_input(void* ptr) {
    struct NameData* input_data = (struct NameData*)ptr;
    printf("Enter name: ");
    scanf("%[^\n]%*c", input_data->name);
    input_data->asciiSum = 0;
    for (int i = 0; input_data->name[i] != '\0'; i++)
        input_data->asciiSum += input_data->name[i];
    return NULL;
}

int main() {
    struct NameData names[NUM_NAMES];
    pthread_t threads[NUM_NAMES];

    for (int i = 0; i < NUM_NAMES; i++) {
        if (pthread_create(&threads[i], NULL, get_user_input, (void*)&names[i]) != 0) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    for (int i = 0; i < NUM_NAMES; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Error joining thread\n");
            return 1;
        }
    }

    int sum = names[0].asciiSum;
    int equalSums = 1;

    for (int i = 1; i < NUM_NAMES; i++) {
        if (names[i].asciiSum != sum) {
            equalSums = 0;
            break;
        }
    }

    if (equalSums)
        printf("Youreka\n");
    else
        printf("Hasta la vista\n");

    return 0;
}