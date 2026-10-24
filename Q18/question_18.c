#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int pipeFd1[2];
    int pipeFd2[2];
    if (pipe(pipeFd1) == -1 || pipe(pipeFd2) == -1 )
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
        
        dup2(pipeFd1[1],1);
        close(pipeFd1[1]);
        close(pipeFd1[0]);
        close(pipeFd2[0]);
        close(pipeFd2[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed\n");
        exit(1);
    }

    int grepPid = fork();
    if(grepPid==-1)
    {
        perror("Fork Failed\n");
        return 1;
    }
    if(!grepPid){
        dup2(pipeFd1[0],0);
        dup2(pipeFd2[1],1);
        close(pipeFd1[1]);
        close(pipeFd1[0]);
        close(pipeFd2[0]);
        close(pipeFd2[1]);
        
        
        execlp("grep", "grep", "^d", NULL);
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
        dup2(pipeFd2[0],0);
        close(pipeFd1[1]);
        close(pipeFd1[0]);
        close(pipeFd2[0]);
        close(pipeFd2[1]);
        
        execlp("wc", "wc", NULL);
        perror("execlp failed\n");
        exit(1);
    }

    close(pipeFd1[0]);
    close(pipeFd1[1]);
    close(pipeFd2[0]);
    close(pipeFd2[1]);
    waitpid(lsPid,NULL,0);
    waitpid(grepPid,NULL,0);
    waitpid(wcPid, NULL, 0);
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q18$ nano question_18.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q18$ cc question_18.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q18$ mkdir q
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q18$ ./a.out
      1       9      46
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q18$ 
*/
