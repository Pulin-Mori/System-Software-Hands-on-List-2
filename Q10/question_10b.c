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
    struct sigaction faultCatcher;
    faultCatcher.sa_handler = signalHandler;
    sigemptyset(&faultCatcher.sa_mask);
    faultCatcher.sa_flags = 0;

    int status = sigaction(SIGINT, &faultCatcher, NULL);
    if (status == -1)
    {
        perror("sigaction failed\n");
        return 1;
    }
    printf("Beginning Infinte loop\n");
    printf("Presss Ctrl + C to trigger SIGINT Signal to quit\n");
    while(1){

    }
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q10$ nano question_10b.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q10$ cc question_10b.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q10$ ./a.out
Beginning Infinte loop
Presss Ctrl + C to trigger SIGINT Signal to quit
^C
Ctrl + C  detected with signal Number : 2
Quiting infinite Loop
Exiting...
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q10$
*/
