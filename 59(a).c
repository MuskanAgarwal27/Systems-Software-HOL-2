#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void handler(int sig)
{
    printf("Caught SIGSEGV (signal %d): invalid memory access\n", sig);
    exit(1);
}
int main(void)
{
    signal(SIGSEGV, handler);
    int *p = NULL;
    printf("Writing through a NULL pointer...\n");
    fflush(stdout);
    *p = 10;
    return 0;
}
/*Output:
Writing through a NULL pointer...
Caught SIGSEGV (signal 11): invalid memory access
*/