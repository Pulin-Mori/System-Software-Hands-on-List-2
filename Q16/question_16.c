#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void writeToFD(int fd, char *text)
{
    int writeStatus = write(fd, text, strlen(text));
    if (writeStatus == -1)
    {
        perror("Error while writing to pipe\n");
        exit(1);
    }
}

void readFromFD(int fd)
{
    char buffer[256];
    int readStatus = read(fd, &buffer, 256);
    if (readStatus == -1)
    {
        perror("Error while reading from pipe\n");
        exit(1);
    }
    for (int i = 0; i < readStatus; i++)
        printf("%c", buffer[i]);
}

int main()
{
    int parTochild[2];
    int childToPar[2];

    if (pipe(parTochild) == -1 || pipe(childToPar))
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
        close(parTochild[0]);
        close(childToPar[1]);
        printf("Parent is writing to child \n");
        char *text = "Hello, From parent\n";
        writeToFD(parTochild[1], text);
        sleep(1);
        printf("Parent is reading what the child has sent\n");
        readFromFD(childToPar[0]);
        close(parTochild[1]);
        close(childToPar[0]);
        wait(0);
    }
    else
    {
        close(childToPar[0]);
        close(parTochild[1]);
        printf("Child is writing to parent \n");
        char *text = "Hello, From child\n";
        writeToFD(childToPar[1], text);
        sleep(2);
        printf("Child is reading what the parent has sent\n");
        readFromFD(parTochild[0]);
        close(childToPar[1]);
        close(parTochild[0]);
       
    }
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q16$ nano question_16.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q16$ cc question_16.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q16$ ./a.out
Parent is writing to child 
Child is writing to parent 
Parent is reading what the child has sent
Hello, From child
Child is reading what the parent has sent
Hello, From parent
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q16$
*/
