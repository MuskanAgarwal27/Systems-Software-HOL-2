#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main(void)
{
    struct msqid_ds info;
    int perm;
    key_t key = ftok(".", 'a');
    int msqid = msgget(key, 0);
    if (msqid == -1) { perror("msgget"); return 1; }
    if (msgctl(msqid, IPC_STAT, &info) == -1) { perror("msgctl IPC_STAT"); return 1; }
    printf("Current permissions: %o\n", info.msg_perm.mode & 0777);
    printf("Enter new permissions in octal (e.g. 644): ");
    scanf("%o", &perm);
    info.msg_perm.mode = perm;
    if (msgctl(msqid, IPC_SET, &info) == -1) { perror("msgctl IPC_SET"); return 1; }
    msgctl(msqid, IPC_STAT, &info);
    printf("New permissions    : %o\n", info.msg_perm.mode & 0777);
    return 0;
}
/*Output:
Current permissions: 666
Enter new permissions in octal (e.g. 644): 644
New permissions    : 644
*/
