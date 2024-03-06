#include <stdio.h>
#include <stdbool.h>
#define MAX_PROCESSES 5
#define MAX_RESOURCES 3
int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
void initialize() {
    printf("Enter the number of available resources:\n");
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        scanf("%d", &available[i]);
    }
	    printf("Enter the maximum resources each process can claim:\n");
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        printf("For Process %d: ", i + 1);
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            scanf("%d", &maximum[i][j]);
        }
    }
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            allocation[i][j] = 0;
            need[i][j] = maximum[i][j];
        }
    }
}
void displayState() {
    printf("\nCurrent State:\n");
    printf("Available resources: ");
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        printf("%d ", available[i]);
    }
    printf("\nProcesses\tAllocation\tMaximum\t\tNeed\n");
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        printf("%d\t\t", i + 1);
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            printf("%d ", allocation[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            printf("%d ", maximum[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}
bool isSafeState(int process, int request[]) {
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        if (request[i] > need[process][i]) {
            return false;
        }
    }
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        if (request[i] > available[i]) {
            return false;
        }
    }
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }
    bool safe = true;
    int work[MAX_RESOURCES];
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        work[i] = available[i];
    }
    bool finish[MAX_PROCESSES] = {false};
    while (safe) {
        safe = false;
        for (int i = 0; i < MAX_PROCESSES; ++i) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < MAX_RESOURCES; ++j) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < MAX_RESOURCES; ++j) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safe = true;
                }
            }
        }
    }
    if (!safe) {
        for (int i = 0; i < MAX_RESOURCES; ++i) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    }
    return safe;
}
void requestResources(int process) {
    int request[MAX_RESOURCES];
    printf("Enter the resource request for Process %d:\n", process + 1);
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        scanf("%d", &request[i]);
    }
    if (isSafeState(process, request)) {
        printf("Resource request granted.\n");
    } else {
        printf("Resource request denied. Process %d must wait to avoid deadlock.\n", process + 1);
    }
}
int main() {
    int choice, process;
    initialize();
    do {
        displayState();
        printf("\n1. Request resources\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the process making the request: ");
                scanf("%d", &process);
                requestResources(process - 1);
                break;
            case 2:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 2);
    return 0;
}
