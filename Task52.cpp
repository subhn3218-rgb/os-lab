#include <iostream>
#include <vector>
using namespace std;

struct Process { int pid, arrival, burst, remaining, completion, turnaround, wait; };

int main() {
    vector<Process> processes = { {1,0,6,6,0,0,0}, {2,1,4,4,0,0,0}, {3,3,2,2,0,0,0} };
    int current_time = 0, completed = 0, n = processes.size();
    int last = -1, seg_start = 0;
    cout << "Timeline : ";

    while (completed < n) {
        int best = -1;
        for (int i = 0; i < n; i++)
            if (processes[i].arrival <= current_time && processes[i].remaining > 0 &&
                (best == -1 || processes[i].remaining < processes[best].remaining))
                best = i;
        if (best == -1) { current_time++; continue; }

        if (best != last) {                       // context switch: close previous segment
            if (last != -1) cout << "[P" << processes[last].pid << " : " << seg_start << "-" << current_time << "] ";
            seg_start = current_time;
            last = best;
        }
        Process& p = processes[best];
        p.remaining--;
        current_time++;
        if (p.remaining == 0) {
            p.completion = current_time;
            p.turnaround = p.completion - p.arrival;
            p.wait = p.turnaround - p.burst;
            completed++;
        }
    }
    cout << "[P" << processes[last].pid << " : " << seg_start << "-" << current_time << "]" << endl;
    cout << "PID | Completion | Waiting Time" << endl;
    for (auto& p : processes)
        cout << "P" << p.pid << " | " << p.completion << " | " << p.wait << endl;
    return 0;
}
