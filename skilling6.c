/*
 * Skilling Session 6: Complete Integrated Restricted Shell with Logging
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

static void log_event(const char *cmd, const char *status) {
    FILE *fp = fopen("access.log", "a");
    if (!fp) return;
    time_t now = time(NULL);
    char *t = ctime(&now);
    if (t) t[strlen(t)-1] = '\0';
    fprintf(fp, "[%s] Command: \"%s\" - %s\n", t ? t : "N/A", cmd, status);
    fclose(fp);
}

int main() {
    char input[512];
    printf("=========================================================\n");
    printf("   OSSP Skilling Session 6: Secure Shell & Audit Trail  \n");
    printf("=========================================================\n");

    log_event("session", "SESSION STARTED");
    printf("Type commands (e.g. ls, pwd, date). Type 'exit' to quit.\n");

    while (1) {
        printf("skilling6> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\r\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            log_event("exit", "SESSION ENDED");
            break;
        }

        if (strlen(input) == 0) continue;

        if (strpbrk(input, ";|&><`$\\")) {
            printf("[-] Blocked: Dangerous metacharacters detected.\n");
            log_event(input, "BLOCKED - UNSAFE INPUT");
            continue;
        }

        pid_t pid = fork();
        if (pid == 0) {
            char *args[] = {input, NULL};
            execvp(args[0], args);
            perror("Execution failed");
            exit(1);
        } else {
            int status;
            waitpid(pid, &status, 0);
            log_event(input, WIFEXITED(status) && WEXITSTATUS(status) == 0 ? "EXECUTED" : "EXECUTED - NONZERO EXIT");
        }
    }
    printf("Audit log recorded in access.log\n");
    return 0;
}
