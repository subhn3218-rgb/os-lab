#include <iostream>
#include <vector>
using namespace std;

struct Process { int pid, priority, burst, arrival, remaining, completion, wait; };

int main() {
    vector<Process> processes = { {1,2,4,0,4,0,0}, {2,1,3,1,3,0,0}, {3,3,2,2,2,0,0} };
    int current_time = 0, completed = 0, n = processes.size();

    while (completed < n) {
        int best = -1;
        for (int i = 0; i < n; i++)
            if (processes[i].arrival <= current_time && processes[i].remaining > 0 &&
                (best == -1 || processes[i].priority < processes[best].priority))
                best = i;
        if (best == -1) { current_time++; continue; }
        Process& p = processes[best];
        p.remaining--;
        current_time++;
        if (p.remaining == 0) {
            p.completion = current_time;
            p.wait = (p.completion - p.arrival) - p.burst;
            completed++;
        }
    }
    cout << "PID | Priority | Burst | Arrival | Waiting Time" << endl;
    for (auto& p : processes)
        cout << "P" << p.pid << " | " << p.priority << " | " << p.burst << " | " << p.arrival << " | " << p.wait << endl;
    return 0;
}
