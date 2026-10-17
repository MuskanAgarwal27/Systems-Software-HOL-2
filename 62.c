#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
int main(void)
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    sigemptyset(&act.sa_mask);
    act.sa_handler = SIG_IGN;
    sigaction(SIGINT, &act, NULL);
    printf("SIGINT ignored for 10 seconds: Ctrl+C does nothing now\n");
    fflush(stdout);
    sleep(10);
    act.sa_handler = SIG_DFL;
    sigaction(SIGINT, &act, NULL);
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