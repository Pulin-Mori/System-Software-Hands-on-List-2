#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handleSIGALRM(int signalNumber)
{
    printf("Detected SIGALARM with signal number : %d\n", signalNumber);
}

int main()
{
    signal(SIGALRM, handleSIGALRM);
    printf("Raising a alarm signal in 5 seconds..\n");

    alarm(5);

    pause();
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ nano question_8d.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ cc question_8d.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ ./a.out
Raising a alarm signal in 5 seconds..
Detected SIGALARM with signal number : 14
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ 

*/
