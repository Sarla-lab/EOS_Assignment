#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sfd, cfd;
    struct sockaddr_in serv, cli;
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(5050);
    bind(sfd, (struct sockaddr*)&serv, sizeof(serv));
    listen(sfd, 1);
    printf("Server waiting for client...\n");
    socklen_t len = sizeof(cli);
    cfd = accept(sfd, (struct sockaddr*)&cli, &len);
    printf("Client connected.\n");
    int a, b, res;
    char op;
    read(cfd, &a, sizeof(a));
    read(cfd, &b, sizeof(b));
    read(cfd, &op, sizeof(op));
    printf("Received from client: %d %c %d\n", a, op, b);
    if (op == '+') res = a + b;
    else if (op == '-') res = a - b;
    else if (op == '*') res = a * b;
    else if (op == '/') res = b ? a / b : 0;
    printf("Result = %d\n", res);
    write(cfd, &res, sizeof(res));
    close(cfd);
    close(sfd);
    return 0;
}
