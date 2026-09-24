CC = gcc
CFLAGS = -Wall -Wextra -g

PRACTICALS = prog1 prog2 prog3 prog4 prog5 prog6_fifo_server prog6_fifo_client signal_handler page_replacement
SKILLINGS = skilling1 skilling2 skilling3 skilling4 skilling5 skilling6

all: $(PRACTICALS) $(SKILLINGS)

prog1: prog1.c
	$(CC) $(CFLAGS) prog1.c -o prog1

prog2: prog2.c
	$(CC) $(CFLAGS) prog2.c -o prog2

prog3: prog3.c
	$(CC) $(CFLAGS) prog3.c -o prog3

prog4: prog4.c
	$(CC) $(CFLAGS) prog4.c -o prog4

prog5: prog5.c
	$(CC) $(CFLAGS) prog5.c -o prog5

prog6_fifo_server: prog6_fifo_server.c
	$(CC) $(CFLAGS) prog6_fifo_server.c -o prog6_fifo_server

prog6_fifo_client: prog6_fifo_client.c
	$(CC) $(CFLAGS) prog6_fifo_client.c -o prog6_fifo_client

signal_handler: signal_handler.c
	$(CC) $(CFLAGS) signal_handler.c -o signal_handler

page_replacement: page_replacement.c
	$(CC) $(CFLAGS) page_replacement.c -o page_replacement

skilling1: skilling1.c
	$(CC) $(CFLAGS) skilling1.c -o skilling1

skilling2: skilling2.c
	$(CC) $(CFLAGS) skilling2.c -o skilling2

skilling3: skilling3.c
	$(CC) $(CFLAGS) skilling3.c -o skilling3

skilling4: skilling4.c
	$(CC) $(CFLAGS) skilling4.c -o skilling4

skilling5: skilling5.c
	$(CC) $(CFLAGS) skilling5.c -o skilling5

skilling6: skilling6.c
	$(CC) $(CFLAGS) skilling6.c -o skilling6

clean:
	rm -f $(PRACTICALS) $(SKILLINGS) a.out access.log output.txt sample_source.txt sample_destination.txt /tmp/server_fifo /tmp/client_*_fifo
