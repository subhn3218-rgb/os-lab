#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct Process { int pid, arrival, burst, completion, turnaround, wait; bool done; };

int main() {
    vector<Process> processes = { {1,0,6,0,0,0,false}, {2,1,8,0,0,0,false}, {3,2,2,0,0,0,false} };
    int current_time = 0, completed = 0, n = processes.size();
    double total_wait = 0;
    vector<int> order;

    while (completed < n) {
        int best = -1;
        for (int i = 0; i < n; i++)
            if (!processes[i].done && processes[i].arrival <= current_time &&
                (best == -1 || processes[i].burst < processes[best].burst))
                best = i;
        if (best == -1) { current_time++; continue; }
        Process& p = processes[best];
        p.completion = current_time + p.burst;
        p.turnaround = p.completion - p.arrival;
        p.wait = p.turnaround - p.burst;
        p.done = true;
        current_time = p.completion;
        completed++;
        total_wait += p.wait;
        order.push_back(best);
    }
    cout << "Execution Order : ";
    for (size_t i = 0; i < order.size(); i++)
        cout << (i ? " -> " : "") << "P" << processes[order[i]].pid;
    cout << endl << "PID | Burst | Wait Time | Turnaround Time" << endl;
    for (int idx : order) {
        Process& p = processes[idx];
        cout << "P" << p.pid << " | " << p.burst << " | " << p.wait << " | " << p.turnaround << endl;
    }
    cout << fixed << setprecision(2) << "Average Waiting Time : " << total_wait / n << " ms" << endl;
    return 0;
}
