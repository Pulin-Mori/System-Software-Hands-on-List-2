#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int pipeFds[2];
    if (pipe(pipeFds) == -1)
    {
        perror("Pipe Failed!\n");
        return 1;
    }
    int lsPid = fork();
    if (lsPid == -1)
    {
        perror("Fork Failed\n");
        return 1;
    }
    if (!lsPid)
    {
        close(pipeFds[0]);
        close(1);
        fcntl(pipeFds[1],F_DUPFD,1);
        close(pipeFds[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed\n");
        exit(1);
    }
    int wcPid = fork();
    if (wcPid == -1)
    {
        perror("Fork Failed\n");
        return 1;
    }
    if (!wcPid)
    {
        close(0);
        close(pipeFds[1]);
        fcntl(pipeFds[0],F_DUPFD,0);
        close(pipeFds[0]);
        execlp("wc", "wc", NULL);
        perror("execlp failed\n");
        exit(1);
    }

    close(pipeFds[0]);
    close(pipeFds[1]);
    waitpid(lsPid, NULL, 0);
    waitpid(wcPid, NULL, 0);
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q17$ nano question_17c.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q17$ cc question_17c.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q17$ ./a.out
      5      38     235
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q17$ 

*/
