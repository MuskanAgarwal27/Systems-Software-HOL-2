#include <stdio.h>
#include <unistd.h>
#include <signal.h>
int main(void)
{
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child : PID %d, parent PID %d\n", getpid(), getppid());
        fflush(stdout);
        sleep(1);
        printf("Child : sending SIGKILL to parent %d\n", getppid());
        fflush(stdout);
        kill(getppid(), SIGKILL);
        sleep(1);
        printf("Child : I am now an orphan, new parent PID %d\n", getppid());
        return 0;
    }
    printf("Parent: PID %d, created child %d, now waiting...\n", getpid(), pid);
    fflush(stdout);
    while (1)
        sleep(1);
}
/*Output:
Parent: PID 2322, created child 2323, now waiting...
Child : PID 2323, parent PID 2322
Child : sending SIGKILL to parent 2322
Killed                     ./s
muskan_agarwal@LAPTOP-ERH9CV2Q:~/prac$ Child : I am now an orphan, new parent PID 500
*/