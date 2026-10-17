#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);
    if (fork() == 0) {
        // First command: ls -l
        close(p1[0]);
        close(p2[0]);
        close(p2[1]);
        dup2(p1[1], 1);
        close(p1[1]);
        execlp("ls", "ls", "-l", NULL);
        exit(1);
    }
    if (fork() == 0) {
        // Second command: grep ^d
        close(p1[1]);
        close(p2[0]);
        dup2(p1[0], 0);
        dup2(p2[1], 1);
        close(p1[0]);
        close(p2[1]);
        execlp("grep", "grep", "^d", NULL);
        exit(1);
    }
    // Third command: wc -l
    close(p1[0]);
    close(p1[1]);
    close(p2[1]);
    dup2(p2[0], 0);
    close(p2[0]);
    execlp("wc", "wc", "-l", NULL);
    exit(1);

    return 0;
}
/*Output:
  0
*/