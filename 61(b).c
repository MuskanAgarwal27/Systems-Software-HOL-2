#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
void handler(int sig)
{
    printf("\nsigaction caught SIGINT (signal %d)\n", sig);
}
int main(void)
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    printf("Press Ctrl+C...\n");
    pause();
    printf("Program continues after handling SIGINT\n");
    return 0;
}
/*Output:
Press Ctrl+C...
sigaction caught SIGINT (signal 2)
Program continues after handling SIGINT
*/