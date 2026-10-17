#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
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
    int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    arg.val = 2;
    semctl(semid, 0, SETVAL, arg);
    printf("2 resources available, 4 processes want them\n");
    fflush(stdout);
    for (int c = 1; c <= 4; c++) {
        if (fork() == 0) {
            printf("Process %d waiting for a resource\n", c);
            fflush(stdout);
            semop(semid, &p, 1);
            printf("Process %d GOT a resource (free left: %d)\n", c, semctl(semid, 0, GETVAL));
            fflush(stdout);
            sleep(2);
            printf("Process %d released its resource\n", c);
            fflush(stdout);
            semop(semid, &v, 1);
            _exit(0);
        }
    }
    for (int c = 0; c < 4; c++)
        wait(NULL);
    semctl(semid, 0, IPC_RMID);
    return 0;
}
/*Output:
2 resources available, 4 processes want them
Process 1 waiting for a resource
Process 2 waiting for a resource
Process 1 GOT a resource (free left: 1)
Process 3 waiting for a resource
Process 2 GOT a resource (free left: 0)
Process 4 waiting for a resource
Process 1 released its resource
Process 3 GOT a resource (free left: 0)
Process 2 released its resource
Process 4 GOT a resource (free left: 0)
Process 3 released its resource
Process 4 released its resource
*/