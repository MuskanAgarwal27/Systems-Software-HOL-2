#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main(void)
{
    key_t key = ftok(".", 'a');
    int msqid = msgget(key, 0);
    if (msqid == -1) { perror("msgget"); return 1; }
    if (msgctl(msqid, IPC_RMID, NULL) == -1) { perror("msgctl IPC_RMID"); return 1; }
    printf("Message queue %d removed. Check with: ipcs -q\n", msqid);
    return 0;
}
/*Output:
Message queue 32768 removed. Check with: ipcs -q
*/