#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int waiting;
    int turnaround;
    int completed;
};

int main() {
    int n, completed = 0, current_time = 0;
    float total_wait = 0, total_turnaround = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        p[i].pid = i + 1;

        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        p[i].completed = 0;
    }

    while (completed < n) {
        int idx = -1;
        int min_burst = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= current_time && p[i].completed == 0) {
                if (p[i].burst < min_burst) {
                    min_burst = p[i].burst;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            current_time += p[idx].burst;

            p[idx].turnaround = current_time - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;

            total_wait += p[idx].waiting;
            total_turnaround += p[idx].turnaround;

            p[idx].completed = 1;
            completed++;
        } else {
            current_time++;
        }
    }

    printf("\nPID\tAT\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].waiting,
               p[i].turnaround);
    }

    printf("\nAverage Waiting Time: %.2f", total_wait / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);

    return 0;
}
