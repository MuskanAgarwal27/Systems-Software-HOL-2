#include <stdio.h>
#include <sys/resource.h>
int main(void)
{
    struct rlimit r;
    unsigned long long newsoft;
    getrlimit(RLIMIT_NOFILE, &r);
    printf("Max open files -> soft: %llu  hard: %llu\n",
           (unsigned long long)r.rlim_cur, (unsigned long long)r.rlim_max);
    printf("Enter new soft limit (must be <= hard limit): ");
    scanf("%llu", &newsoft);
    r.rlim_cur = newsoft;
    if (setrlimit(RLIMIT_NOFILE, &r) == -1) {
        perror("setrlimit");
        return 1;
    }
    getrlimit(RLIMIT_NOFILE, &r);
    printf("New limit      -> soft: %llu  hard: %llu\n",
           (unsigned long long)r.rlim_cur, (unsigned long long)r.rlim_max);
    return 0;
}
/*Output:
Max open files -> soft: 1024  hard: 4096
Enter new soft limit (must be <= hard limit): 2048
New limit      -> soft: 2048  hard: 4096
*/