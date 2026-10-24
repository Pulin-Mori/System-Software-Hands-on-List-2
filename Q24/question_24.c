#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    key_t uid = ftok("/root", 1);
    if (uid == -1)
    {
        perror("ftok failed\n");
        return 1;
    }
    int msgid = msgget(uid, IPC_CREAT | 0666);

    if (msgid == -1)
    {
        perror("msgget failed\n");
        return 1;
    }
    printf("Message queue created with key : %d and msg queue id : %d\n", uid, msgid);

    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q24$ nano question_24.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q24$ cc question_24.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q24$ ./a.out
Message queue created with key : 16908290 and msg queue id : 0
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q24$ 
*/
