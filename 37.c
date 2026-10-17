//writer
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
int main(void)
{
    char buf[100];
    mkfifo("fifo37", 0666);                 
    int fd = open("fifo37", O_WRONLY);      
    if (fd == -1) { perror("open"); return 1; }
    printf("Enter message: ");
    fflush(stdout);
    int n = read(0, buf, sizeof(buf));      
    write(fd, buf, n);                      
    close(fd);                              
    return 0;
}
/*Output:
Enter message: Hello, FIFO!
*/




//reader
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
int main(void)
{
    char buf[100];
    mkfifo("fifo37", 0666);                 
    int fd = open("fifo37", O_RDONLY);      
    if (fd == -1) { perror("open"); return 1; }
    int n = read(fd, buf, sizeof(buf));     
    printf("Received: ");
    fflush(stdout);
    write(1, buf, n);                      
    close(fd);
    return 0;
}
/*Output:
Received: Hello, FIFO!
*/