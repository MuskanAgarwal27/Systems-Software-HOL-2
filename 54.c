#include <stdio.h>
#include <sys/resource.h>
void show(const char *name, int resource)
{
    struct rlimit r;
    if (getrlimit(resource, &r) == -1) {
        perror(name);
        return;
    }
    printf("%-16s soft: ", name);
    if (r.rlim_cur == RLIM_INFINITY) printf("%-14s", "unlimited");
    else printf("%-14llu", (unsigned long long)r.rlim_cur);
    printf(" hard: ");
    if (r.rlim_max == RLIM_INFINITY) printf("unlimited\n");
    else printf("%llu\n", (unsigned long long)r.rlim_max);
}
int main(void)
{
    show("RLIMIT_AS", RLIMIT_AS);
    show("RLIMIT_CORE", RLIMIT_CORE);
    show("RLIMIT_CPU", RLIMIT_CPU);
    show("RLIMIT_DATA", RLIMIT_DATA);
    show("RLIMIT_FSIZE", RLIMIT_FSIZE);
    show("RLIMIT_LOCKS", RLIMIT_LOCKS);
    show("RLIMIT_MEMLOCK", RLIMIT_MEMLOCK);
    show("RLIMIT_MSGQUEUE", RLIMIT_MSGQUEUE);
    show("RLIMIT_NICE", RLIMIT_NICE);
    show("RLIMIT_NOFILE", RLIMIT_NOFILE);
    show("RLIMIT_NPROC", RLIMIT_NPROC);
    show("RLIMIT_RSS", RLIMIT_RSS);
    show("RLIMIT_RTPRIO", RLIMIT_RTPRIO);
    show("RLIMIT_SIGPENDING", RLIMIT_SIGPENDING);
    show("RLIMIT_STACK", RLIMIT_STACK);
    return 0;
}
/*Output:
RLIMIT_AS         soft: unlimited      hard: unlimited
RLIMIT_CORE       soft: unlimited      hard: unlimited
RLIMIT_CPU        soft: unlimited      hard: unlimited
RLIMIT_DATA       soft: unlimited      hard: unlimited
RLIMIT_FSIZE      soft: unlimited      hard: unlimited
RLIMIT_LOCKS      soft: unlimited      hard: unlimited
RLIMIT_MEMLOCK    soft: unlimited      hard: unlimited
RLIMIT_MSGQUEUE   soft: 819200         hard: 819200
RLIMIT_NICE       soft: 0              hard: 0
RLIMIT_NOFILE     soft: 1024           hard: 4096
RLIMIT_NPROC      soft: 709            hard: 709
RLIMIT_RSS        soft: unlimited      hard: unlimited
RLIMIT_RTPRIO     soft: 0              hard: 0
RLIMIT_SIGPENDING soft: 709            hard: 709
RLIMIT_STACK      soft: 8192           hard: unlimited
*/