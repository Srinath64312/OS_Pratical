/*
 * Skilling Session 2: User Authentication Gate & Command Whitelisting
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ATTEMPTS 3
static const char *ALLOWED[] = {"ls", "pwd", "date", "whoami", "echo", "cat", "clear", NULL};

int authenticate() {
    char user[50], pass[50];
    int attempts = 0;
    while (attempts < MAX_ATTEMPTS) {
        printf("Username: ");
        if (scanf("%49s", user) != 1) return 0;
        printf("Password: ");
        if (scanf("%49s", pass) != 1) return 0;

        if (strcmp(user, "admin") == 0 && strcmp(pass, "admin123") == 0) {
            printf("\n[+] Authentication Successful!\n\n");
            int c; while ((c = getchar()) != '\n' && c != EOF);
            return 1;
        }
        attempts++;
        printf("[-] Invalid credentials. Attempts remaining: %d\n\n", MAX_ATTEMPTS - attempts);
    }
    return 0;
}

int is_whitelisted(const char *cmd) {
    for (int i = 0; ALLOWED[i] != NULL; i++) {
        if (strcmp(cmd, ALLOWED[i]) == 0) return 1;
    }
    return 0;
}

int main() {
    char input[1024];
    char *args[20];

    printf("=========================================================\n");
    printf("   OSSP Skilling Session 2: Auth Gate & Whitelisting    \n");
    printf("=========================================================\n");

    if (!authenticate()) {
        printf("Access Denied.\n");
        return 1;
    }

    while (1) {
        printf("skilling2> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\r\n")] = '\0';
        if (strcmp(input, "exit") == 0) break;
        if (strlen(input) == 0) continue;

        int argc = 0;
        char *token = strtok(input, " ");
        while (token && argc < 19) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;

        if (!is_whitelisted(args[0])) {
            printf("[-] Command blocked: %s is not whitelisted.\n", args[0]);
            continue;
        }

        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            perror("Execution failed");
            exit(1);
        } else {
            wait(NULL);
        }
    }
    return 0;
}
