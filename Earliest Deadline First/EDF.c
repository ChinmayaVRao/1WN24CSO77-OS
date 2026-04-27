#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int id;
    int execution_time;
    int period;
    int remaining_time;
    int absolute_deadline;
} Task;

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
        tasks[i].remaining_time = 0;
        tasks[i].absolute_deadline = 0;
        utilization += (double)tasks[i].execution_time / tasks[i].period;
    }

    // Step 2: Check Feasibility
    printf("\n--- Analysis ---\n");
    printf("Total CPU Utilization (U): %.4f\n", utilization);

    if (utilization <= 1.0) {
        printf("Result: Schedulable using EDF.\n");
    } else {
        printf("Result: Not schedulable (Utilization > 1.0).\n");
        return 1; // Exit as it will definitely fail
    }

    printf("\n--- Simulation ---\n");
    printf("Enter total simulation time: ");
    scanf("%d", &total_time);

    for (int t = 0; t < total_time; t++) {
        // Step 3: Assign/Update Absolute Deadlines upon task arrival
        for (int i = 0; i < n; i++) {
            if (t % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].absolute_deadline = t + tasks[i].period;
            }
        }

        int active_task = -1;
        int min_deadline = 999999; // Represents infinity

        // Step 4: Select READY task with the EARLIEST absolute deadline
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                if (tasks[i].absolute_deadline < min_deadline) {
                    min_deadline = tasks[i].absolute_deadline;
                    active_task = i;
                }
            }
        }

        if (active_task != -1) {
            printf("Time %d: Executing Task %d (Deadline: %d)\n",
                    t, tasks[active_task].id, tasks[active_task].absolute_deadline);
            tasks[active_task].remaining_time--;

            // Check if task missed its deadline
            if (tasks[active_task].remaining_time > 0 && (t + 1) >= tasks[active_task].absolute_deadline) {
                printf("  [!] Task %d missed its deadline at time %d!\n", tasks[active_task].id, t + 1);
            }
        } else {
            printf("Time %d: Idle\n", t);
        }
    }

    return 0;
}
