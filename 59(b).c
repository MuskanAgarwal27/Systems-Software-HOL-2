#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void handler(int sig)
{
    printf("\nCaught SIGINT (signal %d): Ctrl+C pressed\n", sig);
}
int main(void)
{
    signal(SIGINT, handler);
    printf("Press Ctrl+C...\n");
    pause();
    printf("Program continues after handling SIGINT\n");
    return 0;
}
/*Output:
Press Ctrl+C...
Caught SIGINT (signal 2): Ctrl+C pressed
Program continues after handling SIGINT
*/