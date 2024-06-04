#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "a+");  

    if (file == NULL) {
        printf("Error: Failed to open/create the file '%s'.\n", filename);
        return 1;
    }

    char input[1024];
    printf("Enter strings (or '-1' to exit):\n");

    while (1) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; 

        if (strcmp(input, "-1") == 0) {
            break;
        }

        fprintf(file, "%s\n", input);
    }

    fclose(file);
    printf("Strings have been written to the file '%s'.\n", filename);
    return 0;
}