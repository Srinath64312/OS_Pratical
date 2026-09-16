/*
 * Practical Session 5: Producer-Consumer Communication Using Anonymous Pipe
 * Demonstrates inter-process communication between parent (producer) and child (consumer).
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

int main() {
    int pipefd[2];
    char buffer[BUFFER_SIZE];
    const char *message = "OSSP IPC: Producer sends data to Consumer through Anonymous Pipe.";

    printf("=========================================================\n");
    printf(" Practical Session 5: Producer-Consumer via Anonymous Pipe\n");
    printf("=========================================================\n");

    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child Process: Consumer
        close(pipefd[1]); // Close write end
        printf("[Consumer Child PID: %d] Reading from pipe...\n", getpid());
        ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("[Consumer Child] Received Message: \"%s\" (%zd bytes)\n", buffer, bytes_read);
        }
        close(pipefd[0]);
        exit(0);
    } else {
        // Parent Process: Producer
        close(pipefd[0]); // Close read end
        printf("[Producer Parent PID: %d] Writing message to pipe...\n", getpid());
        write(pipefd[1], message, strlen(message));
        close(pipefd[1]); // Close write end to signal EOF
        wait(NULL);
        printf("[Producer Parent] Child process consumed message and exited.\n");
    }

    return 0;
}
