#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define FILE_PATH "example.txt"
int main() {
    int fileDescriptor = open(FILE_PATH, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fileDescriptor == -1) {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }
    const char *content = "Hello, UNIX System Calls!\n";
    ssize_t bytesWritten = write(fileDescriptor, content, strlen(content));

    if (bytesWritten == -1) {
        perror("Error writing to the file");
        close(fileDescriptor);
        exit(EXIT_FAILURE);
    }
    printf("Content written to the file successfully.\n");
    if (close(fileDescriptor) == -1) {
        perror("Error closing the file");
        exit(EXIT_FAILURE);
    }
    fileDescriptor = open(FILE_PATH, O_RDONLY);

    if (fileDescriptor == -1) {
        perror("Error opening the file for reading");
        exit(EXIT_FAILURE);
    }
    char buffer[100];
    ssize_t bytesRead = read(fileDescriptor, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        perror("Error reading from the file");
        close(fileDescriptor);
        exit(EXIT_FAILURE);
    }
    buffer[bytesRead] = '\0'; 
	    printf("Content read from the file:\n%s", buffer);
    if (close(fileDescriptor) == -1) {
        perror("Error closing the file");
        exit(EXIT_FAILURE);
    }
    if (remove(FILE_PATH) == -1) {
        perror("Error removing the file");
        exit(EXIT_FAILURE);
    }

    printf("File removed successfully.\n");

    return 0;
}
