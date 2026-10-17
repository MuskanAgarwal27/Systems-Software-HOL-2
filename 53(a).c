#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
void handler(int sig)
{
    char msg[] = "ITIMER_REAL expired: SIGALRM received\n";
    write(1, msg, strlen(msg));
}
int main(void)
{
    struct itimerval timer;
    signal(SIGALRM, handler);
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        return 1;
    }
    printf("ITIMER_REAL set: every 10 s 10 us. Press Ctrl+C to stop.\n");
    fflush(stdout);
    while (1)
        pause();
}
/*Output:
ITIMER_REAL set: every 10 s 10 us. Press Ctrl+C to stop.
ITIMER_REAL expired: SIGALRM received
ITIMER_REAL expired: SIGALRM received
ITIMER_REAL expired: SIGALRM received
*/