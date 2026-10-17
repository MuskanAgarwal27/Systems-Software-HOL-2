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
    key_t key = ftok(".", 'b');
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) { perror("semget"); return 1; }
    printf("Enter initial value for counting semaphore: ");
    scanf("%d", &arg.val);
    if (semctl(semid, 0, SETVAL, arg) == -1) { perror("semctl"); return 1; }
    printf("Counting semaphore created\n");
    printf("Key: 0x%x  Semaphore ID: %d  Value: %d\n", key, semid, semctl(semid, 0, GETVAL));
    return 0;
}
/*Output:
Enter initial value for counting semaphore: 3
Counting semaphore created
Key: 0x4001  Semaphore ID: 32769  Value: 3
*/