#include <stdio.h>
#include <sys/stat.h>   /* mkfifo */
int main(void)
{
    /* mkfifo(path, permissions) — glibc turns this into mknod(path, S_IFIFO|mode, 0) */
    if (mkfifo("myfifo_e", 0666) == -1) {
        perror("mkfifo");
        return 1;
    }
    printf("FIFO 'myfifo_e' created with mkfifo() library function\n");
    return 0;
}
/*Output:
FIFO 'myfifo_e' created with mkfifo() library function
*/