#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>
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
    printf("Max open files\n");
    printLimit(RLIMIT_NOFILE);

    int pipeFd[2];
    if (pipe(pipeFd) == -1)
    {
        perror("Pipe failed\n");
        return 1;
    }
    long long pipeSize = fpathconf(pipeFd[0], _PC_PIPE_BUF);
    if (pipeSize == -1)
    {
        perror("fpathconf fail\n");
        return 1;
    }
    printf("size of pipe (circular buffer) : %lld\n", pipeSize);
    close(pipeFd[0]);
    close(pipeFd[1]);

    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q23$ nano question_23.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q23$ cc question_23.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q23$ ./a.out
Max open files
soft limit : 1024
hard limit : 524288
size of pipe (circular buffer) : 4096
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q23$ 
*/
