#include <stdio.h>

#define MAX 100

int main() {
    int n;
    int PID[MAX], AT[MAX], BT[MAX], TYPE[MAX];
    int CT[MAX], TAT[MAX], WT[MAX], Start[MAX];

    int sysQueue[MAX], userQueue[MAX];
    int sysCount = 0, userCount = 0;

    int i, j, temp;
    int time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("PID: ");
        scanf("%d", &PID[i]);
        printf("Arrival Time: ");
        scanf("%d", &AT[i]);
        printf("Burst Time: ");
        scanf("%d", &BT[i]);
        printf("Type (0 = System, 1 = User): ");
        scanf("%d", &TYPE[i]);
    }

    // Step 1: Separate into queues
    for(i = 0; i < n; i++) {
        if(TYPE[i] == 0)
            sysQueue[sysCount++] = i;
        else
            userQueue[userCount++] = i;
    }

    // Step 2: Sort System Queue by Arrival Time
    for(i = 0; i < sysCount - 1; i++) {
        for(j = i + 1; j < sysCount; j++) {
            if(AT[sysQueue[i]] > AT[sysQueue[j]]) {
                temp = sysQueue[i];
                sysQueue[i] = sysQueue[j];
                sysQueue[j] = temp;
            }
        }
    }

    // Sort User Queue by Arrival Time
    for(i = 0; i < userCount - 1; i++) {
        for(j = i + 1; j < userCount; j++) {
            if(AT[userQueue[i]] > AT[userQueue[j]]) {
                temp = userQueue[i];
                userQueue[i] = userQueue[j];
                userQueue[j] = temp;
            }
        }
    }

    // Step 3: Execute System Processes first
    for(i = 0; i < sysCount; i++) {
        int p = sysQueue[i];

        if(time < AT[p])
            time = AT[p];

        Start[p] = time;
        time += BT[p];
        CT[p] = time;

        TAT[p] = CT[p] - AT[p];
        WT[p] = TAT[p] - BT[p];
    }

    // Step 4: Execute User Processes after System queue
    for(i = 0; i < userCount; i++) {
        int p = userQueue[i];

        if(time < AT[p])
            time = AT[p];

        Start[p] = time;
        time += BT[p];
        CT[p] = time;

        TAT[p] = CT[p] - AT[p];
        WT[p] = TAT[p] - BT[p];
    }

    // Step 5: Display results
    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               PID[i], AT[i], BT[i], TYPE[i],
               CT[i], TAT[i], WT[i]);
    }

    return 0;
}