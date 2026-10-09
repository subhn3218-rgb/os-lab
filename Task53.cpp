#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Process { int pid, arrival, burst, remaining, completion, turnaround, wait; };

int main() {
    int quantum = 2;
    vector<Process> processes = { {1,0,3,3,0,0,0}, {2,0,2,2,0,0,0}, {3,0,4,4,0,0,0} };
    int n = processes.size(), current_time = 0, next_arrival = 0;
    queue<int> q;
    vector<bool> queued(n, false);

    auto enqueueArrivals = [&]() {
        for (int i = 0; i < n; i++)
            if (!queued[i] && processes[i].arrival <= current_time) { q.push(i); queued[i] = true; }
    };

    enqueueArrivals();
    cout << "Quantum = " << quantum << endl << "Execution : ";
    bool first = true;
    while (!q.empty()) {
        int i = q.front(); q.pop();
        Process& p = processes[i];
        int slice = min(quantum, p.remaining);
        p.remaining -= slice;
        current_time += slice;
        cout << (first ? "" : " -> ") << "P" << p.pid << " (" << slice << " ms)";
        first = false;
        enqueueArrivals();                         
        if (p.remaining > 0) q.push(i);
        else {
            p.completion = current_time;
            p.turnaround = p.completion - p.arrival;
            p.wait = p.turnaround - p.burst;
        }
    }
    cout << endl << "PID | Turnaround | Wait" << endl;
    for (auto& p : processes)
        cout << "P" << p.pid << " | " << p.turnaround << " | " << p.wait << endl;
    return 0;
}
