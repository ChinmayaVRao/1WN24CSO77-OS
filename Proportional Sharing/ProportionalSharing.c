#include <stdio.h>
#include <float.h>

typedef struct {
    int id;
    int execution_time;
    int period;
    int weight;
    int remaining_time;
    double stride;
    double pass; // Virtual time / priority tracker
} Task;

#define LARGE_CONSTANT 10000 // Used to calculate stride from weight

int main() {
    int n, total_time;
    double total_weight = 0;
    double total_utilization = 0;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task tasks[n];

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Task %d - Execution (Ci), Period (Ti), and Weight (Wi): ", i + 1);
        scanf("%d %d %d", &tasks[i].execution_time, &tasks[i].period, &tasks[i].weight);

        tasks[i].remaining_time = 0;
        tasks[i].pass = 0; // Initialize virtual time
        total_weight += tasks[i].weight;
        total_utilization += (double)tasks[i].execution_time / tasks[i].period;
    }

    // Step 4: Check Feasibility
    printf("\n--- Analysis ---\n");
    printf("Total Utilization (U): %.4f\n", total_utilization);
    if (total_utilization > 1.0) {
        printf("Warning: System is overloaded (U > 1.0). Scheduling may fail.\n");
    } else {
        printf("System is feasible.\n");
    }

    // Step 2 & 3: Calculate Strides
    // Stride is inversely proportional to weight
    for (int i = 0; i < n; i++) {
        tasks[i].stride = (double)LARGE_CONSTANT / tasks[i].weight;
        printf("Task %d: Share = %.2f%%, Stride = %.2f\n",
                tasks[i].id, (tasks[i].weight / total_weight) * 100, tasks[i].stride);
    }

    printf("\n--- Simulation ---\n");
    printf("Enter simulation duration: ");
    scanf("%d", &total_time);

    for (int t = 0; t < total_time; t++) {
        // Handle task arrivals based on Period
        for (int i = 0; i < n; i++) {
            if (t % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].execution_time;
                // Note: In some implementations, pass is reset or adjusted here
            }
        }

        int selected_task = -1;
        double min_pass = DBL_MAX;

        // Step 5: Select task with the SMALLEST pass (virtual time)
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                if (tasks[i].pass < min_pass) {
                    min_pass = tasks[i].pass;
                    selected_task = i;
                }
            }
        }

        if (selected_task != -1) {
            printf("Time %d: Executing Task %d (Pass: %.2f)\n",
                    t, tasks[selected_task].id, tasks[selected_task].pass);

            tasks[selected_task].remaining_time--;

            // Update virtual time by adding the stride
            tasks[selected_task].pass += tasks[selected_task].stride;
        } else {
            printf("Time %d: Idle\n", t);
        }
    }

    return 0;
}
