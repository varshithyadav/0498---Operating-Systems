#include <stdio.h>
#define MEMORY_SIZE 1000
struct MemoryBlock {
    int start;
    int size;
    int processId;
};
void initializeMemory(struct MemoryBlock memory[], int size);
void displayMemory(struct MemoryBlock memory[], int size);
void allocateMemory(struct MemoryBlock memory[], int size, int processId, int requestSize);
void deallocateMemory(struct MemoryBlock memory[], int size, int processId);
int main() {
    int numBlocks;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &numBlocks);
    struct MemoryBlock memory[MEMORY_SIZE];
    initializeMemory(memory, numBlocks);
    displayMemory(memory, numBlocks);
    allocateMemory(memory, numBlocks, 1, 200);
    displayMemory(memory, numBlocks);
    allocateMemory(memory, numBlocks, 2, 100);
    displayMemory(memory, numBlocks);
    deallocateMemory(memory, numBlocks, 1);
    displayMemory(memory, numBlocks);
    allocateMemory(memory, numBlocks, 3, 150);
    displayMemory(memory, numBlocks);
    return 0;
}
void initializeMemory(struct MemoryBlock memory[], int size) {
    for (int i = 0; i < size; ++i) {
        memory[i].start = i * 100;
        memory[i].size = rand() % 200 + 50; 
		        memory[i].processId = -1;
				    }
}
void displayMemory(struct MemoryBlock memory[], int size) {
    printf("\nMemory State:\n");
    printf("-----------------------------------------------------\n");
    printf("| Block |   Start   |   Size   | Process ID | Status |\n");
    printf("-----------------------------------------------------\n");

    for (int i = 0; i < size; ++i) {
        printf("|   %2d   |   %4d   |   %4d   |     %3d     |", i + 1, memory[i].start, memory[i].size, memory[i].processId);
        if (memory[i].processId == -1) {
            printf("   Free   |\n");
        } else {
            printf(" Allocated |\n");
        }
    }
    printf("-----------------------------------------------------\n");
}
void allocateMemory(struct MemoryBlock memory[], int size, int processId, int requestSize) {
    for (int i = 0; i < size; ++i) {
        if (memory[i].processId == -1 && memory[i].size >= requestSize) {
            memory[i].processId = processId;
            printf("Process %d allocated to Block %d\n", processId, i + 1);
            break;
        }
    }
}
void deallocateMemory(struct MemoryBlock memory[], int size, int processId) {
    for (int i = 0; i < size; ++i) {
        if (memory[i].processId == processId) {
            memory[i].processId = -1;
            printf("Process %d deallocated from Block %d\n", processId, i + 1);
            break;
        }
    }
}
