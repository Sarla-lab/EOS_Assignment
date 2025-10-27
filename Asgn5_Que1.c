#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MSG_KEY 1234

// Define message structure
struct msgbuf {
    long mtype;
    int num1;
    int num2;
    int result;
};

int main() {
    int msgid;
    pid_t pid;
    struct msgbuf msg;

    // Create message queue
    msgid = msgget(MSG_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    else if (pid == 0) {
        // ---------- CHILD PROCESS ----------
        msg.mtype = 1;  // message type for parent
        msg.num1 = 10;
        msg.num2 = 20;

        printf("Child: Sending numbers %d and %d to parent...\n", msg.num1, msg.num2);

        // Send message to parent
        if (msgsnd(msgid, &msg, sizeof(struct msgbuf) - sizeof(long), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        // Wait for sum from parent
        if (msgrcv(msgid, &msg, sizeof(struct msgbuf) - sizeof(long), 2, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("Child: Received sum = %d\n", msg.result);
        exit(0);
    }
    else {
        // ---------- PARENT PROCESS ----------
        // Receive message from child
        if (msgrcv(msgid, &msg, sizeof(struct msgbuf) - sizeof(long), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("Parent: Received numbers %d and %d\n", msg.num1, msg.num2);

        // Calculate sum
        msg.result = msg.num1 + msg.num2;
        msg.mtype = 2; // message type for child

        // Send result back to child
        if (msgsnd(msgid, &msg, sizeof(struct msgbuf) - sizeof(long), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        // Wait for child completion
        wait(NULL);

        // Remove message queue
        msgctl(msgid, IPC_RMID, NULL);

        printf("Parent: Child completed. Message queue removed.\n");
    }

    return 0;
}

