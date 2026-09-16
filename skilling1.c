/*
 * Skilling Session 1: Basic Shell REPL Architecture & Input Loop
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1024

int main() {
    char input[MAX_INPUT];

    printf("=========================================================\n");
    printf("     OSSP Skilling Session 1: Shell REPL Foundations     \n");
    printf("=========================================================\n");

    while (1) {
        printf("skilling1> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\r\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("Exiting Skilling 1 Shell.\n");
            break;
        }

        if (strlen(input) > 0) {
            printf("You entered: %s\n", input);
        }
    }
    return 0;
}
