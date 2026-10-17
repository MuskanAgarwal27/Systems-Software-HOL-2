#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
int main(void)
{
    key_t key = ftok(".", 'b');
    int shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid == -1) { perror("shmget"); return 1; }
    char *data = shmat(shmid, NULL, 0);
    if (data == (char *)-1) { perror("shmat"); return 1; }
    strcpy(data, "Hello from shared memory");
    printf("a. Written to shared memory: %s\n", data);
    fflush(stdout);
    if (fork() == 0) {
        char *ro = shmat(shmid, NULL, SHM_RDONLY);
        if (ro == (char *)-1) { perror("shmat"); _exit(1); }
        printf("b. Read-only attach reads  : %s\n", ro);
        printf("   Trying to overwrite...\n");
        fflush(stdout);
        strcpy(ro, "Overwritten");
        printf("   Overwrite succeeded\n");
        _exit(0);
    }
    int status;
    wait(&status);
    if (WIFSIGNALED(status))
        printf("   Overwrite FAILED: process killed by signal %d (SIGSEGV)\n", WTERMSIG(status));
    printf("   Data is still           : %s\n", data);
    if (shmdt(data) == -1) { perror("shmdt"); return 1; }
    printf("c. Shared memory detached\n");
    if (shmctl(shmid, IPC_RMID, NULL) == -1) { perror("shmctl"); return 1; }
    printf("d. Shared memory removed (check: ipcs -m)\n");
    return 0;
}
/*Output:
a. Written to shared memory: Hello from shared memory
b. Read-only attach reads  : Hello from shared memory
   Trying to overwrite...
   Overwrite FAILED: process killed by signal 11 (SIGSEGV)
   Data is still           : Hello from shared memory
c. Shared memory detached
d. Shared memory removed (check: ipcs -m)
*/