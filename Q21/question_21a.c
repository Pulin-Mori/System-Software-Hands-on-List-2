#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main()
{
    char *pipe_name1 = "pipe1";
    char *pipe_name2 = "pipe2";
    printf("Opening FIFO..\n");

    int fd1 = open(pipe_name1,O_WRONLY);
    int fd2 = open(pipe_name2,O_RDONLY);
    
    if(fd1==-1 || fd2==-1)
    {
        perror("Error opening pipe\n");
        return 1;
    }
    printf("FIFO Successfully Opened\n");
    printf("Writing data to p2...\n");
    char * data = "Hello from p1\n";
    if(write(fd1,data,strlen(data))!=strlen(data))
    {
        perror("Error writing to pipe\n");
        close(fd1);
        return 1;
    }
    printf("Reading from p2..\n");
    char buff[256];
    int len = read(fd2,buff,256);
    if(len==-1)
    {
        perror("Reading error\n");
        close(fd2);
        return 1;
    }
    printf("Data recieved from p2:\n");
    write(1,buff,len);
    close(fd2);
    close(fd1);
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q21$ mkfifo pipe1
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q21$ mkfifo pipe2
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q21$ nano question_21a.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q21$ cc question_21a.c -o P1
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q21$ ./P1
Opening FIFO..
FIFO Successfully Opened
Writing data to p2...
Reading from p2..
Data recieved from p2:
Hello from p2
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q21$ 
*/
