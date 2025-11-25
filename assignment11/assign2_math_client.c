#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
int main() {
    int fd;
    struct sockaddr_un addr;
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/tmp/mysocket");
    connect(fd, (struct sockaddr*)&addr, sizeof(addr));
    int a, b, res;
    char op;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
    printf("Enter operation (+ - * /): ");
    scanf(" %c", &op);
    write(fd, &a, sizeof(a));
    write(fd, &b, sizeof(b));
    write(fd, &op, sizeof(op));
    read(fd, &res, sizeof(res));
    printf("Result = %d\n", res);
    close(fd);
    return 0;
}
