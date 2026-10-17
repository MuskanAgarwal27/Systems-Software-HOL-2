#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct msgbuf {
    long mtype;
    char mtext[100];
};
int main(void)
{
    struct msgbuf m;
    key_t key = ftok(".", 'a');
    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) { perror("msgget"); return 1; }
    while (1) {
        printf("Enter message type (0 to stop): ");
        scanf("%ld", &m.mtype);
        if (m.mtype <= 0)
            break;
        printf("Enter message text: ");
        scanf(" %[^\n]", m.mtext);
        if (msgsnd(msqid, &m, strlen(m.mtext) + 1, 0) == -1)
            perror("msgsnd");
        else
            printf("Message sent\n");
    }
    printf("Check with: ipcs -q\n");
    return 0;
}
/*Output:
Enter message type (0 to stop): 1
Enter message text: Hello, message queue!
Message sent
Enter message type (0 to stop): 2
Enter message text: Another message
Message sent
Enter message type (0 to stop): 0
Check with: ipcs -q
*/