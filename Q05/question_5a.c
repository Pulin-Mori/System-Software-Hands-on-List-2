#include <stdio.h>
#include <unistd.h>

int main()
{
    long maxArguements = sysconf(_SC_ARG_MAX);
    long maxChildProcess = sysconf(_SC_CHILD_MAX);
    long clockTicks = sysconf(_SC_CLK_TCK);
    long maxOpenFiles = sysconf(_SC_OPEN_MAX);
    long pageSize = sysconf(_SC_PAGE_SIZE);
    long totalPages = sysconf(_SC_PHYS_PAGES);
    long availablePages = sysconf(_SC_AVPHYS_PAGES);
    if (maxArguements == -1||maxChildProcess == -1||clockTicks == -1||maxOpenFiles == -1||pageSize == -1||totalPages == -1||availablePages == -1 )
    {
        perror("sysconf failed\n");
        return 1;
    }
    printf("maximum length of the arguments to the exec family of functions : %ld\n", maxArguements);
    printf("maximum number of simultaneous process per user id : %ld\n", maxChildProcess);
    printf("number of clock ticks (jiffy) per second : %ld\n", clockTicks);
    printf("maximum number of open files : %ld\n", maxOpenFiles);
    printf("size of a page : %ld\n", pageSize);
    printf("total number of pages in the physical memory : %ld\n", totalPages);
    printf("number of currently available pages in the physical memory : %ld\n", availablePages);
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q05$ nano question_5a.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q05$ cc question_5a.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q05$ ./a.out
maximum length of the arguments to the exec family of functions : 2097152
maximum number of simultaneous process per user id : 30074
number of clock ticks (jiffy) per second : 100
maximum number of open files : 1024
size of a page : 4096
total number of pages in the physical memory : 2562703
number of currently available pages in the physical memory : 1781579
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q05$ 

*/
