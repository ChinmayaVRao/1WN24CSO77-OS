#include <stdio.h>

int main() {
    int n, bt[20], wt[20], tat[20], at[20], ct[20];
    int i;
    float twt = 0.0, ttat = 0.0, awt, att;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input Arrival Time and Burst Time
    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // FCFS Scheduling Logic

    // First process
    ct[0] = at[0] + bt[0];
    tat[0] = ct[0] - at[0];
    wt[0] = 0;   // First process has no waiting time

    // Remaining processes
    for (i = 1; i < n; i++) {

        // If CPU is idle
        if (at[i] > ct[i - 1]) {
            ct[i] = at[i] + bt[i];
        } else {
            ct[i] = ct[i - 1] + bt[i];
        }

        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        // Safety check (optional)
        if (wt[i] < 0)
            wt[i] = 0;
    }

    // Calculate totals
    for (i = 0; i < n; i++) {
        twt += wt[i];
        ttat += tat[i];
    }

    awt = twt / n;
    att = ttat / n;

    // Output Table
    printf("\n%-10s%-10s%-10s%-10s%-10s%-10s",
           "PROCESS", "AT", "BT", "CT", "WT", "TAT");

    for (i = 0; i < n; i++) {
        printf("\nP%d\t\t%d\t%d\t%d\t%d\t%d",
               i + 1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f", awt);
    printf("\nAverage Turnaround Time = %.2f\n", att);

    return 0;
}
