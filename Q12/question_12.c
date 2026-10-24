#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Fork Failed\n");
        return 1;
    }
    if (!pid)
    {
        pid_t parentid = getppid();

        printf("Sending kill signal to parent with ppid : %d\n", parentid);
        sleep(2);
        int kill_status = kill(parentid, SIGKILL);

        if (kill_status == -1)
        {
            printf("kill signal to parent failed\n");
            exit(1);
        }
        sleep(1);
        printf("New parent id is %d\n", getppid());
        exit(0);
    }
    else
    {
        printf("parent waiting for kill signal\n");
        pause();
    }
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q12$ nano question_12.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q12$ nano question_12.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q12$ cc question_12.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q12$ ./a.out
parent waiting for kill signal
Sending kill signal to parent with ppid : 5869
Killed                     ./a.out
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q12$ New parent id is 2283
*/
