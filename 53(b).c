#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
void handler(int sig)
{
    char msg[] = "ITIMER_VIRTUAL expired: SIGVTALRM received\n";
    write(1, msg, strlen(msg));
}
int main(void)
{
    struct itimerval timer;
    signal(SIGVTALRM, handler);
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("setitimer");
        return 1;
    }
    printf("ITIMER_VIRTUAL set: every 10 s 10 us. Press Ctrl+C to stop.\n");
    fflush(stdout);
    while (1)
        pause();
}
/*Output:
ITIMER_VIRTUAL set: every 10 s 10 us. Press Ctrl+C to stop
ITIMER_VIRTUAL expired: SIGVTALRM received
ITIMER_VIRTUAL expired: SIGVTALRM received
*/