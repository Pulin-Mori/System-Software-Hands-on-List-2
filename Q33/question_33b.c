#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 9001

int main()
{

    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    int len = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
    printf("Client is pinging the server\n");
    int connectStatus = connect(socketFD, (struct sockaddr *)&address, sizeof(address));
    if (connectStatus == -1)
    {
        printf("connect failed\n");
        return 1;
    }
    char *msg = "Hey wanna connect?";
    write(socketFD, msg, strlen(msg));
    printf("Msg from client sent to server\n");
    char buffer[256];
    int responseLen = read(socketFD, buffer, 256);
    buffer[responseLen] = '\0';
    printf("Server said : %s\n", buffer);

    close(socketFD);
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q33$ cc question_33b.c -o client
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q33$ ./client
Client is pinging the server
Msg from client sent to server
Server said : Let's Connect...
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q33$ 
*/
