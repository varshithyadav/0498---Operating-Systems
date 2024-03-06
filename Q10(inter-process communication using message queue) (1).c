#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define MESSAGE_SIZE 128
struct Message {
    long mtype; 
	char mtext[MESSAGE_SIZE];
};

int main() {
    key_t key = 5678; 
    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }
     pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        struct Message message;
        message.mtype = 1; 
        printf("Child process sending message to the queue: Hello from the child!\n");
        strncpy(message.mtext, "Hello from the child!", MESSAGE_SIZE);
      if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    } else {
        sleep(2);
        struct Message receivedMessage;
        if (msgrcv(msgid, &receivedMessage, sizeof(receivedMessage.mtext), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("Parent process received message from the queue: %s\n", receivedMessage.mtext
