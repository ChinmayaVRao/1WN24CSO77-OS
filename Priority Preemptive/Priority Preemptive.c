#include <stdio.h>

#define MAX_PROCESSES 10
#define INF 9999

struct Process {
    int pid, at, bt, pr, ct, tat, wt, remaining_bt, done;
};

// Main function to simulate the scheduler
int main() {
    int n, time = 0, completed = 0;
    struct Process p[MAX_PROCESSES];
    float totalTAT = 0, totalWT = 0;

    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    // Input Process Details (Arrival Time, Burst Time, Priority)
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d - AT, BT, Priority: ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].remaining_bt = p[i].bt;
        p[i].done = 0;
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    // Loop until all processes are finished
    while (completed < n) {
        int idx = -1, highestPriority = INF;
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time && p[i].remaining_bt > 0) {
                if (p[i].pr < highestPriority || (p[i].pr == highestPriority && (idx == -1 || p[i].at < p[idx].at))) {
                    highestPriority = p[i].pr;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].remaining_bt--;
            time++;
            if (p[idx].remaining_bt == 0) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].done = 1;
                completed++;
                printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[idx].pid, p[idx].at, p[idx].bt, p[idx].pr, p[idx].ct, p[idx].tat, p[idx].wt);
            }
        } else time++;
    }

    // Output average metrics
    for (int i = 0; i < n; i++) {
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }
    printf("Avg TAT: %.2f, Avg WT: %.2f\n", totalTAT / n, totalWT / n);
    return 0;
}
