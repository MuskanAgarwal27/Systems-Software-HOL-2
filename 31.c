#include <unistd.h>
int main(void) {
    int fd[2];
    char buf[100];
    char msg[] = "Hello through the pipe!\n";
    if (pipe(fd) == -1) {
        write(2, "pipe failed\n", 12);
        return 1;
    }
    write(fd[1], msg, sizeof(msg) - 1);     // put data INTO the pipe
    int n = read(fd[0], buf, sizeof(buf));  // take data OUT of the pipe
    write(1, buf, n);                       // show it on the monitor
    close(fd[0]);
    close(fd[1]);
    return 0;
}
/*Output:
Hello through the pipe!
*/