/*
 * Practical Session 6 (Part 1 - Server): Client-Server Communication using Named Pipes (FIFOs)
 * Server creates a well-known FIFO (/tmp/server_fifo), listens for client requests,
 * and sends processed responses back to each client's dedicated FIFO.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

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

int main() {
    int server_fd;
    Request request;
    char client_fifo[100];

    printf("=========================================================\n");
    printf(" Practical Session 6: FIFO Server (Named Pipes IPC)\n");
    printf("=========================================================\n");

    /* Create server FIFO */
    if (mkfifo(SERVER_FIFO, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo server failed");
        exit(EXIT_FAILURE);
    }

    printf("[Server PID: %d] Server started.\n", getpid());
    printf("[Server] Listening on %s ...\n", SERVER_FIFO);
    printf("[Server] Waiting for client requests (Press Ctrl+C to stop)...\n");

    /*
     * Open server FIFO for reading and writing (O_RDWR).
     * O_RDWR prevents read() from returning EOF when all clients have closed their descriptors.
     */
    server_fd = open(SERVER_FIFO, O_RDWR);
    if (server_fd == -1) {
        perror("open server FIFO failed");
        unlink(SERVER_FIFO);
        exit(EXIT_FAILURE);
    }

    while (1) {
        ssize_t n = read(server_fd, &request, sizeof(Request));
        if (n <= 0) {
            continue;
        }

        printf("\n[Server] Received message from Client [PID %d]: \"%s\"\n",
               request.client_pid, request.message);

        /* Construct client's dedicated response FIFO name */
        snprintf(client_fifo, sizeof(client_fifo), "/tmp/client_%d_fifo", request.client_pid);

        int client_fd = open(client_fifo, O_WRONLY);
        if (client_fd == -1) {
            perror("[Server] open client FIFO failed");
            continue;
        }

        Response response;
        snprintf(response.response, sizeof(response.response),
                 "Server processed: %s", request.message);

        write(client_fd, &response, sizeof(response));
        close(client_fd);

        printf("[Server] Sent response to Client [PID %d]: \"%s\"\n",
               request.client_pid, response.response);
    }

    close(server_fd);
    unlink(SERVER_FIFO);
    return 0;
}
