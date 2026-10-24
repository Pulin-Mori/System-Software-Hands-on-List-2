#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

volatile sig_atomic_t timerExpired = 0;
void handleSIGPROF(int signalNumber)
{
    printf("Detected SIGPROF with signal number : %d\n", signalNumber);
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
    int timerStatus = setitimer(ITIMER_PROF, &timer, NULL);
    if (timerStatus == -1)
    {
        printf("Could not initiate the timer\n");
    }
}
int main()
{
    struct itimerval timerSec;

    setTimer(&timerSec, 5, 0);
    signal(SIGPROF, handleSIGPROF);
    printf("5 seconds timer starts now\n");
    startTimer(timerSec);
    while (!timerExpired)
    {
        getpid();
    }
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ nano question_8g.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ cc question_8g.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ ./a.out
5 seconds timer starts now
Detected SIGPROF with signal number : 27
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q08$ 

*/
