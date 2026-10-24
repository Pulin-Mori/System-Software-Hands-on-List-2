#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>

#define SHM_SIZE 1024

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int main() {
    key_t shm_key = ftok(".", 'b');
    key_t sem_key = ftok(".", 's');

    // Create / get shared memory segment
    int shmid = shmget(shm_key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }
    char *shm_ptr = (char *)shmat(shmid, NULL, 0);

    // Create / initialize binary semaphore
    int semid = semget(sem_key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid != -1) {
        union semun arg;
        arg.val = 1;
        semctl(semid, 0, SETVAL, arg);
    } else if (errno == EEXIST) {
        semid = semget(sem_key, 1, 0666);
    } else {
        perror("semget failed");
        exit(1);
    }

    struct sembuf p = {0, -1, 0}; // Lock
    struct sembuf v = {0, 1, 0};  // Unlock

    printf("[PID %d] Requesting write lock on shared memory...\n", getpid());
    semop(semid, &p, 1);

    printf("[PID %d] Lock acquired! Enter message to write: ", getpid());
    fgets(shm_ptr, SHM_SIZE, stdin);

    printf("[PID %d] Written to shared memory: %s", getpid(), shm_ptr);
    printf("Press Enter to release write lock...");
    char buf[10];
    fgets(buf, sizeof(buf), stdin);

    semop(semid, &v, 1);
    printf("[PID %d] Lock released.\n", getpid());

    shmdt(shm_ptr);
    return 0;
}
/*
Terminal 1:
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ nano question_32b.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ cc question_32b.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ ./a.out
[PID 8638] Requesting write lock on shared memory...
[PID 8638] Lock acquired! Enter message to write: Pulin Mori
[PID 8638] Written to shared memory: Pulin Mori
Press Enter to release write lock...
[PID 8638] Lock released.
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ 

Terminal 2:
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ ./a.out
[PID 8640] Requesting write lock on shared memory...
[PID 8640] Lock acquired! Enter message to write: iroM niluP
[PID 8640] Written to shared memory: iroM niluP
Press Enter to release write lock...
[PID 8640] Lock released.
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ 

*/
