//Using dup2
#include<unistd.h>
int main(void){
    int fd[2];
    pipe(fd);
    if(fork()==0){
        close(1);
        dup2(fd[1],1);
        close(fd[0]);
        close(fd[1]);   
        execlp("ls","ls",NULL);
    }else{
        close(0);
        dup2(fd[0],0);
        close(fd[0]);
        close(fd[1]);
        execlp("wc","wc",NULL);
    }
    return 0;
}
/*Output:
  5  5  32
*/