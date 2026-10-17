#include <stdio.h>
#include <sys/stat.h>   /* mknod, S_IFIFO */
int main(void)
{
    if (mknod("myfifo_d", S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        return 1;
    }
    printf("FIFO 'myfifo_d' created with mknod() system call\n");
    return 0;
}
/*Output:
FIFO 'myfifo_d' created with mknod() system call
*/