#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef struct {
    int id;
    int execution_time;
    int period;
    int remaining_time;
    int next_deadline;
} Task;

void sortTasksByPeriod(Task tasks[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tasks[j].period > tasks[j + 1].period) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, total_time;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task tasks[n];
    double utilization = 0;

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Task %d - Execution Time (Ci) and Period (Ti): ", i + 1);
        scanf("%d %d", &tasks[i].execution_time, &tasks[i].period);
        tasks[i].remaining_time = 0; // Initially no work
        tasks[i].next_deadline = 0;
        utilization += (double)tasks[i].execution_time / tasks[i].period;
    }

    // Step 2: Calculate RMS Bound
    double bound = n * (pow(2.0, 1.0 / n) - 1);

    printf("\n--- Analysis ---\n");
    printf("CPU Utilization (U): %.4f\n", utilization);
    printf("RMS Bound: %.4f\n", bound);

    if (utilization <= bound) {
        printf("Result: Schedulable using RMS.\n");
    } else {
        printf("Result: Not guaranteed (U > Bound). Further analysis needed.\n");
    }

    // Step 4: Assign Priorities (Sort by Period)
    sortTasksByPeriod(tasks, n);

    printf("\n--- Simulation ---\n");
    printf("Enter total simulation time: ");
    scanf("%d", &total_time);

    for (int t = 0; t < total_time; t++) {
        int active_task = -1;

        // Check for task arrivals/renewals
        for (int i = 0; i < n; i++) {
            if (t % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].execution_time;
            }
        }

        // Step 5: Select highest priority (lowest period) task that is READY
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                active_task = i;
                break; // Because they are sorted by period, first one found is highest priority
            }
        }

        if (active_task != -1) {
            printf("Time %d: Executing Task %d\n", t, tasks[active_task].id);
            tasks[active_task].remaining_time--;
        } else {
            printf("Time %d: Idle\n", t);
        }
    }

    return 0;
}