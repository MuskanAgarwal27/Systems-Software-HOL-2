#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void handler(int sig)
{
    printf("Caught SIGFPE (signal %d): arithmetic error\n", sig);
    exit(1);
}
int main(void)
{
    signal(SIGFPE, handler);
    volatile int a = 10, b = 0;
    printf("Dividing by zero...\n");
    fflush(stdout);
    int c = a / b;
    printf("%d\n", c);
    return 0;
}
/*Output:
Dividing by zero...
Caught SIGFPE (signal 8): arithmetic error
*/