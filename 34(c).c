#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main() {
    int fd[2];
    pipe(fd);
    if (fork() == 0) {
        close(fd[0]);
        close(1);
        fcntl(fd[1], F_DUPFD, 1);
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        exit(1);
    } else {
        close(fd[1]);
        close(0);
        fcntl(fd[0], F_DUPFD, 0);
        close(fd[0]);

        execlp("wc", "wc", NULL);
        exit(1);
    }
    return 0;
}
/*Output:
  6  49  367
*/