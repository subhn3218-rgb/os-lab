#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Process { int pid, arrival, burst, completion, turnaround, wait; };

int main() {
    vector<Process> processes = { {1,0,5,0,0,0}, {2,1,3,0,0,0}, {3,2,8,0,0,0} };
    sort(processes.begin(), processes.end(),
         [](const Process& a, const Process& b) { return a.arrival < b.arrival; });

    int current_time = 0;
    double total_wait = 0;
    for (auto& p : processes) {
        if (current_time < p.arrival) current_time = p.arrival;
        p.completion = current_time + p.burst;
        p.turnaround = p.completion - p.arrival;
        p.wait = p.turnaround - p.burst;
        current_time = p.completion;
        total_wait += p.wait;
    }
    cout << "PID | Arrival | Burst | Completion | Turnaround | Wait" << endl;
    for (auto& p : processes)
        cout << "P" << p.pid << " | " << p.arrival << " | " << p.burst << " | " << p.completion
             << " | " << p.turnaround << " | " << p.wait << endl;
    cout << fixed << setprecision(2) << "Average Waiting Time : " << total_wait / processes.size() << " ms" << endl;
    return 0;
}
