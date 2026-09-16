/*
 * Skilling Session 4: Shell Built-in Commands & Environment Variables
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    char input[1024];
    char cwd[1024];

    printf("=========================================================\n");
    printf(" OSSP Skilling Session 4: Built-in Commands (cd, pwd, env)\n");
    printf("=========================================================\n");

    while (1) {
        printf("skilling4> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\r\n")] = '\0';

        if (strcmp(input, "exit") == 0) break;
        if (strlen(input) == 0) continue;

        if (strcmp(input, "pwd") == 0) {
            if (getcwd(cwd, sizeof(cwd))) printf("%s\n", cwd);
        } else if (strncmp(input, "cd", 2) == 0) {
            char *dir = input + 2;
            while (*dir == ' ') dir++;
            if (*dir == '\0') dir = getenv("HOME");
            if (chdir(dir) != 0) perror("cd failed");
            else {
                getcwd(cwd, sizeof(cwd));
                printf("Changed directory to: %s\n", cwd);
            }
        } else if (strcmp(input, "env") == 0) {
            printf("USER=%s\nHOME=%s\nPATH=%s\n", getenv("USER"), getenv("HOME"), getenv("PATH"));
        } else {
            printf("Supported built-ins: cd <dir>, pwd, env, exit\n");
        }
    }
    return 0;
}
