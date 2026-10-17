#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
void handler(int sig)
{
    printf("sigaction caught SIGFPE (signal %d)\n", sig);
    exit(1);
}
int main(void)
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGFPE, &act, NULL);
    volatile int a = 10, b = 0;
    printf("Dividing by zero...\n");
    fflush(stdout);
    int c = a / b;
    printf("%d\n", c);
    return 0;
}
/*Output:
Dividing by zero...
sigaction caught SIGFPE (signal 8)
*/