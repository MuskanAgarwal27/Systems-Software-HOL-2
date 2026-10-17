#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void handler(int sig)
{
    printf("Caught SIGALRM (signal %d) from alarm()\n", sig);
}
int main(void)
{
    signal(SIGALRM, handler);
    alarm(3);
    printf("Alarm set for 3 seconds, waiting...\n");
    fflush(stdout);
    pause();
    return 0;
}
/*Output:
Alarm set for 3 seconds, waiting...
Caught SIGALRM (signal 14) from alarm()
*/