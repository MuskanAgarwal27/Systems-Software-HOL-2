#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
volatile sig_atomic_t done = 0;
void handler(int sig)
{
    printf("Caught SIGPROF (signal %d) from ITIMER_PROF\n", sig);
    done = 1;
}
int main(void)
{
    struct itimerval t = {0};
    signal(SIGPROF, handler);
    t.it_value.tv_sec = 2;
    setitimer(ITIMER_PROF, &t, NULL);
    printf("ITIMER_PROF set for 2 s of user+system CPU time, looping...\n");
    fflush(stdout);
    while (!done)
        getppid();
    return 0;
}
/*Output:
ITIMER_PROF set for 2 s of user+system CPU time, looping...
Caught SIGPROF (signal 2) from ITIMER_PROF
*/
