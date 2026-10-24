#include <stdio.h>
#include <sys/resource.h>
void printLimit(int resource)
{
    struct rlimit resourceLimit;
    int getStatus = getrlimit(resource, &resourceLimit);

    if (getStatus == -1)
    {
        perror("getrlimit failed\n");
        return;
    }
    if (resourceLimit.rlim_cur == RLIM_INFINITY)
        printf("soft limit : infinty\n");
    else
        printf("soft limit : %lld\n", (long long)resourceLimit.rlim_cur);
    if (resourceLimit.rlim_max == RLIM_INFINITY)
        printf("hard limit : infinty\n");
    else
        printf("hard limit : %lld\n", (long long)resourceLimit.rlim_max);
}
int main()
{
    printf("Max core file size\n");
    printLimit(RLIMIT_CORE);
    printf("Max CPU time (seconds)\n");
    printLimit(RLIMIT_CPU);
    printf("Max data segment size\n");
    printLimit(RLIMIT_DATA);
    printf("Max file size\n");
    printLimit(RLIMIT_FSIZE);
    printf("Max open files\n");
    printLimit(RLIMIT_NOFILE);
    printf("Max processes per user\n");
    printLimit(RLIMIT_NPROC);
    printf("Max stack size\n");
    printLimit(RLIMIT_STACK);

    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q02$ nano question_2.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q02$ cc question_2.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q02$ ./a.out
Max core file size
soft limit : 0
hard limit : infinty
Max CPU time (seconds)
soft limit : infinty
hard limit : infinty
Max data segment size
soft limit : infinty
hard limit : infinty
Max file size
soft limit : infinty
hard limit : infinty
Max open files
soft limit : 1024
hard limit : 524288
Max processes per user
soft limit : 30074
hard limit : 30074
Max stack size
soft limit : 8388608
hard limit : infinty
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q02$
*/
