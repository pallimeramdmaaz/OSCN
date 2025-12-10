#include <bits/stdc++.h>
using namespace std;

struct GSeg { int pid; int start; int end; };

int main() {
    int n = 5;
    vector<int> AT = {4, 0, 6, 2, 1};
    vector<int> BT = {7, 5, 3, 9, 4}; 
    int quantum = 3;

    vector<int> rem = BT;
    vector<int> CT(n, 0);
    vector<int> added(n, 0); 

    deque<int> q;
    int time = 0;
    int completed = 0;

    for (int i = 0; i < n; ++i) {
        if (AT[i] <= time && !added[i]) {
            q.push_back(i);
            added[i] = 1;
        }
    }

    if (q.empty()) {
        int nextAt = INT_MAX;
        for (int i = 0; i < n; ++i) if (!added[i]) nextAt = min(nextAt, AT[i]);
        time = nextAt;
        for (int i = 0; i < n; ++i) {
            if (AT[i] <= time && !added[i]) {
                q.push_back(i);
                added[i] = 1;
            }
        }
    }

    vector<GSeg> gantt;

    while (completed < n) {
        if (q.empty()) {
            int nextAt = INT_MAX;
            for (int i = 0; i < n; ++i) if (!added[i]) nextAt = min(nextAt, AT[i]);
            time = nextAt;
            for (int i = 0; i < n; ++i) {
                if (AT[i] <= time && !added[i]) {
                    q.push_back(i);
                    added[i] = 1;
                }
            }
            continue;
        }

        int idx = q.front(); q.pop_front();
        int exec = min(rem[idx], quantum);
        int start = time;
        int end = time + exec;

        rem[idx] -= exec;
        time = end;

        gantt.push_back({idx+1, start, end});

        for (int i = 0; i < n; ++i) {
            if (AT[i] <= time && !added[i]) {
                q.push_back(i);
                added[i] = 1;
            }
        }

        if (rem[idx] == 0) {
            CT[idx] = time;
            completed++;
        } else {
            q.push_back(idx);
        }
    }

    cout << "Gantt chart segments:\n";
    for (auto &s : gantt) cout << "| P" << s.pid << " ";
    cout << "|\n";
    for (auto &s : gantt) cout << s.start << "    ";
    cout << gantt.back().end << "\n\n";

    cout << left << setw(6) << "Proc" << setw(6) << "AT" << setw(6) << "BT"
         << setw(6) << "CT" << setw(6) << "TAT" << setw(6) << "WT" << "\n";

    double sumTAT = 0.0, sumWT = 0.0;
    for (int i = 0; i < n; ++i) {
        int tat = CT[i] - AT[i];
        int wt  = tat - BT[i];
        sumTAT += tat;
        sumWT  += wt;
        cout << "P" << (i+1) << setw(5) << "" 
             << setw(6) << AT[i] << setw(6) << BT[i]
             << setw(6) << CT[i] << setw(6) << tat << setw(6) << wt << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage TAT = " << (sumTAT / n) << " ms\n";
    cout << "Average WT  = " << (sumWT / n)  << " ms\n";

    return 0;
}
