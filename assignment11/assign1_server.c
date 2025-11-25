#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define MSG_KEY 0x1234
struct msgbuf {
    long mtype;
    char fifoname[64];
    char filename[64];
};
int main() {
    int msgid = msgget(MSG_KEY, IPC_CREAT | 0600);
    struct msgbuf msg;
    msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 1, 0);
    int fsrc = open(msg.filename, O_RDONLY);
    int ffifo = open(msg.fifoname, O_WRONLY);
    char buf[256];
    int n;
    while ((n = read(fsrc, buf, sizeof(buf))) > 0)
        write(ffifo, buf, n);
    close(fsrc);
    close(ffifo);
    msgctl(msgid, IPC_RMID, NULL);
    unlink(msg.fifoname);
    return 0;
}
