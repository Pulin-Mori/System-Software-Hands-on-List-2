#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
unsigned long long rdtsc()
{
    unsigned long long dst;
    __asm__ __volatile__("rdtsc" : "=A"(dst));
    return dst;
}
int main()
{
    unsigned long long startTime, endTime;
    startTime = rdtsc();
    for (int i = 0; i < 100; i++)
        getppid();
    endTime = rdtsc();

    printf("Time Taken by 100 getppids : %llu\n", endTime - startTime);
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q04$ nano question_4.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q04$ cc question_4.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q04$ ./a.out
Time Taken by 100 getppids : 154446
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q04$ 

*/
