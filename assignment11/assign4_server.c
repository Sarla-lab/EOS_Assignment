#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main() {
    int sfd, cfd;
    char buf[256];
    struct sockaddr_in serv, cli;
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("0.0.0.0");
    serv.sin_port = htons(5050);
    bind(sfd, (struct sockaddr*)&serv, sizeof(serv));
    listen(sfd, 1);
    socklen_t len = sizeof(cli);
    cfd = accept(sfd, (struct sockaddr*)&cli, &len);
    while (1) {
        memset(buf, 0, sizeof(buf));
        read(cfd, buf, sizeof(buf));
        if (strcmp(buf, "bye\n") == 0) break;
        printf("Client> %s", buf);
        printf("Server> ");
        fgets(buf, sizeof(buf), stdin);
        write(cfd, buf, strlen(buf));
        if (strcmp(buf, "bye\n") == 0) break;
    }
    close(cfd);
    close(sfd);
    return 0;
}
