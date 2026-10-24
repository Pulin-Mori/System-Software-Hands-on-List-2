#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

volatile sig_atomic_t timerExpired = 0;
void handleSIGVTALRM(int signalNumber)
{
    printf("Detected SIGVTALARM with signal number : %d\n", signalNumber);
    timerExpired = 1;
}

void setTimer(struct itimerval *timer, int sec, int micro)
{
    timer->it_value.tv_sec = sec;
    timer->it_value.tv_usec = micro;
    timer->it_interval.tv_sec = 0;
    timer->it_interval.tv_usec = 0;
}
void startTimer(struct itimerval timer)
{
    int timerStatus = setitimer(ITIMER_VIRTUAL, &timer, NULL);
    if (timerStatus == -1)
    {
        printf("Could not initiate the timer\n");
    }
}
int main()
{
    struct itimerval timerSec;

    setTimer(&timerSec, 5, 0);
    signal(SIGVTALRM, handleSIGVTALRM);
    printf("5 seconds timer starts now\n");
    startTimer(timerSec);
    while (!timerExpired)
        ;
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ nano question_8f.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ cc question_8f.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ ./a.out
5 seconds timer starts now
Detected SIGVTALARM with signal number : 26
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ 

*/
