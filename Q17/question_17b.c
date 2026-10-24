#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

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

        dup2(pipeFds[1],1);
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
        close(pipeFds[1]);
        dup2(pipeFds[0],0);
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
ulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q17$ nano question_17b.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q17$ cc question_17b.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q17$ ./a.out
      4      29     176
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q17$
*/
