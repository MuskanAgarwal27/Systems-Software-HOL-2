//Using dup()
#include <stdio.h>
#include <unistd.h>
int main(void){
    int fd[2];
    pipe(fd);
    if(fork()==0){
        close(1);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);   
        execlp("ls","ls",NULL);
    }else{
        close(0);
        dup(fd[0]);
        close(fd[0]);
        close(fd[1]);
        execlp("wc","wc",NULL);
    }
    return 0;
}
/*Output:
  5  5  32
*/