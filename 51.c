#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main(int argc, char *argv[])
{
    struct sockaddr_in serv, cli;
    socklen_t len = sizeof(cli);
    char buf[100];
    int port = (argc > 1) ? atoi(argv[1]) : 8080;
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1) { perror("socket"); return 1; }
    int on = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(port);
    if (bind(sd, (struct sockaddr *)&serv, sizeof(serv)) == -1) { perror("bind"); return 1; }
    listen(sd, 5);
    printf("Server waiting on port %d...\n", port);
    int nsd = accept(sd, (struct sockaddr *)&cli, &len);
    if (nsd == -1) { perror("accept"); return 1; }
    printf("Client connected from %s:%d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
    int n = read(nsd, buf, sizeof(buf) - 1);
    buf[n > 0 ? n : 0] = '\0';
    printf("Client says: %s\n", buf);
    printf("Enter reply: ");
    fflush(stdout);
    fgets(buf, sizeof(buf), stdin);
    write(nsd, buf, strlen(buf));
    close(nsd);
    close(sd);
    return 0;
}
/*Output:
Server waiting on port 8080...
Client connected from 127.0.0.1:54321
Client says: Hello, Server!
Enter reply: Hi, Client!
Client disconnected.
*/