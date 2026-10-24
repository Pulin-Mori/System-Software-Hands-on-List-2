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
void setLimit(int resource, int newLimit)
{
    struct rlimit resourceLimit;
    int getStatus = getrlimit(resource, &resourceLimit);
    if (getStatus == -1)
    {
        perror("getrlimit failed\n");
        return;
    }
    resourceLimit.rlim_cur = newLimit;
    int setStatus = setrlimit(resource, &resourceLimit);
    if (setStatus == -1)
    {
        perror("setrlimit failed\n");
        return;
    }
}

int main()
{
    char *resourceNames[] = {
        "Max core file size",
        "Max CPU time (seconds)",
        "Max data segment size",
        "Max file size",
        "Max open files",
        "Max processes per user",
        "Max stack size"};
    int resourceFlags[] = {
        RLIMIT_CORE,
        RLIMIT_CPU,
        RLIMIT_DATA,
        RLIMIT_FSIZE,
        RLIMIT_NOFILE,
        RLIMIT_NPROC,
        RLIMIT_STACK};
    printf("Enter the resource to change the limit:\n");
    for (int i = 0; i < 7; i++)
        printf("%d. %s\n", i + 1, resourceNames[i]);
    int choice = 0;

    scanf("%d", &choice);
    if (choice > 7 || choice < 1)
    {
        perror("Choice should be between 1-7\n");
        return 1;
    }
    int newLimit = 0;
    printf("Enter new limit for the resource:");
    scanf("%d", &newLimit);
    printf("Before Update\n");
    printLimit(resourceFlags[choice - 1]);
    setLimit(resourceFlags[choice - 1], newLimit);
    printf("After Update\n");
    printLimit(resourceFlags[choice - 1]);

    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q03$ nano question_3.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q03$ cc question_3.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q03$ ./a.out
Enter the resource to change the limit:
1. Max core file size
2. Max CPU time (seconds)
3. Max data segment size
4. Max file size
5. Max open files
6. Max processes per user
7. Max stack size
5
Enter new limit for the resource:200
Before Update
soft limit : 1024
hard limit : 524288
After Update
soft limit : 200
hard limit : 524288
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q03$ 

*/
