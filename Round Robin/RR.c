#include <stdio.h>

int main() {
    int n, tq;
    int at[20], bt[20], rem_bt[20];
    int ct[20], tat[20], wt[20];
    int i, time = 0, remain;
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rem_bt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    remain = n;
    time = 0;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    while(remain > 0) {
        int done = 1;

        for(i = 0; i < n; i++) {

            if(at[i] <= time && rem_bt[i] > 0) {

                done = 0;

                if(rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                }
                else {
                    time += rem_bt[i];
                    ct[i] = time;
                    rem_bt[i] = 0;

                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];

                    printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                           i+1, at[i], bt[i], ct[i], tat[i], wt[i]);

                    total_wt += wt[i];
                    total_tat += tat[i];

                    remain--;
                }
            }
        }

        if(done) {
            time++;   // move time forward if no process available
        }
    }

    printf("\nAverage Waiting Time = %.2f", total_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat/n);

    return 0;
}
