#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void signalHandler(int signalNumber)
{
    printf("Segmentation fault caught with Signal Number : %d\n", signalNumber);
    printf("Unsafe to proceed\n");
    printf("Exiting...\n");
    exit(1);
}
int main()
{
    struct sigaction faultCatcher;
    faultCatcher.sa_handler = signalHandler;
    sigemptyset(&faultCatcher.sa_mask);
    faultCatcher.sa_flags = 0;

    int *ptr = NULL;
    int status = sigaction(SIGSEGV, &faultCatcher, NULL);
    if (status == -1)
    {
        perror("sigaction failed\n");
        return 1;
    }
    printf("Trying to access null pointer\n");
    *ptr = 73;
    return 0;
}
/*
ulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q10$ nano question_10a.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q10$ cc question_10a.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q10$ ./a.out
Trying to access null pointer
Segmentation fault caught with Signal Number : 11
Unsafe to proceed
Exiting...
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q10$ 
*/
