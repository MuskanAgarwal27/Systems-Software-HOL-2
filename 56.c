#include <stdio.h>
#include <unistd.h>
unsigned long long rdtsc(void)
{
    unsigned int lo, hi;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long long)hi << 32) | lo;
}
int main(void)
{
    unsigned long long start, end;
    start = rdtsc();
    for (int i = 0; i < 100; i++)
        getppid();
    end = rdtsc();
    printf("Cycles for 100 getppid() calls : %llu\n", end - start);
    printf("Average cycles per call        : %llu\n", (end - start) / 100);
    return 0;
}
/*Output:
Cycles for 100 getppid() calls : 51710
Average cycles per call        : 517
*/