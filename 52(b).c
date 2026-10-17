#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void *handle_client(void *arg)
{
    int nsd = *(int *)arg;
    char buf[100], reply[150];
    free(arg);
    int n = read(nsd, buf, sizeof(buf) - 1);
    buf[n > 0 ? n : 0] = '\0';
    printf("[thread %lu] client says: %s", pthread_self(), buf);
    fflush(stdout);
    snprintf(reply, sizeof(reply), "Served by thread %lu\n", pthread_self());
    write(nsd, reply, strlen(reply));
    close(nsd);
    return NULL;
}
int main(int argc, char *argv[])
{
    struct sockaddr_in serv;
    pthread_t tid;
    int port = (argc > 1) ? atoi(argv[1]) : 8080;
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    int on = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(port);
    if (bind(sd, (struct sockaddr *)&serv, sizeof(serv)) == -1) { perror("bind"); return 1; }
    listen(sd, 5);
    printf("Concurrent server (pthread) on port %d\n", port);
    fflush(stdout);
    while (1) {
        int *nsd = malloc(sizeof(int));
        *nsd = accept(sd, NULL, NULL);
        if (*nsd == -1) { free(nsd); continue; }
        pthread_create(&tid, NULL, handle_client, nsd);
        pthread_detach(tid);
    }
}
/*Output:
Concurrent server (pthread) on port 8080
[thread 140735123456768] client says: Hello, Server!
[thread 140735115064064] client says: Hi, Server!
*/  