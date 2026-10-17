#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int main(void)
{
    char ids[] = {'a', 'b', 't'};
    for (int i = 0; i < 3; i++) {
        key_t key = ftok(".", ids[i]);
        int semid = semget(key, 1, 0);
        if (semid == -1) {
            printf("No semaphore for key '%c'\n", ids[i]);
            continue;
        }
        if (semctl(semid, 0, IPC_RMID) == -1)
            perror("semctl");
        else
            printf("Removed semaphore %d (key '%c')\n", semid, ids[i]);
    }
    printf("Check with: ipcs -s\n");
    return 0;
}
/*Output:
No semaphore for key 'a'
No semaphore for key 'b'
Removed semaphore 32770 (key 't')
Check with: ipcs -s
*/