#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
int main() {
    int sfd, cfd;
    struct sockaddr_un addr;
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/tmp/mysocket");
    bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
    listen(sfd, 1);
    printf("Server waiting for client...\n");
    cfd = accept(sfd, NULL, NULL);
    printf("Client connected.\n");
    int a, b;
    char op;
    read(cfd, &a, sizeof(a));
    read(cfd, &b, sizeof(b));
    read(cfd, &op, sizeof(op));
    printf("Received from client: %d %c %d\n", a, op, b);
    int res = 0;
    if (op == '+') res = a + b;
    else if (op == '-') res = a - b;
    else if (op == '*') res = a * b;
    else if (op == '/') res = b ? a / b : 0;
    printf("Result = %d\n", res);
    write(cfd, &res, sizeof(res));
    close(cfd);
    close(sfd);
    unlink("/tmp/mysocket");
    return 0;
}
