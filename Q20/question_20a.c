#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main()
{
    char *pipe_name = "my_pipe";
    printf("Opening FIFO..\n");

    int fd = open(pipe_name,O_WRONLY);
    if(fd==-1)
    {
        perror("Error opening pipe\n");
        return 1;
    }
    printf("FIFO Successfully Opened\n");
    printf("Writing data to it...\n");
    char * data = "Hello from Pulin's write\n";
    if(write(fd,data,strlen(data))!=strlen(data))
    {
        perror("Error writing to pipe\n");
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q20$ mkfifo my_pipe
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q20$ nano question_20a.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q20$ cc question_20a.c -o write
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q20$ ./write 
Opening FIFO..
FIFO Successfully Opened
Writing data to it...
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q20$
*/
