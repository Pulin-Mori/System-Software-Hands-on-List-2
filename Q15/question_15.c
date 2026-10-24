#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int pipefds[2];
    int pipeStatus = pipe(pipefds);
    if (pipeStatus == -1)
    {
        perror("Error in pipe system call\n");
        return 1;
    }
    int pid = fork();
    if (pid == -1)
    {
        perror("Fork Failed\n");
        return 1;
    }
    if (pid)
    {
        printf("Parent is writing to pipe write end\n");
        close(pipefds[0]);
        char *text = "Hello, From parent\n";
        int writeStatus = write(pipefds[1], text, strlen(text));
        if (writeStatus == -1)
        {
            perror("Error while writing to pipe\n");
            exit(1);
        }
        close(pipefds[1]);
        wait(0);
    }
    else
    {

        char buffer[256];
        close(pipefds[1]);
        int readStatus = read(pipefds[0], &buffer, 256);
        if (readStatus == -1)
        {
            perror("Error while reading from pipe\n");
            exit(1);
        }
        close(pipefds[0]);
        printf("Printing what child read from the pipe\n");
        for (int i = 0; i < readStatus; i++)
            printf("%c", buffer[i]);
    }
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q15$ nano question_15.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q15$ cc question_15.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q15$ ./a.out
Parent is writing to pipe write end
Printing what child read from the pipe
Hello, From parent
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q15$
*/
