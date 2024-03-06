#include <stdio.h>
#include <stdlib.h>
#define MEMORY_SIZE 100
struct Block {
    int size;
    int allocated;
};
void initializeMemory(struct Block memory[], int size) {
    for (int i = 0; i < size; i++) {
        memory[i].size = 0;
        memory[i].allocated = 0;
    }
}
void displayMemory(struct Block memory[], int size) {
    printf("\nMemory Layout:\n");
    for (int i = 0; i < size; i++) {
        printf("[%d] ", memory[i].size);
        if (memory[i].allocated) {
            printf("(Allocated) ");
        } else {
            printf("(Free) ");
        }
    }
    printf("\n");
}
void firstFit(struct Block memory[], int size, int requestSize) {
    for (int i = 0; i < size; i++) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            memory[i].allocated = 1;
            printf("First Fit: Allocated %d units starting at block %d.\n", requestSize, i);
            return;
        }
    }
    printf("First Fit: Insufficient memory to allocate %d units.\n", requestSize);
}
void bestFit(struct Block memory[], int size, int requestSize) {
    int bestFitIndex = -1;
    int bestFitSize = MEMORY_SIZE + 1;
    for (int i = 0; i < size; i++) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            if (memory[i].size < bestFitSize) {
                bestFitSize = memory[i].size;
                bestFitIndex = i;
            }
        }
    }
    if (bestFitIndex != -1) {
        memory[bestFitIndex].allocated = 1;
        printf("Best Fit: Allocated %d units starting at block %d.\n", requestSize, bestFitIndex);
    } else {
        printf("Best Fit: Insufficient memory to allocate %d units.\n", requestSize);
    }
}
void worstFit(struct Block memory[], int size, int requestSize) {
    int worstFitIndex = -1;
    int worstFitSize = -1;

    for (int i = 0; i < size; i++) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            if (memory[i].size > worstFitSize) {
                worstFitSize = memory[i].size;
                worstFitIndex = i;
            }
        }
    }
    if (worstFitIndex != -1) {
        memory[worstFitIndex].allocated = 1;
        printf("Worst Fit: Allocated %d units starting at block %d.\n", requestSize, worstFitIndex);
    } else {
        printf("Worst Fit: Insufficient memory to allocate %d units.\n", requestSize);
    }
}
int main() {
    struct Block memory[MEMORY_SIZE];
    int choice, requestSize;
    initializeMemory(memory, MEMORY_SIZE);
    do {
        displayMemory(memory, MEMORY_SIZE);
        printf("\nMemory Allocation Strategies:\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter memory request size: ");
                scanf("%d", &requestSize);
                firstFit(memory, MEMORY_SIZE, requestSize);
                break;
            case 2:
                printf("Enter memory request size: ");
                scanf("%d", &requestSize);
                bestFit(memory, MEMORY_SIZE, requestSize);
                break;
            case 3:
                printf("Enter memory request size: ");
                scanf("%d", &requestSize);
                worstFit(memory, MEMORY_SIZE, requestSize);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);
    return 0;
}
