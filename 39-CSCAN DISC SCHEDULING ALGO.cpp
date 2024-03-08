#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void cScan(int requests[], int numRequests, int head, int totalTracks) {
    int totalDistance = 0;
    int currentTrack = head;

    printf("Sequence of service:\n");

    // Moving towards higher track numbers
    printf("%d -> ", head);
    for (int track = head + 1; track < totalTracks; track++) {
        for (int i = 0; i < numRequests; i++) {
            if (requests[i] == track) {
                printf("%d -> ", track);
                totalDistance += abs(currentTrack - track);
                currentTrack = track;
            }
        }
    }

    // Moving towards lower track numbers (to track 0)
    printf("0 -> ");
    totalDistance += currentTrack;
    currentTrack = 0;

    // Moving towards higher track numbers again
    for (int track = 1; track < head; track++) {
        for (int i = 0; i < numRequests; i++) {
            if (requests[i] == track) {
                printf("%d -> ", track);
                totalDistance += abs(currentTrack - track);
                currentTrack = track;
            }
        }
    }

    printf("End\n");
    printf("Total head movement: %d\n", totalDistance);
}

int main() {
    int requests[MAX_REQUESTS];
    int numRequests, head, totalTracks;

    printf("Enter the number of tracks: ");
    scanf("%d", &totalTracks);

    printf("Enter the number of requests: ");
    scanf("%d", &numRequests);

    if (numRequests <= 0 || numRequests > MAX_REQUESTS) {
        printf("Invalid number of requests.\n");
        return 1;
    }

    printf("Enter the request sequence:\n");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
        if (requests[i] < 0 || requests[i] >= totalTracks) {
            printf("Invalid track number.\n");
            return 1;
        }
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    cScan(requests, numRequests, head, totalTracks);

    return 0;
}

