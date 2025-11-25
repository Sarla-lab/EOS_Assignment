#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main() {
    int fd;
    char buf[256];
    struct sockaddr_in serv;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(5050);
    connect(fd, (struct sockaddr*)&serv, sizeof(serv));
    while (1) {
        printf("Client> ");
        fgets(buf, sizeof(buf), stdin);
        write(fd, buf, strlen(buf));
        if (strcmp(buf, "bye\n") == 0) break;
        memset(buf, 0, sizeof(buf));
        read(fd, buf, sizeof(buf));
        printf("Server: %s", buf);
        if (strcmp(buf, "bye\n") == 0) break;
    }
    close(fd);
    return 0;
}
