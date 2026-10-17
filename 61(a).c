#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
void handler(int sig)
{
    printf("sigaction caught SIGSEGV (signal %d)\n", sig);
    exit(1);
}
int main(void)
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGSEGV, &act, NULL);
    int *p = NULL;
    printf("Writing through a NULL pointer...\n");
    fflush(stdout);
    *p = 10;
    return 0;
}
/*Output:
Writing through a NULL pointer...
sigaction caught SIGSEGV (signal 11)
*/  