#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void signalHandler(int signalNumber)
{
    printf("Signal Number : %d\n", signalNumber);
    printf("Indicates division by zero\n");
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
    int status = sigaction(SIGFPE, &faultCatcher, NULL);
    if (status == -1)
    {
        perror("sigaction failed\n");
        return 1;
    }
    printf("Dividing by 0\n");
    int a,b;
    a=10,b=0;
    int num = a/b;
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q10$ nano question_10c.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q10$ cc question_10c.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q10$ ./a.out
Dividing by 0
Signal Number : 8
Indicates division by zero
Exiting...
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q10$ 

*/
