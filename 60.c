#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
    signal(SIGINT, SIG_IGN);
    printf("SIGINT ignored for 10 seconds: Ctrl+C does nothing now\n");
    fflush(stdout);
    sleep(10);

    signal(SIGINT, SIG_DFL);
    printf("SIGINT reset to default: Ctrl+C will now terminate the program\n");
    fflush(stdout);
    sleep(10);

    printf("No Ctrl+C pressed, exiting normally\n");
    return 0;
}
/*Output:
SIGINT ignored for 10 seconds: Ctrl+C does nothing now
SIGINT reset to default: Ctrl+C will now terminate the program
No Ctrl+C pressed, exiting normally
*/