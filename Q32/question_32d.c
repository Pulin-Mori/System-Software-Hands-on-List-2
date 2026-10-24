#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    char choice;
    printf("Select semaphore to remove:\n");
    printf("  'a' -> Ticket creation semaphore (32a)\n");
    printf("  's' -> Shared memory semaphore (32b)\n");
    printf("  'c' -> Counting semaphore (32c)\n");
    printf("Enter choice [a/s/c]: ");
    scanf(" %c", &choice);

    key_t key = ftok(".", choice);
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    int semid = semget(key, 1, 0);
    if (semid == -1) {
        perror("Semaphore not found");
        exit(1);
    }

    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("Failed to remove semaphore");
        exit(1);
    }

    printf("Semaphore (ID: %d, Key: 0x%08x) removed successfully.\n", semid, key);
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ nano question_32d.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ cc question_32d.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ ./a.out
Select semaphore to remove:
  'a' -> Ticket creation semaphore (32a)
  's' -> Shared memory semaphore (32b)
  'c' -> Counting semaphore (32c)
Enter choice [a/s/c]: c
Semaphore (ID: 4, Key: 0x63021747) removed successfully.
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$ ./a.out
Select semaphore to remove:
  'a' -> Ticket creation semaphore (32a)
  's' -> Shared memory semaphore (32b)
  'c' -> Counting semaphore (32c)
Enter choice [a/s/c]: c
Semaphore not found: No such file or directory
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q32$
*/
