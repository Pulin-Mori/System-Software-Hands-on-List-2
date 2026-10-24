#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void signalHandler(int signalNumber)
{
    printf("\nCtrl + C  detected with signal Number : %d\n", signalNumber);
    printf("Quiting infinite Loop\n");
    printf("Exiting...\n");
    exit(1);
}
int main()
{
    signal(SIGINT, signalHandler);
    printf("Beginning Infinte loop\n");
    printf("Presss Ctrl + C to trigger SIGINT Signal to quit\n");
    while(1){

    }
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ nano question_8b.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ cc question_8b.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ ./a.out
Beginning Infinte loop
Presss Ctrl + C to trigger SIGINT Signal to quit
^C
Ctrl + C  detected with signal Number : 2
Quiting infinite Loop
Exiting...
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ 

*/
