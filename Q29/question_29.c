#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main()
{
    key_t uid = ftok("/root", 1);
    if (uid == -1)
    {
        perror("ftok failed\n");
        return 1;
    }
    int msgid = msgget(uid, 0);

    if (msgid == -1)
    {
        perror("msgget failed\n");
        return 1;
    }

    int rmStatus = msgctl(msgid, IPC_RMID, NULL);
    if (rmStatus == -1)
    {
        perror("msgctl failed\n");
        return 1;
    }
    printf("Msg queue deleted\n");

    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q29$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x01020002 0          pulin      644        0            0           

pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q29$ nano question_29.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q29$ cc question_29.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q29$ ./a.out
Msg queue deleted
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q29$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    

pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q29$ 
*/
