#include <unistd.h>
#include <sys/wait.h>
int main(void) {
    int p2c[2], c2p[2];   // parent->child, child->parent
    char buf[100];
    int n;
    pipe(p2c);
    pipe(c2p);
    if (fork() == 0) {                         // CHILD
        close(p2c[1]);                         // child only reads p2c
        close(c2p[0]);                         // child only writes c2p
        n = read(p2c[0], buf, sizeof(buf));
        write(1, "Child got: ", 11);
        write(1, buf, n);
        write(c2p[1], "Hi parent!\n", 11);
        close(p2c[0]);
        close(c2p[1]);
    } else {                                   // PARENT
        close(p2c[0]);                         // parent only writes p2c
        close(c2p[1]);                         // parent only reads c2p
        write(p2c[1], "Hi child!\n", 10);
        n = read(c2p[0], buf, sizeof(buf));
        write(1, "Parent got: ", 12);
        write(1, buf, n);
        close(p2c[1]);
        close(c2p[0]);
        wait(NULL);
    }
    return 0;
}
/*Output:  
Child got: Hi child!
Parent got: Hi parent!
*/