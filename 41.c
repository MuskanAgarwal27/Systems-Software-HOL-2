#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main(void)
{
    key_t key = ftok(".", 'a');
    if (key == -1) { perror("ftok"); return 1; }
    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) { perror("msgget"); return 1; }
    printf("Key         : %d (hex 0x%x)\n", key, key);
    printf("Message ID  : %d\n", msqid);
    return 0;
}
/*Output:
Key         : 1630580848 (hex 0x6130b070)
Message ID  : 0
*/