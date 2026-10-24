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
    signal(SIGFPE, signalHandler);
    printf("Dividing by 0\n");
    int a,b;
    a=10,b=0;
    int num = a/b;
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ nano question_8c.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ cc question_8c.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ ./a.out
Dividing by 0
Signal Number : 8
Indicates division by zero
Exiting...
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ 

*/
