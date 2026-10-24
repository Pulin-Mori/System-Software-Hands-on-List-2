#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int main() {
    key_t key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Create or retrieve semaphore
    int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid != -1) {
        // First process initializes semaphore to 1
        union semun arg;
        arg.val = 1;
        semctl(semid, 0, SETVAL, arg);
    } else if (errno == EEXIST) {
        semid = semget(key, 1, 0666);
    } else {
        perror("semget failed");
        exit(1);
    }

    struct sembuf p = {0, -1, 0}; // Wait / Lock
    struct sembuf v = {0, 1, 0};  // Signal / Unlock

    printf("[PID %d] Waiting to enter critical section...\n", getpid());
    semop(semid, &p, 1);

    printf("[PID %d] Entered critical section.\n", getpid());

    // Read and update ticket counter in ticket.txt
    int fd = open("ticket.txt", O_RDWR | O_CREAT, 0666);
    int ticket = 0;
    ssize_t bytes = read(fd, &ticket, sizeof(ticket));
    if (bytes == 0) {
        ticket = 1;
    } else {
        ticket++;
    }

    printf("[PID %d] Allocated Ticket Number: %d\n", getpid(), ticket);
    printf("Press Enter to write back and release lock...");
    char buf[10];
    fgets(buf, sizeof(buf), stdin);

    lseek(fd, 0, SEEK_SET);
    write(fd, &ticket, sizeof(ticket));
    close(fd);

    // Release lock
    semop(semid, &v, 1);
    printf("[PID %d] Released lock and exited critical section.\n", getpid());

    return 0;
}
/*
Terminal 1:
ulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ nano question_32a.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ cc question_32a.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ ./a.out
[PID 8561] Waiting to enter critical section...
[PID 8561] Entered critical section.
[PID 8561] Allocated Ticket Number: 1
Press Enter to write back and release lock...
[PID 8561] Released lock and exited critical section.
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$

Terminal 2:
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ ./a.out
[PID 8566] Waiting to enter critical section...
[PID 8566] Entered critical section.
[PID 8566] Allocated Ticket Number: 2
Press Enter to write back and release lock...
[PID 8566] Released lock and exited critical section.
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ 

*/
