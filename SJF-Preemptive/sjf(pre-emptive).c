#include <stdio.h>
#include <stdlib.h> // Required for malloc and realloc

// Structure to hold process details
typedef struct {
    int pid;       // Process ID
    int at;        // Arrival Time
    int bt;        // Burst Time
    int wt;        // Waiting Time
    int tat;       // Turnaround Time
} Process;

int main() {
    int n, time = 0, completed = 0, i;
    // Arrays to store remaining burst times and completion status
    int rt[100];
    int c[100] = {0};
    int total_wt = 0, total_tat = 0;
    Process p[100];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the Arrival time and Burst time for Process %d: ", p[i].pid);
        scanf("%d%d", &p[i].at, &p[i].bt);
        rt[i] = p[i].bt; // Initialize remaining time as burst time
    }

    // Main scheduling loop: runs until all processes are completed
    while (completed != n) {
        int s = -1; // Index of the selected process
        int min_rt = 999999; // Initialize with a large value

        // Find the process with the shortest remaining time among arrived processes
        for (i = 0; i < n; i++) {
            if (p[i].at <= time && c[i] == 0) {
                if (rt[i] < min_rt) {
                    min_rt = rt[i];
                    s = i;
                }
            }
        }

        // If no process is available, increment time and continue
        if (s == -1) {
            time++;
            continue;
        }

        // Execute the selected process for one time unit
        rt[s]--;
        time++;

        // If a process completes execution
        if (rt[s] == 0) {
            c[s] = 1; // Mark as completed
            completed++;
            p[s].tat = time - p[s].at; // Calculate turnaround time
            p[s].wt = p[s].tat - p[s].bt; // Calculate waiting time
        }
    }

    // Calculate total and average times
    for (i = 0; i < n; i++) {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    // Print results
    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);

    return 0;
}

