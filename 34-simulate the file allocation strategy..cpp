#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100

struct Record {
    int recordNumber;
    char data[50];
};

void initializeRecords(struct Record records[], int n) {
    for (int i = 0; i < n; i++) {
        records[i].recordNumber = i + 1;
        sprintf(records[i].data, "Data for record %d", i + 1);
    }
}

void printRecords(struct Record records[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Record %d: %s\n", records[i].recordNumber, records[i].data);
    }
}

int main() {
    struct Record records[MAX_RECORDS];
    int totalRecords;

    printf("Enter the total number of records: ");
    scanf("%d", &totalRecords);

    if (totalRecords > MAX_RECORDS || totalRecords <= 0) {
        printf("Invalid number of records.\n");
        return 1;
    }

    initializeRecords(records, totalRecords);

    printf("Records in the file:\n");
    printRecords(records, totalRecords);

    return 0;
}

