#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
    key_t uid = ftok("/root", 1);
    if (uid == -1)
    {
        perror("ftok failed\n");
        return 1;
    }
    int memSize = 256;
    int shmid = shmget(uid, memSize, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget failed\n");
        return 1;
    }
    printf("Shared memory Id : %d\n", shmid);
    char *shPtr = shmat(shmid, NULL, 0);
    printf("Writing to shared memory\n");
    strcpy(shPtr, "Hello Shared Memory!");

    printf("This is the data in shared memory : %s\n", shPtr);
    char *readPtr = shmat(shmid, NULL, SHM_RDONLY);
    printf("Writing to read only shared memory\n");
    // strcpy(readPtr, "This will fail!");

    printf("Detaching the shared memory\n");

    shmdt(shPtr);
    shmdt(readPtr);
    printf("Removing the shared memory\n");
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q30$ nano question_30.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q30$ cc question_30.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q30$ ./a.out
Shared memory Id : 0
Writing to shared memory
This is the data in shared memory : Hello Shared Memory!
Writing to read only shared memory
Detaching the shared memory
Removing the shared memory
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q30$ 
*/
