#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
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
    struct sembuf p = {0, -1, SEM_UNDO};
    struct sembuf v = {0,  1, SEM_UNDO};
    int ticket = 0;
    key_t key = ftok(".", 't');
    int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid != -1) {
        arg.val = 1;
        semctl(semid, 0, SETVAL, arg);
    } else if (errno == EEXIST) {
        semid = semget(key, 1, 0);
    } else {
        perror("semget");
        return 1;
    }
    int fd = open("ticket.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1) { perror("open"); return 1; }
    printf("Waiting to enter critical section...\n");
    semop(semid, &p, 1);
    printf("Inside critical section\n");
    lseek(fd, 0, SEEK_SET);
    if (read(fd, &ticket, sizeof(ticket)) <= 0)
        ticket = 0;
    ticket++;
    lseek(fd, 0, SEEK_SET);
    write(fd, &ticket, sizeof(ticket));
    printf("Your ticket number: %d\n", ticket);
    printf("Press Enter to leave critical section...");
    getchar();
    semop(semid, &v, 1);
    printf("Left critical section\n");
    close(fd);
    return 0;
}
/*Output:
Waiting to enter critical section...
Inside critical section
Your ticket number: 1
Press Enter to leave critical section...
Left critical section
*/