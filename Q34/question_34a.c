#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#define PORT 9001

void handleClient(int connection) {
    printf("Connection request from client has been received\n");
    char msg[256];
    memset(msg, 0, sizeof(msg));

    ssize_t bytes_read = read(connection, msg, sizeof(msg) - 1);
    if (bytes_read > 0) {
        msg[bytes_read] = '\0';
        printf("Client said: %s\n", msg);
        char *response = "Hello From Server\n";
        write(connection, response, strlen(response));
    }

    close(connection);
    exit(0);
}

int main() {
    // Automatically reap terminated child processes to prevent zombies
    signal(SIGCHLD, SIG_IGN);

    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    struct sockaddr_in address;
    int opt = 1;
    setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(socketFD, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(socketFD);
        exit(1);
    }

    if (listen(socketFD, 5) < 0) {
        perror("Listen failed");
        close(socketFD);
        exit(1);
    }

    printf("Server is listening on Port: %d\n", PORT);

    while (1) {
        printf("Waiting for client to connect...\n");
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);

        int connection = accept(socketFD, (struct sockaddr *)&client_addr, &len);
        if (connection < 0) {
            perror("Accept failed");
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            close(connection);
            continue;
        } else if (pid == 0) {
            // Child process handles client
            close(socketFD);
            handleClient(connection);
        } else {
            // Parent process tracks listening socket
            close(connection);
        }
    }

    close(socketFD);
    return 0;
}
/*
Terminal 1:
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q34$ nano question_34a.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q34$ cc question_34a.c -o server_fork
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q34$ ./server_fork 
Server is listening on Port: 9001
Waiting for client to connect...
Waiting for client to connect...
Connection request from client has been received
Client said: Hello from Pulin

^C
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q34$

Terminal 2:
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q34$ nc 127.0.0.1 9001
Hello from Pulin
Hello From Server
^C
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q34$ 

*/
