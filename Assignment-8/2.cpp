// Non-Preemptive SJF CPU Scheduling with Arrival Time and Gantt Chart
#include <stdio.h>
int main() {
int n, i;
printf("Enter number of processes: ");
scanf("%d", &n);
int pid[n], at[n], bt[n], ct[n], tat[n], wt[n];
int completed[n];
float avg_tat = 0, avg_wt = 0;
int total_tat = 0, total_wt = 0;

// Input
for (i = 0; i < n; i++) {
    printf("Enter Process ID, Arrival Time and Burst Time for process %d: ", i + 1);
    scanf("%d %d %d", &pid[i], &at[i], &bt[i]);
    completed[i] = 0;
}

int current_time = 0, completed_count = 0;
int gantt_order[n];
int gantt_ct[n];
int gidx = 0;

// SJF Non-Preemptive Scheduling
while (completed_count < n) {
    int idx = -1;
    int min_bt = 1000000000; // large number

    // find available process with smallest burst time
    for (i = 0; i < n; i++) {
        if (!completed[i] && at[i] <= current_time) {
            if (bt[i] < min_bt) {
                min_bt = bt[i];
                idx = i;
            }
        }
    }

    if (idx == -1) {
        // no process has arrived yet, CPU idle
        int next_at = 1000000000;
        for (i = 0; i < n; i++) {
            if (!completed[i] && at[i] < next_at) {
                next_at = at[i];
            }
        }
        current_time = next_at;
        continue;
    }

    current_time += bt[idx];
    ct[idx] = current_time;
    completed[idx] = 1;
    completed_count++;

    gantt_order[gidx] = pid[idx];
    gantt_ct[gidx] = current_time;
    gidx++;
}

// Calculate TAT and WT
for (i = 0; i < n; i++) {
    tat[i] = ct[i] - at[i];
    wt[i] = tat[i] - bt[i];
    total_tat += tat[i];
    total_wt += wt[i];
}

avg_tat = (float) total_tat / n;
avg_wt = (float) total_wt / n;

// Output table
printf("\nNon-Preemptive SJF Result:\n");
printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
for (i = 0; i < n; i++) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
}

printf("\nTotal Turnaround Time = %d", total_tat);
printf("\nTotal Waiting Time    = %d", total_wt);
printf("\nAverage TAT           = %.2f", avg_tat);
printf("\nAverage WT            = %.2f\n", avg_wt);

// Gantt Chart
printf("\nGantt Chart (PID with completion times):\n");
printf("0");
for (i = 0; i < gidx; i++) {
    printf("  | P%d |  %d", gantt_order[i], gantt_ct[i]);
}
printf("\n");

return 0;


}
