# OS Practicals & Skilling Sessions

Operating Systems and Systems Programming (OSSP) — 25CS2104E Laboratory, Skilling Sessions, and Practical Simulations Repository.

---

## 📁 Repository Structure

### 🧪 Practical Sessions
- **`prog1.c`** — **Practical 1:** Command Execution using `fork()`, `execvp()`, and `wait()`.
- **`prog2.c`** — **Practical 2:** File Copy using low-level POSIX system calls (`open`, `read`, `write`, `close`).
- **`prog3.c`** — **Practical 3:** Process Lifecycle, PID/PPID inspection, and execution states.
- **`prog4.c`** — **Practical 4:** Process Synchronization comparing `wait()` and `waitpid()`.
- **`prog5.c`** — **Practical 5:** Producer-Consumer Inter-Process Communication (IPC) via Anonymous Pipes (`pipe()`).
- **`prog6_fifo_server.c`** — **Practical 6 (Part 1 - Server):** Multi-Client Server IPC using Named Pipes (FIFOs via `mkfifo`).
- **`prog6_fifo_client.c`** — **Practical 6 (Part 1 - Client):** Client that creates a dedicated return FIFO and communicates with the FIFO server.
- **`signal_handler.c`** — **Practical 6 (Part 2):** Asynchronous Event Handling using POSIX `sigaction()` capturing `SIGINT`, `SIGTERM`, and `SIGUSR1`.
- **`page_replacement.c`** — **Memory Management:** Page Replacement Algorithms Simulator (FIFO, Optimal, LRU, and MRU) with frame visualizations, page hit/fault tracking, and benchmark comparisons.

### 🛠️ Skilling Sessions (Restricted Shell Project)
- **`skilling1.c`** — **Skilling Session 1:** Shell REPL architecture and interactive input loop.
- **`skilling2.c`** — **Skilling Session 2:** User authentication gate and command whitelisting.
- **`skilling3.c`** — **Skilling Session 3:** Process synchronization with `waitpid()` and exit status macros.
- **`skilling4.c`** — **Skilling Session 4:** Shell built-in commands (`cd`, `pwd`, `env`) executed directly in the parent process.
- **`skilling5.c`** — **Skilling Session 5:** POSIX signal handling (`SIGINT` Ctrl+C interception and `SIGCHLD` zombie reaper).
- **`skilling6.c`** — **Skilling Session 6:** Complete integrated Restricted Shell with security sanitization and audit logging.

---

## 🚀 Build and Compilation

To compile all practicals and skilling programs at once using `gcc` with `-Wall -Wextra -g`:
```bash
make
```

To clean compiled binaries and temporary test artifacts:
```bash
make clean
```

---

## 💻 Running the Programs

### 1. Practicals 1 to 5
```bash
./prog1
./prog2
./prog3
./prog4
./prog5
```

### 2. Practical 6 (Named Pipes / FIFO Client-Server)
Open two or three terminals:

**Terminal 1 (Server):**
```bash
./prog6_fifo_server
```

**Terminal 2 (Client 1):**
```bash
./prog6_fifo_client "Hello Server from Client 1"
```

**Terminal 3 (Client 2):**
```bash
./prog6_fifo_client "Hello Server from Client 2"
```

### 3. Practical 6 (POSIX Signal Handling)
**Terminal 1:**
```bash
./signal_handler
```
**Terminal 2 (Sending signals):**
```bash
kill -SIGUSR1 <PID>    # Custom event handled
kill -SIGINT <PID>     # Interrupt handled (or press Ctrl+C in Terminal 1)
kill -SIGTERM <PID>    # Graceful shutdown
```

### 4. Page Replacement Algorithms Simulation
```bash
./page_replacement
```
Supports:
1. Built-in Handout Example 1 (FIFO demo with 3 frames)
2. Built-in Handout Example 2 (Optimal, LRU, MRU comparisons with 4 frames)
3. Custom page reference string and frame capacity input

### 5. Skilling Sessions (Restricted Shell)
```bash
./skilling1
./skilling2
./skilling3
./skilling4
./skilling5
./skilling6
```
