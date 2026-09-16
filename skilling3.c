/*
 * Skilling Session 3: Process Lifecycle, waitpid() Status Checking & perror()
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    printf("=========================================================\n");
    printf("  OSSP Skilling Session 3: waitpid() & Status Checking   \n");
    printf("=========================================================\n");

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");
        return 1;
    } else if (pid == 0) {
        printf("[Child PID: %d] Simulating work for 2 seconds...\n", getpid());
        sleep(2);
        printf("[Child] Exiting with status code 42.\n");
        exit(42);
    } else {
        int status;
        printf("[Parent] Waiting for Child PID: %d via waitpid()...\n", pid);
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("[Parent] Child exited normally with code: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("[Parent] Child terminated by signal: %d\n", WTERMSIG(status));
        }
    }
    return 0;
}
