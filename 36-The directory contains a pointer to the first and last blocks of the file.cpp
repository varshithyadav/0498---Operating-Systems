#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

struct Block {
    int blockNumber;
    char data[50];
    struct Block* nextBlock;
};

struct File {
    struct Block* firstBlock;
    struct Block* lastBlock;
    int numBlocks;
};

void initializeBlocks(struct Block blocks[], int n) {
    for (int i = 0; i < n; i++) {
        blocks[i].blockNumber = i + 1;
        sprintf(blocks[i].data, "Data for block %d", i + 1);
        blocks[i].nextBlock = NULL;
    }
}

void initializeFile(struct File* file) {
    file->firstBlock = NULL;
    file->lastBlock = NULL;
    file->numBlocks = 0;
}

void addBlockToFile(struct File* file, struct Block* block) {
    if (file->firstBlock == NULL) {
        file->firstBlock = block;
    } else {
        file->lastBlock->nextBlock = block;
    }
    file->lastBlock = block;
    file->numBlocks++;
}

void printFile(struct File* file) {
    printf("File blocks:\n");
    struct Block* currentBlock = file->firstBlock;
    while (currentBlock != NULL) {
        printf("Block %d: %s\n", currentBlock->blockNumber, currentBlock->data);
        currentBlock = currentBlock->nextBlock;
    }
}

int main() {
    struct Block blocks[MAX_BLOCKS];
    struct File file;
    int totalBlocks;

    printf("Enter the total number of blocks: ");
    scanf("%d", &totalBlocks);

    if (totalBlocks > MAX_BLOCKS || totalBlocks <= 0) {
        printf("Invalid number of blocks.\n");
        return 1;
    }

    initializeBlocks(blocks, totalBlocks);
    initializeFile(&file);

    printf("Blocks in the file:\n");
    for (int i = 0; i < totalBlocks; i++) {
        printf("Block %d\n", blocks[i].blockNumber);
    }

    printf("\nAdding blocks to the file...\n");
    for (int i = 0; i < totalBlocks; i++) {
        addBlockToFile(&file, &blocks[i]);
    }

    printf("\n");
    printFile(&file);

    return 0;
}

