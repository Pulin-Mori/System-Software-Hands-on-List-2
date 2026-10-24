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
    int *ptr = NULL;
    signal(SIGSEGV, signalHandler);
    printf("Trying to access null pointer\n");
    *ptr = 73;
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ nano question_8a.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ cc question_8a.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ ./a.out
Trying to access null pointer
Segmentation fault caught with Signal Number : 11
Unsafe to proceed
Exiting...
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ 

*/
