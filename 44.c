#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct msgbuf {
    long mtype;
    char mtext[100];
};
int main(void)
{
    struct msgbuf m;
    long type;
    key_t key = ftok(".", 'a');
    int msqid = msgget(key, 0);
    if (msqid == -1) { perror("msgget"); return 1; }
    printf("Enter message type to receive (0 = first message): ");
    scanf("%ld", &type);
    printf("Waiting for a message (flag 0 blocks)...\n");
    int n = msgrcv(msqid, &m, sizeof(m.mtext), type, 0);
    if (n == -1) { perror("msgrcv"); return 1; }
    printf("Received type %ld, %d bytes: %s\n", m.mtype, n, m.mtext);
    return 0;
}
/*Output:
Enter message type to receive (0 = first message): 1
Waiting for a message (flag 0 blocks)...
Received type 1, 6 bytes: hello
*/
