#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main(int argc, char *argv[])
{
    struct sockaddr_in serv, cli;
    socklen_t len;
    char buf[100], reply[150];
    int port = (argc > 1) ? atoi(argv[1]) : 8080;
    signal(SIGCHLD, SIG_IGN);
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    int on = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(port);
    if (bind(sd, (struct sockaddr *)&serv, sizeof(serv)) == -1) { perror("bind"); return 1; }
    listen(sd, 5);
    printf("Concurrent server (fork) on port %d\n", port);
    fflush(stdout);
    while (1) {
        len = sizeof(cli);
        int nsd = accept(sd, (struct sockaddr *)&cli, &len);
        if (nsd == -1) continue;
        if (fork() == 0) {
            close(sd);
            int n = read(nsd, buf, sizeof(buf) - 1);
            buf[n > 0 ? n : 0] = '\0';
            printf("[child %d] client %s:%d says: %s", getpid(),
                   inet_ntoa(cli.sin_addr), ntohs(cli.sin_port), buf);
            fflush(stdout);
            snprintf(reply, sizeof(reply), "Served by child process %d\n", getpid());
            write(nsd, reply, strlen(reply));
            close(nsd);
            _exit(0);
        }
        close(nsd);
    }
}
/*Output:
Concurrent server (fork) on port 8080
[child 12345] client 127.0.0.1:54321 says: Hello, Server!
[child 12346] client 127.0.0.1:54322 says: Hi, Server!
*/