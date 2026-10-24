#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main()
{
    key_t uid = ftok("/root", 2);
    if (uid == -1)
    {
        perror("ftok failed\n");
        return 1;
    }
    int semid = semget(uid, 1, IPC_CREAT | 0666);
    if (semid == -1)
    {
        perror("semget failed\n");
        return 1;
    }
    union semun semaphore;
    semaphore.val = 10;
    if (semctl(semid, 0, SETVAL, semaphore) == -1)
    {
        perror("semctl failed\n");
        return 1;
    }
    printf("counting semaphore created\n");
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q31$ nano question_31b.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q31$ cc question_31b.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q31$ ./a.out
counting semaphore created
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q31$ ipcs -s

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     
0x01020002 0          pulin      666        1         
0x02020002 1          pulin      666        1         

pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q31$
*/
