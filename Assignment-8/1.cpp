// FCFS CPU Scheduling with Arrival Time and Idle Handling
#include <stdio.h>
int main() {
int n, i, j;
printf("Enter number of processes: ");
scanf("%d", &n);
int pid[n], at[n], bt[n];
int ct[n], tat[n], wt[n];
float avg_tat = 0, avg_wt = 0;
int total_tat = 0, total_wt = 0;

// Input
for (i = 0; i < n; i++) {
    printf("Enter Process ID, Arrival Time and Burst Time for process %d: ", i + 1);
    scanf("%d %d %d", &pid[i], &at[i], &bt[i]);
}

// Sort by Arrival Time (simple bubble sort)
for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
        if (at[j] > at[j + 1]) {
            int temp;

            temp = at[j];
            at[j] = at[j + 1];
            at[j + 1] = temp;

            temp = bt[j];
            bt[j] = bt[j + 1];
            bt[j + 1] = temp;

            temp = pid[j];
            pid[j] = pid[j + 1];
            pid[j + 1] = temp;
        }
    }
}

int current_time = 0;

// Calculate CT, TAT, WT
for (i = 0; i < n; i++) {
    if (current_time < at[i]) {
        // CPU idle until next process arrives
        current_time = at[i];
    }
    current_time += bt[i];
    ct[i] = current_time;

    tat[i] = ct[i] - at[i];
    wt[i] = tat[i] - bt[i];

    total_tat += tat[i];
    total_wt += wt[i];
}

avg_tat = (float) total_tat / n;
avg_wt = (float) total_wt / n;

// Output table
printf("\nFCFS Scheduling Result:\n");
printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
for (i = 0; i < n; i++) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
}

printf("\nTotal Turnaround Time = %d", total_tat);
printf("\nTotal Waiting Time    = %d", total_wt);
printf("\nAverage TAT           = %.2f", avg_tat);
printf("\nAverage WT            = %.2f\n", avg_wt);

return 0;


}
