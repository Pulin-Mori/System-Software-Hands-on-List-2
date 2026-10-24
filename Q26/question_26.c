#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
struct msg_buffer
{
    long mtype;
    char mtext[100];
};
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
    struct msg_buffer msg;
    msg.mtype = 1;

    strcpy(msg.mtext, "hello to the msg queue\0");
    int len = strlen(msg.mtext);
    printf("Sending msg to msg queue with id : %d\n", msgid);
    int sentStatus = msgsnd(msgid, &msg, len, 0);
    if (sentStatus == -1)
    {
        perror("msgsnd error\n");
        return 1;
    }
    printf("msg sent\n");
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q26$ nano question_26.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q26$ cc question_26.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q26$ ./a.out
Sending msg to msg queue with id : 0
msg sent
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q26$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x01020002 0          pulin      666        22           1           

pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q26$ 
*/
