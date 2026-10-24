#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int signalNumber)
{
    printf("Trying to catch SIGSTOP with Signal Number : %d\n", signalNumber);
    printf("Exiting...\n");
}
int main()
{
    printf("U can try to stop me using a stop signal\n");
    printf("Here is my pid %d\n", getpid());
    signal(SIGSTOP, signalHandler);
    pause();
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q13$ nano question_12b.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q13$ cc question_12b.c -o reciever
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q13$ ./reciever 
U can try to stop me using a stop signal
Here is my pid 6010

[1]+  Stopped                    ./reciever
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q13$ 
*/
