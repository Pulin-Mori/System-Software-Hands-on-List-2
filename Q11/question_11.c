#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int main()
{
    struct sigaction faultCatcher;
    faultCatcher.sa_handler = SIG_IGN;
    sigemptyset(&faultCatcher.sa_mask);
    faultCatcher.sa_flags = 0;

    int status = sigaction(SIGINT, &faultCatcher, NULL);
    if (status == -1)
    {
        perror("sigaction failed\n");
        return 1;
    }
    printf("SIGINT will be ignored for 10 seconds\n");
    printf("You cannot exit using CTRL + C\n");
    

    sleep(10);
    
    printf("\nsetting SIGINT to its default behaviour\n");
    faultCatcher.sa_handler = SIG_DFL;
    
    status = sigaction(SIGINT, &faultCatcher, NULL);
    if (status == -1)
    {
        perror("sigaction failed\n");
        return 1;
    }
    printf("Press CTRL + C to exit program\n");
    pause();
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q11$ nano question_11.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q11$ cc question_11.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q11$ ./a.out
SIGINT will be ignored for 10 seconds
You cannot exit using CTRL + C
^C^C
^C^C^C^C
setting SIGINT to its default behaviour
Press CTRL + C to exit program
^C
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q11$ 
*/
