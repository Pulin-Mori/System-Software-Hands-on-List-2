#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include<unistd.h>

void handleSIGALRM(int signalNumber)
{
    printf("Detected SIGALARM with signal number : %d\n", signalNumber);
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
    int timerStatus = setitimer(ITIMER_REAL, &timer, NULL);
    if (timerStatus == -1)
    {
        printf("Could not initiate the timer\n");
    }
}

int main()
{
    struct itimerval timerSec;

    setTimer(&timerSec, 5, 0);
    signal(SIGALRM, handleSIGALRM);

    printf("5 seconds timer starts now\n");
    startTimer(timerSec);
    pause();
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ nano question_8e.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ cc question_8e.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ ./a.out
5 seconds timer starts now
Detected SIGALARM with signal number : 14
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ 

*/
