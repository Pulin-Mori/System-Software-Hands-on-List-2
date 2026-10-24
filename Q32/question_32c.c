#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int main() {
    key_t key = ftok(".", 'c');
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Initialize counting semaphore to 2 (2 available resources)
    int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid != -1) {
        union semun arg;
        arg.val = 2; // Two pseudo resources available
        semctl(semid, 0, SETVAL, arg);
    } else if (errno == EEXIST) {
        semid = semget(key, 1, 0666);
    } else {
        perror("semget failed");
        exit(1);
    }

    struct sembuf p = {0, -1, 0}; // Decrement (acquire 1 resource)
    struct sembuf v = {0, 1, 0};  // Increment (release 1 resource)

    printf("[PID %d] Requesting pseudo resource (Total slots: 2)...\n", getpid());
    semop(semid, &p, 1);

    printf(">> [PID %d] Resource acquired! Using resource now.\n", getpid());
    printf(">> Press Enter to release the resource...");
    char buf[10];
    fgets(buf, sizeof(buf), stdin);

    semop(semid, &v, 1);
    printf("<< [PID %d] Resource released.\n", getpid());

    return 0;
}
/*
Terminal 1:
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ nano question_32c.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ cc question_32c.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ ./a.out
[PID 8701] Requesting pseudo resource (Total slots: 2)...
>> [PID 8701] Resource acquired! Using resource now.
>> Press Enter to release the resource...
<< [PID 8701] Resource released.
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ 

Terminal 2:
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ ./a.out
[PID 8706] Requesting pseudo resource (Total slots: 2)...
>> [PID 8706] Resource acquired! Using resource now.
>> Press Enter to release the resource...
<< [PID 8706] Resource released.
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$

Terminal 3:
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ ./a.out
[PID 8708] Requesting pseudo resource (Total slots: 2)...
>> [PID 8708] Resource acquired! Using resource now.
>> Press Enter to release the resource...
<< [PID 8708] Resource released.
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ 

*/
