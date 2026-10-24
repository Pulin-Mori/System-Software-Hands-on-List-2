#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

volatile sig_atomic_t timerExpired = 0;

void handleSignal(int signal)
{
    printf("Timer ended with signal: %d\n", signal);
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
    struct itimerval timerMilliSec;

    setTimer(&timerSec, 10, 0);
    setTimer(&timerMilliSec, 0, 10);
    signal(SIGPROF, handleSignal);

    printf("10 seconds timer starts now\n");
    startTimer(timerSec);
    while (!timerExpired)
        getpid();
        
    timerExpired = 0;

    printf("10 microseconds timer starts now\n");
    startTimer(timerMilliSec);
    while (!timerExpired)
        getpid();
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q01$ ./a.out
10 seconds timer starts now
Timer ended with signal: 27
10 microseconds timer starts now
Timer ended with signal: 27
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q01$ 

*/
