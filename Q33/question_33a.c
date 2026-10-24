#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9001
int main()
{

    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    int len = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(socketFD, (struct sockaddr *)&address, sizeof(address));

    listen(socketFD, 3);
    printf("Server is listening on Port : %d\n", PORT);
    int connection = accept(socketFD, (struct sockaddr *)&address, (socklen_t *)&len);

    printf("Connection request from client has been recieved\n");
    char msg[256];
    read(connection, msg, 256);
    printf("Client said : %s\n", msg);
    char *response = "Let's Connect...\0";
    write(connection, response, strlen(response));

    close(connection);
    close(socketFD);
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q33$ cc question_33a.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q33$ ./a.out
Server is listening on Port : 9001
Connection request from client has been recieved
Client said : Hey wanna connect?
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q33$
*/
