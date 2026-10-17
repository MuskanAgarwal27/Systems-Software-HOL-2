#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
volatile sig_atomic_t done = 0;
void handler(int sig)
{
    printf("Caught SIGVTALRM (signal %d) from ITIMER_VIRTUAL\n", sig);
    done = 1;
}
int main(void)
{
    struct itimerval t = {0};
    signal(SIGVTALRM, handler);
    t.it_value.tv_sec = 2;
    setitimer(ITIMER_VIRTUAL, &t, NULL);
    printf("ITIMER_VIRTUAL set for 2 s of user CPU time, busy looping...\n");
    fflush(stdout);
    while (!done)
        getppid();  // Busy loop to consume user CPU time

    return 0;
}
/*Output:
ITIMER_VIRTUAL set for 2 s of user CPU time, busy looping...
Caught SIGVTALRM (signal 26) from ITIMER_VIRTUAL
*/