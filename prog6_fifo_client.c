/*
 * Practical Session 6 (Part 1 - Client): Client-Server Communication using Named Pipes (FIFOs)
 * Creates a unique FIFO (/tmp/client_<PID>_fifo), sends a message to the server FIFO,
 * and waits to read the processed response from its own FIFO.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define SERVER_FIFO "/tmp/server_fifo"
#define MAX_MSG 256
#define MAX_RESP 512

typedef struct {
    pid_t client_pid;
    char message[MAX_MSG];
} Request;

typedef struct {
    char response[MAX_RESP];
} Response;

int main(int argc, char *argv[]) {
    int server_fd, client_fd;
    char client_fifo[100];
    char message[MAX_MSG];
    Request request;
    Response response;

    pid_t pid = getpid();

    printf("=========================================================\n");
    printf(" Practical Session 6: FIFO Client (Named Pipes IPC)\n");
    printf("=========================================================\n");
    printf("[Client PID: %d]\n", pid);

    /* Create unique FIFO for this client */
    snprintf(client_fifo, sizeof(client_fifo), "/tmp/client_%d_fifo", pid);

    if (mkfifo(client_fifo, 0666) == -1) {
        perror("mkfifo client failed");
        exit(EXIT_FAILURE);
    }

    if (argc > 1) {
        // If provided via command line argument
        strncpy(message, argv[1], sizeof(message) - 1);
        message[sizeof(message) - 1] = '\0';
    } else {
        printf("Enter message to send to server: ");
        if (fgets(message, sizeof(message), stdin) == NULL) {
            unlink(client_fifo);
            exit(EXIT_SUCCESS);
        }
        /* Remove trailing newline */
        message[strcspn(message, "\r\n")] = '\0';
    }

    request.client_pid = pid;
    strncpy(request.message, message, sizeof(request.message) - 1);
    request.message[sizeof(request.message) - 1] = '\0';

    /* Open server FIFO for writing */
    server_fd = open(SERVER_FIFO, O_WRONLY);
    if (server_fd == -1) {
        perror("Unable to open server FIFO (is server running?)");
        unlink(client_fifo);
        exit(EXIT_FAILURE);
    }

    /* Send request to server */
    write(server_fd, &request, sizeof(request));
    close(server_fd);
    printf("[Client] Sent request: \"%s\"\n", request.message);

    /* Open client's dedicated FIFO for reading server's response */
    client_fd = open(client_fifo, O_RDONLY);
    if (client_fd == -1) {
        perror("Unable to open client FIFO for reading");
        unlink(client_fifo);
        exit(EXIT_FAILURE);
    }

    /* Read response */
    ssize_t bytes_read = read(client_fd, &response, sizeof(response));
    if (bytes_read > 0) {
        printf("[Client] Server Response: \"%s\"\n", response.response);
    }
    close(client_fd);

    /* Clean up client FIFO */
    unlink(client_fifo);
    return 0;
}
