#include <stdio.h>
#include <unistd.h>
int main(void)
{
    printf("a. Max length of arguments to exec : %ld bytes\n", sysconf(_SC_ARG_MAX));
    printf("b. Max processes per user ID       : %ld\n", sysconf(_SC_CHILD_MAX));
    printf("c. Clock ticks (jiffies) per second: %ld\n", sysconf(_SC_CLK_TCK));
    printf("d. Max open files                  : %ld\n", sysconf(_SC_OPEN_MAX));
    printf("e. Page size                       : %ld bytes\n", sysconf(_SC_PAGESIZE));
    printf("f. Total pages in physical memory  : %ld\n", sysconf(_SC_PHYS_PAGES));
    printf("g. Available pages in memory       : %ld\n", sysconf(_SC_AVPHYS_PAGES));
    return 0;
}
/*Output:
a. Max length of arguments to exec : 2097152 bytes
b. Max processes per user ID       : 31043
c. Clock ticks (jiffies) per second: 100
d. Max open files                  : 10240
e. Page size                       : 4096 bytes
f. Total pages in physical memory  : 1989543
g. Available pages in memory       : 1679448
*/