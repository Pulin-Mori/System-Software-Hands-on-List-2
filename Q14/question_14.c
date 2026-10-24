#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pipefds[2];
    int pipeStatus = pipe(pipefds);
    if (pipeStatus == -1)
    {
        perror("Error in pipe system call\n");
        return 1;
    }
    printf("Writing to pipe write end\n");
    char *text = "Hello, I wrote to the pipe\n";
    int writeStatus = write(pipefds[1], text, strlen(text));
    if (writeStatus == -1)
    {
        perror("Error while writing to pipe\n");
        return 1;
    }
    char buffer[256];
    int readStatus = read(pipefds[0], &buffer, 256);
    if (readStatus == -1)
    {
        perror("Error while reading from pipe\n");
        return 1;
    }
    printf("Printing what I read from the pipe\n");
    for (int i = 0; i < readStatus; i++)
        printf("%c", buffer[i]);
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q14$ nano question_14.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q14$ cc question_14.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q14$ ./a.out
Writing to pipe write end
Printing what I read from the pipe
Hello, I wrote to the pipe
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q14$ 

*/
