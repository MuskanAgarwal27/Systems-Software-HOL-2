#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void handler(int sig)
{
    printf("Caught SIGSTOP (signal %d)\n", sig);
}
int main(void)
{
    if (signal(SIGSTOP, handler) == SIG_ERR)
        perror("signal(SIGSTOP)");
    printf("My PID is %d. Run: ./64b_send_sigstop %d\n", getpid(), getpid());
    fflush(stdout);
    for (int i = 1; ; i++) {
        printf("Running... %d\n", i);
        fflush(stdout);
        sleep(1);
    }
}
/*Output: 
My PID is 133. Run: ./64b_send_sigstop 133
Running... 1
Running... 2
Running... 3
Caught SIGSTOP (signal 19)
Running... 4
Running... 5
Running... 6
Running... 7
Running... 8
Running... 9
Running... 10
Running... 11
Running... 12
*/