//Write a program using C/C++/Java to simulate the priority scheduling (pre-emptive as well as non-preemptive approach) and RR, CPU scheduling algorithms. The scenario is: user may input n processes with respective CPU burst time and arrival time (also take the priority number in case of priority scheduling). System will ask the user to select the type of algorithm from the list mentioned above. System should display the waiting time for each process, average waiting time for the whole system, and final execution sequence.
#include <iostream>
using namespace std;

class Process {
    public:
    int pid, arrival, burst, waiting, turnaround, remaining;
};

void roundRobin(Process processes[], int n, int timeQuantum) {
    int time = 0, completed = 0;
    int executionSequence[1000], seqLength = 0;

    for (int i = 0; i < n; i++) processes[i].remaining = processes[i].burst;

    while (completed < n) {
        bool executed = false;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= time && processes[i].remaining > 0) {
                executed = true; // Process executed
                executionSequence[seqLength++] = processes[i].pid;

                if (processes[i].remaining > timeQuantum) {
                    processes[i].remaining -= timeQuantum;
                    time += timeQuantum;
                } else {
                    time += processes[i].remaining;
                    processes[i].remaining = 0;
                    processes[i].turnaround = time - processes[i].arrival;
                    processes[i].waiting = processes[i].turnaround - processes[i].burst;
                    completed++;
                }
            }
        }

        // If no process was executed, advance time
        if (!executed) {
            time++;
        }
    }

    cout << "\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n";
    double totalWait = 0;
    for (int i = 0; i < n; i++) {
        totalWait += processes[i].waiting;
        cout << "P" << processes[i].pid << "\t" << processes[i].arrival << "\t"
             << processes[i].burst << "\t" << processes[i].waiting << "\t"
             << processes[i].turnaround << endl;
    }

    cout << "\nAverage Waiting Time: " << totalWait / n << endl;
    cout << "\nExecution Sequence: ";
    for (int i = 0; i < seqLength; i++) {
        cout << "P" << executionSequence[i] << " ";
    }
    cout << endl;
}

int main() {
    int n, timeQuantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time and burst time for process P" << i + 1 << ": ";
        cin >> processes[i].arrival >> processes[i].burst;
    }

    cout << "Enter time quantum: ";
    cin >> timeQuantum;

    roundRobin(processes, n, timeQuantum);
    return 0;
}