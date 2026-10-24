#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{

    char *pipe = "myfifo";
    int fd = open(pipe, O_RDONLY);

    if (fd == -1)
    {
        perror("Error opening FIFO\n");
        return 1;
    }

    fd_set readfds;
    struct timeval timeout;
    int ret;
    char buffer[100];

    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    ret = select(fd + 1, &readfds, NULL, NULL, &timeout);
    if (ret == -1)
    {
        perror("Error in select");
        return 1;
    }
    else if (ret)
    {
        printf("Data is available now.\n");
        read(fd, buffer, sizeof(buffer));
        printf("Data entered : %s\n", buffer);
    }
    else
    {
        printf("No data within 10 seconds.\n");
    }
    return 0;
}
/*
Terminal 1:
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q22$ nano question_22.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q22$ cc question_22.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q22$ ./a.out
Data is available now.
Data entered : Hello from Pulin

pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q22$ 

Terminal 2:
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q22$ mkfifo myfifo
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q22$ echo "Hello from Pulin" > myfifo
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q22$ 
*/
