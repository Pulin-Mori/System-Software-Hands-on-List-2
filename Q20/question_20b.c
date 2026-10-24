#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char *pipe_name = "my_pipe";
    printf("Opening FIFO..\n");

    int fd = open(pipe_name, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening pipe\n");
        return 1;
    }
    printf("FIFO Successfully Opened\n");
    printf("Reading data from it...\n");
    char data[256];

    int dataLen = read(fd, data, 256);
    if (dataLen == -1)
    {
        perror("Error reading from pipe\n");
        close(fd);
        return 1;
    }
    write(1, data, dataLen);
    close(fd);
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q20$ nano question_20b.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q20$ cc question_20b.c -o recieve
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q20$ ./recieve 
Opening FIFO..
FIFO Successfully Opened
Reading data from it...
Hello from Pulin's write
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q20$
*/
