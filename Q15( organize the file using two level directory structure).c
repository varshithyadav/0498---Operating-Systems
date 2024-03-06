#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DIRECTORIES 10
#define MAX_FILES_PER_DIRECTORY 10
#define MAX_DIR_NAME_LENGTH 20
#define MAX_FILE_NAME_LENGTH 20
struct File {
    char filename[MAX_FILE_NAME_LENGTH];
};
struct Directory {
    char dirname[MAX_DIR_NAME_LENGTH];
    struct File files[MAX_FILES_PER_DIRECTORY];
    int fileCount;
};
struct TwoLevelDirectory {
    struct Directory directories[MAX_DIRECTORIES];
    int directoryCount;
};
void initializeTwoLevelDirectory(struct TwoLevelDirectory *twodir) {
    twodir->directoryCount = 0;
}
void displayDirectories(struct TwoLevelDirectory *twodir) {
    printf("\nDirectories in the main directory:\n");
    for (int i = 0; i < twodir->directoryCount; i++) {
        printf("%s\n", twodir->directories[i].dirname);
    }
}
void displayFiles(struct TwoLevelDirectory *twodir, const char *dirname) {
    int found = 0;
    for (int i = 0; i < twodir->directoryCount; i++) {
        if (strcmp(twodir->directories[i].dirname, dirname) == 0) {
            found = 1;
            printf("\nFiles in the directory '%s':\n", dirname);
            for (int j = 0; j < twodir->directories[i].fileCount; j++) {
                printf("%s\n", twodir->directories[i].files[j].filename);
            }
            break;
        }
    }
    if (!found) {
        printf("Directory '%s' not found.\n", dirname);
    }
}
void addDirectory(struct TwoLevelDirectory *twodir, const char *dirname) {
    if (twodir->directoryCount < MAX_DIRECTORIES) {
        strcpy(twodir->directories[twodir->directoryCount].dirname, dirname);
        twodir->directories[twodir->directoryCount].fileCount = 0;
        twodir->directoryCount++;
        printf("Directory '%s' added to the main directory.\n", dirname);
    } else {
        printf("Main directory is full. Cannot add more directories.\n");
    }
}
void addFile(struct TwoLevelDirectory *twodir, const char *dirname, const char *filename) {
    int found = 0;
    for (int i = 0; i < twodir->directoryCount; i++) {
        if (strcmp(twodir->directories[i].dirname, dirname) == 0) {
            found = 1;
            if (twodir->directories[i].fileCount < MAX_FILES_PER_DIRECTORY) {
                strcpy(twodir->directories[i].files[twodir->directories[i].fileCount].filename, filename);
                twodir->directories[i].fileCount++;
                printf("File '%s' added to the directory '%s'.\n", filename, dirname);
            } else {
                printf("Directory '%s' is full. Cannot add more files.\n", dirname);
            }
            break;
        }
    }
    if (!found) {
        printf("Directory '%s' not found. Cannot add file.\n", dirname);
    }
}
int main() {
    struct TwoLevelDirectory twoLevelDirectory;
    initializeTwoLevelDirectory(&twoLevelDirectory);
    int choice;
    char dirname[MAX_DIR_NAME_LENGTH];
    char filename[MAX_FILE_NAME_LENGTH];
    do {
        printf("\nTwo-Level Directory Operations:\n");
        printf("1. Display Directories\n");
        printf("2. Add Directory\n");
        printf("3. Display Files in Directory\n");
        printf("4. Add File to Directory\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                displayDirectories(&twoLevelDirectory);
                break;
            case 2:
                printf("Enter directory name to add: ");
                scanf("%s", dirname);
                addDirectory(&twoLevelDirectory, dirname);
                break;
            case 3:
                printf("Enter directory name to display files: ");
                scanf("%s", dirname);
                displayFiles(&twoLevelDirectory, dirname);
                break;
            case 4:
                printf("Enter directory name to add file: ");
                scanf("%s", dirname);
                printf("Enter filename to add: ");
                scanf("%s", filename);
                addFile(&twoLevelDirectory, dirname, filename);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);
    return 0;
}
