/*
 * Skilling Session 5: Signal Interception (SIGINT) and Zombie Reaping (SIGCHLD)
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

static void sigint_handler(int sig) {
    (void)sig;
    printf("\n[!] Caught SIGINT (Ctrl+C). Type 'exit' to quit.\nskilling5> ");
    fflush(stdout);
}

static void sigchld_handler(int sig) {
    (void)sig;
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("\n[Async Reaper] Cleaned up background child PID %d.\nskilling5> ", pid);
        fflush(stdout);
    }
}

int main() {
    char input[256];

    struct sigaction sa_int, sa_chld;
    sa_int.sa_handler = sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);

    sa_chld.sa_handler = sigchld_handler;
    sigemptyset(&sa_chld.sa_mask);
    sa_chld.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &sa_chld, NULL);

    printf("=========================================================\n");
    printf("   OSSP Skilling Session 5: Signals (SIGINT & SIGCHLD)  \n");
    printf("=========================================================\n");

    while (1) {
        printf("skilling5> ");
        fflush(stdout);
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\r\n")] = '\0';

        if (strcmp(input, "exit") == 0) break;
        if (strcmp(input, "fork_bg") == 0) {
            pid_t pid = fork();
            if (pid == 0) {
                sleep(2);
                exit(0);
            } else {
                printf("[Parent] Forked background child PID: %d\n", pid);
            }
        }
    }
    return 0;
}
