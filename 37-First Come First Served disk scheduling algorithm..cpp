#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void firstComeFirstServed(int requests[], int numRequests) {
    int head = 0;
    int totalDistance = 0;

    printf("Sequence of service:\n");
    for (int i = 0; i < numRequests; i++) {
        printf("%d -> ", requests[i]);
        totalDistance += abs(head - requests[i]);
        head = requests[i];
    }

    printf("End\n");
    printf("Total head movement: %d\n", totalDistance);
}

int main() {
    int requests[MAX_REQUESTS];
    int numRequests;

    printf("Enter the number of requests: ");
    scanf("%d", &numRequests);

    if (numRequests <= 0 || numRequests > MAX_REQUESTS) {
        printf("Invalid number of requests.\n");
        return 1;
    }

    printf("Enter the request sequence:\n");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    firstComeFirstServed(requests, numRequests);

    return 0;
}

