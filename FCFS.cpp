#include <iostream>
using namespace std;

class Process {
    public:
    int pid, arrival, burst, waiting, turnaround;
};

void fcfs(Process processes[], int n) {
    int time = 0;
    double totalWait = 0;

    cout << "\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n";
    // if any process doesn't start at arrival time of t = 0 then:
    for (int i = 0; i < n; i++) {
        if (time < processes[i].arrival) {
            time = processes[i].arrival; 
            // time is set to last process's arrival time
        }

        processes[i].waiting = time - processes[i].arrival;
        processes[i].turnaround = processes[i].waiting + processes[i].burst;
        totalWait += processes[i].waiting;

        cout << "P" << processes[i].pid << "\t" << processes[i].arrival << "\t"
             << processes[i].burst << "\t" << processes[i].waiting << "\t"
             << processes[i].turnaround << endl;

        time += processes[i].burst;
    }

    cout << "\nAverage Waiting Time: " << totalWait / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time and burst time for process P" << i + 1 << ": ";
        cin >> processes[i].arrival >> processes[i].burst;
    }

    fcfs(processes, n);
    return 0;
}