//Write a program in C/C++/Java to simulate the Banker’s algorithm for deadlock avoidance. Consider at least 3 processes in the system, with 4 resource classes having at least one resource instance for each class. Assume the values for Available, Allocation, MAX, and request from a particular process from your side. Program must reflect two cases, where a safe sequence exists for one and safe sequence does not exist for another.
#include <iostream>
using namespace std;

void runBankersAlgorithm(int numProcesses, int numResources, int maxDemand[][4], int allocated[][4], int available[]) {
    int finished[numProcesses], safeSequence[numProcesses], safeSequenceIndex = 0;

    // Initialize all processes as not finished
    for (int i = 0; i < numProcesses; i++) {
        finished[i] = 0;
    }

    // Calculate the need matrix
    int need[numProcesses][numResources];
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = maxDemand[i][j] - allocated[i][j];
        }
    }

    // Check for a safe sequence
    for (int loop = 0; loop < numProcesses; loop++) {
        for (int i = 0; i < numProcesses; i++) {
            if (!finished[i]) { // Process not yet finished
                bool canBeAllocated = true;

                // Check if the process's needs can be satisfied with available resources
                for (int j = 0; j < numResources; j++) {
                    if (need[i][j] > available[j]) {
                        canBeAllocated = false;
                        break;
                    }
                }

                if (canBeAllocated) {
                    // Add process to the safe sequence
                    safeSequence[safeSequenceIndex++] = i;

                    // Release resources allocated to this process
                    for (int j = 0; j < numResources; j++) {
                        available[j] += allocated[i][j];
                    }

                    // Mark the process as finished
                    finished[i] = 1;
                }
            }
        }
    }

    // Check if all processes could finish
    bool isSafe = true;
    for (int i = 0; i < numProcesses; i++) {
        if (!finished[i]) {
            isSafe = false;
            cout << "No safe sequence exists." << endl;
            return;
        }
    }

    // Print the safe sequence
    if (isSafe) {
        cout << "Safe sequence exists: ";
        for (int i = 0; i < numProcesses - 1; i++) {
            cout << "P" << safeSequence[i] << " -> ";
        }
        cout << "P" << safeSequence[numProcesses - 1] << endl;
    }
}

int main() {
    int numProcesses = 5;
    int numResources = 4;

    // Case 1: Safe Sequence
    int maxDemand1[5][4] = {{0, 2, 1, 0}, {1, 6, 5, 2}, {2, 3, 6, 6}, {0, 6, 5, 2}, {0, 6, 5, 6}};
    int allocated1[5][4] = {{0, 1, 1, 0}, {1, 2, 3, 1}, {1, 3, 6, 5}, {0, 6, 3, 2}, {0, 0, 1, 4}};
    int available1[4] = {1, 5, 2, 0};

    cout << "Case 1 (Safe Sequence):" << endl;
    runBankersAlgorithm(numProcesses, numResources, maxDemand1, allocated1, available1);

    // Case 2: Not Safe Sequence
    int maxDemand2[5][4] = {{0, 2, 1, 0}, {1, 6, 5, 2}, {2, 3, 6, 6}, {0, 6, 5, 2}, {0, 6, 5, 6}};
    int allocated2[5][4] = {{0, 1, 1, 0}, {1, 2, 3, 1}, {1, 3, 6, 5}, {0, 6, 3, 2}, {0, 6, 5, 6}};
    int available2[4] = {0, 0, 0, 0};

    cout << "\nCase 2 (Not Safe Sequence):" << endl;
    runBankersAlgorithm(numProcesses, numResources, maxDemand2, allocated2, available2);

    return 0;
}
