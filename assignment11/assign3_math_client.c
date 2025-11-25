#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main() {
    int fd;
    struct sockaddr_in serv;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(5050);
    connect(fd, (struct sockaddr*)&serv, sizeof(serv));
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
