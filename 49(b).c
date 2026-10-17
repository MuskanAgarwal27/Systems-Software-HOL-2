#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
int main(void)
{
    union semun arg;
    struct sembuf p = {0, -1, SEM_UNDO};
    struct sembuf v = {0,  1, SEM_UNDO};
    int i;
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);
    int *count = shmat(shmid, NULL, 0);
    *count = 0;
    for (int c = 0; c < 2; c++) {
        if (fork() == 0) {
            for (i = 0; i < 10000; i++) {
                semop(semid, &p, 1);
                (*count)++;
                semop(semid, &v, 1);
            }
            shmdt(count);
            _exit(0);
        }
    }
    wait(NULL);
    wait(NULL);
    printf("Two processes each added 10000 to shared memory\n");
    printf("Final value: %d (expected 20000)\n", *count);
    shmdt(count);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    return 0;
}
/*Output:
Two processes each added 10000 to shared memory
Final value: 20000 (expected 20000)
*/