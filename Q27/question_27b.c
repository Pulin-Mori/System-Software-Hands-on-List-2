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
    int msgid = msgget(uid, 0);

    if (msgid == -1)
    {
        perror("msgget failed\n");
        return 1;
    }
    struct msg_buffer msg;
    msg.mtype = 1;

    int len = sizeof(msg.mtext);
    printf("waiting for msg from the  msg queue with id : %d\n", msgid);
    int recieveStatus = msgrcv(msgid, &msg, len, 0, IPC_NOWAIT);
    if (recieveStatus == -1)
    {
        perror("msgrcv error\n");
        return 1;
    }
    printf("msg recieved\n");
    printf("Msg type: %ld\n", msg.mtype);
    printf("Msg content: %s\n", msg.mtext);

    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q27$ nano question_27b.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q27$ cc question_27b.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q27$ ./a.out
waiting for msg from the  msg queue with id : 0
msgrcv error
: No message of desired type
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q27$ cd ../Q26
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q26$ ./a.out
Sending msg to msg queue with id : 0
msg sent
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q26$ cd ../Q27
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q27$ cc question_27b.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q27$ ./a.out
waiting for msg from the  msg queue with id : 0
msg recieved
Msg type: 1
Msg content: hello to the msg queue
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q27$
*/
