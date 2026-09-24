# OS Practicals & Skilling Sessions

Operating Systems and Systems Programming (OSSP) — 25CS2104E Laboratory and Skilling Sessions Repository.

##  Repository Structure

###  Practical Sessions
- **`prog1.c`** — Practical 1: Command Execution using `fork()`, `execvp()`, and `wait()`.
- **`prog2.c`** — Practical 2: File Copy using POSIX system calls (`open`, `read`, `write`, `close`).
- **`prog3.c`** — Practical 3: Process Lifecycle, PID/PPID inspection, and execution states.
- **`prog4.c`** — Practical 4: Process Synchronization comparing `wait()` and `waitpid()`.
- **`prog5.c`** — Practical 5: Producer-Consumer Inter-Process Communication (IPC) via Anonymous Pipes.

###  Skilling Sessions (Project-Based Learning)
- **`skilling1.c`** — Skilling Session 1: Shell REPL architecture and interactive input loop.
- **`skilling2.c`** — Skilling Session 2: User authentication gate and command whitelisting.
- **`skilling3.c`** — Skilling Session 3: Process synchronization with `waitpid()` and exit status macros.
- **`skilling4.c`** — Skilling Session 4: Shell built-in commands (`cd`, `pwd`, `env`) executed in parent process.
- **`skilling5.c`** — Skilling Session 5: POSIX signal handling (`SIGINT` Ctrl+C interception and `SIGCHLD` zombie reaper).
- **`skilling6.c`** — Skilling Session 6: Complete integrated Restricted Shell with security sanitization and audit logging.

##  Build and Run

To compile all practicals and skilling programs:
```bash
make
```

To run a specific practical or skilling program:
```bash
./prog1
./prog4
./prog5
./skilling2
./skilling5
./skilling6
```

To clean compiled binaries:
```bash
make clean
```
