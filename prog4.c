/*
 * Practical Session 4: Process Synchronization using wait() and waitpid()
 * Creates multiple child processes and compares wait() and waitpid() synchronization.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pids[3];
    int status;

    printf("=========================================================\n");
    printf(" Practical Session 4: Synchronization with wait() & waitpid() \n");
    printf("=========================================================\n");

    for (int i = 0; i < 3; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pids[i] == 0) {
            printf("[Child %d] PID: %d, Sleep duration: %d sec\n", i + 1, getpid(), 3 - i);
            sleep(3 - i);
            printf("[Child %d] Finished task.\n", i + 1);
            exit(10 + i);
        }
    }

    printf("\n[Parent] Specifically waiting for Child 3 (PID: %d) via waitpid()...\n", pids[2]);
    waitpid(pids[2], &status, 0);
    if (WIFEXITED(status)) {
        printf("[Parent] Child 3 terminated with exit status: %d\n", WEXITSTATUS(status));
    }

    printf("\n[Parent] Collecting remaining children using wait()...\n");
    pid_t finished_pid;
    while ((finished_pid = wait(&status)) > 0) {
        if (WIFEXITED(status)) {
            printf("[Parent] Reaped Child PID: %d with exit code: %d\n", finished_pid, WEXITSTATUS(status));
        }
    }

    printf("\n[Parent] All child processes successfully synchronized.\n");
    return 0;
}
