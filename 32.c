#include <unistd.h>
#include <sys/wait.h>
int main(void) {
    int fd[2];
    char buf[100];
    pipe(fd);
    if (fork() == 0) {                  // CHILD: reader
        close(fd[1]);                   // child doesn't write
        int n = read(fd[0], buf, sizeof(buf));
        write(1, "Child received: ", 16);
        write(1, buf, n);
        close(fd[0]);
    } else {                            // PARENT: writer
        close(fd[0]);                   // parent doesn't read
        write(fd[1], "Hello child!\n", 13);
        close(fd[1]);
        wait(NULL);                     // wait for child to finish
    }
    return 0;
}
/*Output:
Child received: Hello child!
*/