#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void scan(int requests[], int numRequests, int head, int direction, int totalTracks) {
    int totalDistance = 0;
    int currentTrack = head;
    int nextTrack;

    if (direction == 0) {
        printf("Sequence of service:\n");
        printf("%d -> ", head);
        for (int track = head + 1; track < totalTracks; track++) {
            nextTrack = -1;
            for (int i = 0; i < numRequests; i++) {
                if (requests[i] == track) {
                    nextTrack = track;
                    break;
                }
            }
            if (nextTrack != -1) {
                printf("%d -> ", nextTrack);
                totalDistance += abs(currentTrack - nextTrack);
                currentTrack = nextTrack;
            }
        }
        printf("End\n");
    } else {
        printf("Sequence of service:\n");
        printf("%d -> ", head);
        for (int track = head - 1; track >= 0; track--) {
            nextTrack = -1;
            for (int i = 0; i < numRequests; i++) {
                if (requests[i] == track) {
                    nextTrack = track;
                    break;
                }
            }
            if (nextTrack != -1) {
                printf("%d -> ", nextTrack);
                totalDistance += abs(currentTrack - nextTrack);
                currentTrack = nextTrack;
            }
        }
        printf("0 -> ");
        totalDistance += currentTrack;
        currentTrack = 0;
        for (int track = 1; track < totalTracks; track++) {
            nextTrack = -1;
            for (int i = 0; i < numRequests; i++) {
                if (requests[i] == track) {
                    nextTrack = track;
                    break;
                }
            }
            if (nextTrack != -1) {
                printf("%d -> ", nextTrack);
                totalDistance += abs(currentTrack - nextTrack);
                currentTrack = nextTrack;
            }
        }
        printf("End\n");
    }

    printf("Total head movement: %d\n", totalDistance);
}

int main() {
    int requests[MAX_REQUESTS];
    int numRequests, head, direction, totalTracks;

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

    printf("Enter the direction (0 for towards higher track numbers, 1 for towards lower track numbers): ");
    scanf("%d", &direction);

    if (direction != 0 && direction != 1) {
        printf("Invalid direction.\n");
        return 1;
    }

    scan(requests, numRequests, head, direction, totalTracks);

    return 0;
}

