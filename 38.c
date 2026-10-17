//p1
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
int main(void)
{
    char buf[100];
    int n;
    mkfifo("fifoA", 0666);
    mkfifo("fifoB", 0666);
    int wfd = open("fifoA", O_WRONLY);      
    int rfd = open("fifoB", O_RDONLY);      
    printf("P1, enter message for P2: ");
    fflush(stdout);
    n = read(0, buf, sizeof(buf));
    write(wfd, buf, n);                     
    n = read(rfd, buf, sizeof(buf));        
    printf("Reply from P2: ");
    fflush(stdout);
    write(1, buf, n);
    close(wfd);
    close(rfd);
    return 0;
}
/*Output:
P1, enter message for P2: Hello, P2!
Reply from P2: Hello, P1!
*/




//p2
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
int main(void)
{
    char buf[100];
    int n;
    mkfifo("fifoA", 0666);
    mkfifo("fifoB", 0666);
    int rfd = open("fifoA", O_RDONLY);      /* I read  on fifoA (pairs with p1's write-open) */
    int wfd = open("fifoB", O_WRONLY);      /* I write on fifoB (pairs with p1's read-open)  */
    n = read(rfd, buf, sizeof(buf));        /* wait for P1's message */
    printf("Message from P1: ");
    fflush(stdout);
    write(1, buf, n);
    printf("P2, enter reply for P1: ");
    fflush(stdout);
    n = read(0, buf, sizeof(buf));
    write(wfd, buf, n);                     /* reply to P1 */
    close(rfd);
    close(wfd);
    return 0;
}
/*Output:
Message from P1: Hello, P2!
P2, enter reply for P1: Hello, P1!
*/