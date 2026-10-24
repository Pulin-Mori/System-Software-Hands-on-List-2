#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int main()
{
    printf("SIGINT will be ignored for 10 seconds\n");
    printf("You cannot exit using CTRL + C\n");
    signal(SIGINT,SIG_IGN);

    sleep(10);
    
    printf("\nsetting SIGINT to its default behaviour\n");
    signal(SIGINT,SIG_DFL);
    printf("Press CTRL + C to exit program\n");
    pause();
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q09$ nano question_9.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q09$ cc question_9.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q09$ ./a.out
SIGINT will be ignored for 10 seconds
You cannot exit using CTRL + C
^C^C^C^C^C
^C^C
^C
^C^C^C

setting SIGINT to its default behaviour
Press CTRL + C to exit program
^C
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q09$ 
*/
