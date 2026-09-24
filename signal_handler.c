/*
 * Practical Session 6 (Part 2): Asynchronous Event Handling via POSIX Signals
 * Demonstrates capturing SIGINT, SIGTERM, and SIGUSR1 using sigaction()
 * with volatile sig_atomic_t flags for async-signal safety.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

volatile sig_atomic_t sigint_received = 0;
volatile sig_atomic_t sigterm_received = 0;
volatile sig_atomic_t sigusr1_received = 0;

/*
 * Signal handler: executes asynchronously when signal arrives.
 * Keeps handler reentrant & safe by only updating atomic flags.
 */
void signal_handler(int signo) {
    if (signo == SIGINT) {
        sigint_received = 1;
    } else if (signo == SIGTERM) {
        sigterm_received = 1;
    } else if (signo == SIGUSR1) {
        sigusr1_received = 1;
    }
}

int main() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);

    /* Register signal handlers */
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction SIGINT failed");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("sigaction SIGTERM failed");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction SIGUSR1 failed");
        exit(EXIT_FAILURE);
    }

    printf("=========================================================\n");
    printf(" Practical Session 6: POSIX Signal Handling (sigaction) \n");
    printf("=========================================================\n");
    printf("Process PID: %d\n", getpid());
    printf("\nSend signals to this process from another terminal using:\n");
    printf("  kill -SIGINT %d   (or press Ctrl+C in this terminal)\n", getpid());
    printf("  kill -SIGUSR1 %d\n", getpid());
    printf("  kill -SIGTERM %d  (terminates the loop cleanly)\n\n", getpid());

    while (1) {
        pause(); // Wait for signal delivery

        if (sigint_received) {
            printf("[Signal Received] SIGINT intercepted!\n");
            printf(" -> Interrupt signal handled safely without crash.\n");
            sigint_received = 0;
        }

        if (sigusr1_received) {
            printf("[Signal Received] SIGUSR1 intercepted!\n");
            printf(" -> Custom user-defined event handled.\n");
            sigusr1_received = 0;
        }

        if (sigterm_received) {
            printf("[Signal Received] SIGTERM intercepted!\n");
            printf(" -> Termination signal received. Preparing graceful shutdown...\n");
            break;
        }
    }

    printf("Program terminated gracefully.\n");
    return 0;
}
