#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
void show_time(const char *label, time_t t)
{
    if (t == 0)
        printf("%s: not yet\n", label);
    else
        printf("%s: %s", label, ctime(&t));
}
int main(void)
{
    key_t key = ftok(".", 'a');
    int msqid = msgget(key, IPC_CREAT | 0666);

    if (msqid == -1) {
        perror("msgget");
        return 1;
    }
    struct {
        long mtype;
        char mtext[20];
    } m = {1, "hello"};
    if (msgsnd(msqid, &m, strlen(m.mtext) + 1, 0) == -1) {
        perror("msgsnd");
        return 1;
    }
    struct msqid_ds info;
    if (msgctl(msqid, IPC_STAT, &info) == -1) {
        perror("msgctl");
        return 1;
    }
    printf("a. Access permission         : %o\n",
           info.msg_perm.mode & 0777);
    printf("b. UID / GID                 : %d / %d\n",
           info.msg_perm.uid, info.msg_perm.gid);
    show_time("c. Time of last msgsnd       ", info.msg_stime);
    show_time("   Time of last msgrcv       ", info.msg_rtime);
    show_time("d. Time of last change       ", info.msg_ctime);
    printf("e. Size of queue (bytes now) : %lu\n",
           (unsigned long)info.__msg_cbytes);
    printf("f. Number of messages        : %lu\n",
           (unsigned long)info.msg_qnum);
    printf("g. Max bytes allowed         : %lu\n",
           (unsigned long)info.msg_qbytes);
    printf("h. PID of last msgsnd        : %d\n",
           info.msg_lspid);
    printf("   PID of last msgrcv        : %d\n",
           info.msg_lrpid);
    return 0;
}

/*Output:
a. Access permission         : 666
b. UID / GID                 : 1000 / 1000
c. Time of last msgsnd       : Fri Oct 16 20:54:34 2026
   Time of last msgrcv       : not yet
d. Time of last change       : Fri Oct 16 20:52:03 2026
e. Size of queue (bytes now) : 6
f. Number of messages        : 1
g. Max bytes allowed         : 16384
h. PID of last msgsnd        : 1839
   PID of last msgrcv        : 0
*/