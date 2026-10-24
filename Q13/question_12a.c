#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>

int main(int argc,char* args[])
{
    
        if(argc!=2)
        {
            perror("Usage : <pid>");
            return 1;
        }
        pid_t pid = atoi(args[1]);

        printf("Sending kill signal to process with pid : %d\n", pid);
        
        int kill_status = kill(pid, SIGSTOP);

        if (kill_status == -1)
        {
            perror("kill signal to process failed\n");
            return 1;
        }
        
    return 0;
}
/*
ulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q13$ nano question_12a.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q13$ cc question_12a.c -o sender
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q13$ ./sender 
Usage : <pid>: Success
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q13$ ./sender 6010
Sending kill signal to process with pid : 6010
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q13$ 

*/
