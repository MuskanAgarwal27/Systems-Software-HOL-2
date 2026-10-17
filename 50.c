#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void lock(int semid, int n)
{
    struct sembuf op = {n, -1, 0};
    semop(semid, &op, 1);
}

int main(void)
{
    union semun arg;
    int semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);
    semctl(semid, 1, SETVAL, arg);
    printf("Semaphore set ID: %d (two binary semaphores: R0 and R1)\n", semid);
    fflush(stdout);

    if (fork() == 0) {
        lock(semid, 1);
        printf("Child : locked R1, now waiting for R0...\n");
        fflush(stdout);
        sleep(1);
        lock(semid, 0);
        printf("Child : got R0 (never printed)\n");
        _exit(0);
    }

    lock(semid, 0);
    printf("Parent: locked R0, now waiting for R1...\n");
    fflush(stdout);
    sleep(1);
    lock(semid, 1);
    printf("Parent: got R1 (never printed)\n");
    return 0;
}
/*Output:
Semaphore set ID: 32771 (two binary semaphores: R0 and R1)
Parent: locked R0, now waiting for R1...
Child : locked R1, now waiting for R0...
Child : got R0 (never printed)
Parent: got R1 (never printed)
*/