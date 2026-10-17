#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
int main(void)
{
    union semun arg;
    key_t key = ftok(".", 'a');
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) { perror("semget"); return 1; }
    arg.val = 1;
    if (semctl(semid, 0, SETVAL, arg) == -1) { perror("semctl"); return 1; }
    printf("Binary semaphore created\n");
    printf("Key: 0x%x  Semaphore ID: %d  Value: %d\n", key, semid, semctl(semid, 0, GETVAL));
    return 0;
}
/*Output:
Binary semaphore created
Key: 0x4000  Semaphore ID: 32768  Value: 1
*/