#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <pid>\n", argv[0]);
        return 1;
    }
    pid_t pid = atoi(argv[1]);
    if (kill(pid, SIGSTOP) == -1) {
        perror("kill");
        return 1;
    }
    printf("Sent SIGSTOP to %d. It is now stopped (state T in ps).\n", pid);
    printf("Press Enter to send SIGCONT and resume it...");
    getchar();
    kill(pid, SIGCONT);
    printf("Sent SIGCONT to %d\n", pid);
    return 0;
}
/*Output: 
Sent SIGSTOP to <pid>. It is now stopped (state T in ps).
Press Enter to send SIGCONT and resume it...
Sent SIGCONT to <pid>
*/