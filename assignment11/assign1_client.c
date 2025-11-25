#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
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
    msg.mtype = 1;
    strcpy(msg.fifoname, "/tmp/myfifo");
    printf("Enter filename to send: ");
    scanf("%s", msg.filename);
    mkfifo(msg.fifoname, 0666);
    msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0);
    int ffifo = open(msg.fifoname, O_RDONLY);
    char outname[80];
    sprintf(outname, "received_%s", msg.filename);
    int fout = open(outname, O_CREAT | O_TRUNC | O_WRONLY, 0666);
    char buf[256];
    int n;
    while ((n = read(ffifo, buf, sizeof(buf))) > 0)
        write(fout, buf, n);
    close(ffifo);
    close(fout);
    return 0;
}
