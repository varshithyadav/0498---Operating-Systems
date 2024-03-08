#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

struct Block {
    int blockNumber;
    char data[50];
};

struct IndexBlock {
    struct Block *blocks[MAX_BLOCKS];
    int numBlocks;
};

void initializeBlocks(struct Block blocks[], int n) {
    for (int i = 0; i < n; i++) {
        blocks[i].blockNumber = i + 1;
        sprintf(blocks[i].data, "Data for block %d", i + 1);
    }
}

void initializeIndexBlock(struct IndexBlock *indexBlock) {
    indexBlock->numBlocks = 0;
}

void addBlockToIndexBlock(struct IndexBlock *indexBlock, struct Block *block) {
    if (indexBlock->numBlocks < MAX_BLOCKS) {
        indexBlock->blocks[indexBlock->numBlocks++] = block;
    } else {
        printf("Index block is full.\n");
    }
}

void printBlocks(struct Block blocks[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Block %d: %s\n", blocks[i].blockNumber, blocks[i].data);
    }
}

int main() {
    struct Block blocks[MAX_BLOCKS];
    struct IndexBlock indexBlock;
    int totalBlocks;

    printf("Enter the total number of blocks: ");
    scanf("%d", &totalBlocks);

    if (totalBlocks > MAX_BLOCKS || totalBlocks <= 0) {
        printf("Invalid number of blocks.\n");
        return 1;
    }

    initializeBlocks(blocks, totalBlocks);
    initializeIndexBlock(&indexBlock);

    printf("Blocks in the file:\n");
    printBlocks(blocks, totalBlocks);

    printf("\nAdding blocks to the index block...\n");
    for (int i = 0; i < totalBlocks; i++) {
        addBlockToIndexBlock(&indexBlock, &blocks[i]);
    }

    printf("\nIndex block:\n");
    for (int i = 0; i < indexBlock.numBlocks; i++) {
        printf("Block %d\n", indexBlock.blocks[i]->blockNumber);
    }

    return 0;
}

