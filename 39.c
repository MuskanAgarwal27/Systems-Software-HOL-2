#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/select.h>
int main(void)
{
    char buf[100];
    fd_set rfds;            
    struct timeval tv;      
    mkfifo("fifo39", 0666);
    int fd = open("fifo39", O_RDONLY | O_NONBLOCK);
    if (fd == -1) { perror("open"); return 1; }
    FD_ZERO(&rfds);         
    FD_SET(fd, &rfds);      
    tv.tv_sec  = 10;        
    tv.tv_usec = 0;
    printf("Waiting up to 10 seconds for data in fifo39...\n");
    int ret = select(fd + 1, &rfds, NULL, NULL, &tv);  
    if (ret == -1)
        perror("select");
    else if (ret == 0)
        printf("No data within 10 seconds (timeout)\n");
    else if (FD_ISSET(fd, &rfds)) {
        int n = read(fd, buf, sizeof(buf));
        printf("Data received within 10 seconds: ");
        fflush(stdout);
        write(1, buf, n);
    }
 
    close(fd);
    return 0;
}
/*Output:
Waiting up to 10 seconds for data in fifo39...
Data received within 10 seconds: Hello, FIFO!
*/