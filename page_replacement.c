/*
 * Page Replacement Algorithms Simulation
 * Covers:
 *   1. FIFO (First-In, First-Out)
 *   2. Optimal Page Replacement
 *   3. LRU (Least Recently Used)
 *   4. MRU (Most Recently Used)
 *
 * Includes built-in test suites from standard OSSP lab handouts and interactive mode.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FRAMES 32
#define MAX_PAGES 128

void print_frames(int frames[], int num_frames) {
    printf("[ ");
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == -1) {
            printf("- ");
        } else {
            printf("%d ", frames[i]);
        }
    }
    printf("]");
}

// 1. First In First Out (FIFO)
int run_fifo(const int pages[], int n, int num_frames) {
    int frames[MAX_FRAMES];
    for (int i = 0; i < num_frames; i++) frames[i] = -1;

    int page_faults = 0;
    int next_replace_idx = 0;

    printf("\n--- FIFO Page Replacement (Frames = %d) ---\n", num_frames);
    printf("Incoming Page | Frame State       | Status\n");
    printf("--------------+-------------------+-------------\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool hit = false;

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                hit = true;
                break;
            }
        }

        if (hit) {
            printf("      %2d      | ", page);
            print_frames(frames, num_frames);
            printf(" | Hit\n");
        } else {
            page_faults++;
            frames[next_replace_idx] = page;
            next_replace_idx = (next_replace_idx + 1) % num_frames;

            printf("      %2d      | ", page);
            print_frames(frames, num_frames);
            printf(" | Page Fault\n");
        }
    }

    printf("--------------+-------------------+-------------\n");
    printf("Total Page Faults: %d\n", page_faults);
    printf("Total Hits: %d\n", n - page_faults);
    printf("Hit Ratio: %.2f%%\n", ((double)(n - page_faults) / n) * 100);
    return page_faults;
}

// 2. Optimal Page Replacement
int run_optimal(const int pages[], int n, int num_frames) {
    int frames[MAX_FRAMES];
    for (int i = 0; i < num_frames; i++) frames[i] = -1;

    int page_faults = 0;

    printf("\n--- Optimal Page Replacement (Frames = %d) ---\n", num_frames);
    printf("Incoming Page | Frame State       | Status\n");
    printf("--------------+-------------------+-------------\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool hit = false;

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                hit = true;
                break;
            }
        }

        if (hit) {
            printf("      %2d      | ", page);
            print_frames(frames, num_frames);
            printf(" | Hit\n");
        } else {
            page_faults++;
            int empty_slot = -1;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    empty_slot = j;
                    break;
                }
            }

            if (empty_slot != -1) {
                frames[empty_slot] = page;
            } else {
                // Find page not used for longest duration in future
                int farthest = i + 1;
                int victim_idx = 0;

                for (int j = 0; j < num_frames; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k]) {
                            if (k > farthest) {
                                farthest = k;
                                victim_idx = j;
                            }
                            break;
                        }
                    }
                    // If frame page never appears again in future, replace immediately
                    if (k == n) {
                        victim_idx = j;
                        break;
                    }
                }
                frames[victim_idx] = page;
            }

            printf("      %2d      | ", page);
            print_frames(frames, num_frames);
            printf(" | Page Fault\n");
        }
    }

    printf("--------------+-------------------+-------------\n");
    printf("Total Page Faults: %d\n", page_faults);
    printf("Total Hits: %d\n", n - page_faults);
    printf("Hit Ratio: %.2f%%\n", ((double)(n - page_faults) / n) * 100);
    return page_faults;
}

// 3. Least Recently Used (LRU)
int run_lru(const int pages[], int n, int num_frames) {
    int frames[MAX_FRAMES];
    int last_used[MAX_FRAMES];
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }

    int page_faults = 0;

    printf("\n--- LRU Page Replacement (Frames = %d) ---\n", num_frames);
    printf("Incoming Page | Frame State       | Status\n");
    printf("--------------+-------------------+-------------\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool hit = false;
        int hit_idx = -1;

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                hit = true;
                hit_idx = j;
                break;
            }
        }

        if (hit) {
            last_used[hit_idx] = i;
            printf("      %2d      | ", page);
            print_frames(frames, num_frames);
            printf(" | Hit\n");
        } else {
            page_faults++;
            int empty_slot = -1;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    empty_slot = j;
                    break;
                }
            }

            if (empty_slot != -1) {
                frames[empty_slot] = page;
                last_used[empty_slot] = i;
            } else {
                // Find least recently used
                int min_time = last_used[0];
                int victim_idx = 0;
                for (int j = 1; j < num_frames; j++) {
                    if (last_used[j] < min_time) {
                        min_time = last_used[j];
                        victim_idx = j;
                    }
                }
                frames[victim_idx] = page;
                last_used[victim_idx] = i;
            }

            printf("      %2d      | ", page);
            print_frames(frames, num_frames);
            printf(" | Page Fault\n");
        }
    }

    printf("--------------+-------------------+-------------\n");
    printf("Total Page Faults: %d\n", page_faults);
    printf("Total Hits: %d\n", n - page_faults);
    printf("Hit Ratio: %.2f%%\n", ((double)(n - page_faults) / n) * 100);
    return page_faults;
}

// 4. Most Recently Used (MRU)
int run_mru(const int pages[], int n, int num_frames) {
    int frames[MAX_FRAMES];
    int last_used[MAX_FRAMES];
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }

    int page_faults = 0;

    printf("\n--- MRU Page Replacement (Frames = %d) ---\n", num_frames);
    printf("Incoming Page | Frame State       | Status\n");
    printf("--------------+-------------------+-------------\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool hit = false;
        int hit_idx = -1;

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                hit = true;
                hit_idx = j;
                break;
            }
        }

        if (hit) {
            last_used[hit_idx] = i;
            printf("      %2d      | ", page);
            print_frames(frames, num_frames);
            printf(" | Hit\n");
        } else {
            page_faults++;
            int empty_slot = -1;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    empty_slot = j;
                    break;
                }
            }

            if (empty_slot != -1) {
                frames[empty_slot] = page;
                last_used[empty_slot] = i;
            } else {
                // Find most recently used
                int max_time = -1;
                int victim_idx = 0;
                for (int j = 0; j < num_frames; j++) {
                    if (last_used[j] > max_time) {
                        max_time = last_used[j];
                        victim_idx = j;
                    }
                }
                frames[victim_idx] = page;
                last_used[victim_idx] = i;
            }

            printf("      %2d      | ", page);
            print_frames(frames, num_frames);
            printf(" | Page Fault\n");
        }
    }

    printf("--------------+-------------------+-------------\n");
    printf("Total Page Faults: %d\n", page_faults);
    printf("Total Hits: %d\n", n - page_faults);
    printf("Hit Ratio: %.2f%%\n", ((double)(n - page_faults) / n) * 100);
    return page_faults;
}

void run_all_algorithms(const int pages[], int n, int num_frames) {
    printf("\n=========================================================\n");
    printf(" Reference String: ");
    for (int i = 0; i < n; i++) printf("%d ", pages[i]);
    printf("\n Frames: %d\n", num_frames);
    printf("=========================================================\n");

    int f_fifo = run_fifo(pages, n, num_frames);
    int f_opt = run_optimal(pages, n, num_frames);
    int f_lru = run_lru(pages, n, num_frames);
    int f_mru = run_mru(pages, n, num_frames);

    printf("\n=========================================================\n");
    printf("                 COMPARISON SUMMARY                      \n");
    printf("=========================================================\n");
    printf(" Algorithm            | Page Faults | Page Hits | Hit Ratio\n");
    printf("----------------------+-------------+-----------+----------\n");
    printf(" FIFO                 |     %3d     |    %3d    |  %6.2f%%\n", f_fifo, n - f_fifo, ((double)(n - f_fifo)/n)*100);
    printf(" Optimal              |     %3d     |    %3d    |  %6.2f%%\n", f_opt, n - f_opt, ((double)(n - f_opt)/n)*100);
    printf(" LRU (Least Recent)   |     %3d     |    %3d    |  %6.2f%%\n", f_lru, n - f_lru, ((double)(n - f_lru)/n)*100);
    printf(" MRU (Most Recent)    |     %3d     |    %3d    |  %6.2f%%\n", f_mru, n - f_mru, ((double)(n - f_mru)/n)*100);
    printf("=========================================================\n");
}

int main() {
    int choice;
    printf("=========================================================\n");
    printf("       OSSP: Page Replacement Algorithms Simulator       \n");
    printf("=========================================================\n");
    printf("1. Run Handout Example 1 (FIFO demo: 1 3 0 3 5 6 3 with 3 frames)\n");
    printf("2. Run Handout Example 2 (Optimal / LRU / MRU: 7 0 1 2 0 3 0 4 2 3 0 3 2 3 with 4 frames)\n");
    printf("3. Enter Custom Reference String and Frame Capacity\n");
    printf("Enter choice (1-3): ");

    if (scanf("%d", &choice) != 1) {
        choice = 2; // Default to comprehensive example
    }

    if (choice == 1) {
        int pages[] = {1, 3, 0, 3, 5, 6, 3};
        int n = sizeof(pages) / sizeof(pages[0]);
        run_all_algorithms(pages, n, 3);
    } else if (choice == 2) {
        int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 3};
        int n = sizeof(pages) / sizeof(pages[0]);
        run_all_algorithms(pages, n, 4);
    } else {
        int n, num_frames;
        printf("Enter number of page references: ");
        if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_PAGES) return 1;
        int pages[MAX_PAGES];
        printf("Enter page reference string (separated by spaces): ");
        for (int i = 0; i < n; i++) {
            if (scanf("%d", &pages[i]) != 1) return 1;
        }
        printf("Enter number of frames: ");
        if (scanf("%d", &num_frames) != 1 || num_frames <= 0 || num_frames > MAX_FRAMES) return 1;

        run_all_algorithms(pages, n, num_frames);
    }

    return 0;
}
