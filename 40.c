#define _GNU_SOURCE 
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(void)
{
    int fd[2];
    long maxfiles = sysconf(_SC_OPEN_MAX);
    printf("Max files a process can open : %ld\n", maxfiles);
    pipe(fd);                                   
    long pipebuf = fpathconf(fd[0], _PC_PIPE_BUF);
    printf("Pipe size (PIPE_BUF)         : %ld bytes\n", pipebuf);
    int capacity = fcntl(fd[0], F_GETPIPE_SZ);
    printf("Pipe total capacity          : %d bytes\n", capacity); 
    close(fd[0]);
    close(fd[1]);
    return 0;
}
/*Output:
Max files a process can open : 1024
Pipe size (PIPE_BUF)         : 4096 bytes
Pipe total capacity          : 65536 bytes
*/