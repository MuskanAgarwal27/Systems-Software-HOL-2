#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
void handler(int sig)
{
    printf("Caught SIGALRM (signal %d) from ITIMER_REAL\n", sig);
}
int main(void)
{
    struct itimerval t = {0};
    signal(SIGALRM, handler);
    t.it_value.tv_sec = 2;
    setitimer(ITIMER_REAL, &t, NULL);
    printf("ITIMER_REAL set for 2 seconds, waiting...\n");
    fflush(stdout);
    pause();
    return 0;
}
/*Output:
ITIMER_REAL set for 2 seconds, waiting...
Caught SIGALRM (signal 14) from ITIMER_REAL
*/