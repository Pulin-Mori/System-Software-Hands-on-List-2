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
    struct msqid_ds info;
    printf("accessing message queue info with id : %d\n", msgid);

    int infoStatus = msgctl(msgid, IPC_STAT, &info);
    if (infoStatus == -1)
    {
        perror("msgctl failed\n");
        return 1;
    }
    printf("Access Mode (octal): %o\n", info.msg_perm.mode);
    printf("Owner UID : %d\n", info.msg_perm.uid);
    printf("Owner GID : %d\n", info.msg_perm.gid);
    printf("Last time msg sent : %s", ctime(&info.msg_stime));
    printf("Last time msg recieved : %s", ctime(&info.msg_rtime));
    printf("Last time of change : %s", ctime(&info.msg_ctime));
    printf("Size of msg queue : %ld Bytes\n", info.msg_qbytes);
    printf("Number of msgs in queue : %ld \n", info.msg_qnum);
    printf("Max bytes allowed  : %ld Bytes\n", info.msg_qbytes);
    printf("PID of last msg sent : %d \n", info.msg_lspid);
    printf("PID of last msg recieved : %d \n", info.msg_lrpid);

    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q25$ nano question_25.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q25$ cc question_25.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q25$ ./a.out
accessing message queue info with id : 0
Access Mode (octal): 666
Owner UID : 1000
Owner GID : 1000
Last time msg sent : Thu Jan  1 05:30:00 1970
Last time msg recieved : Thu Jan  1 05:30:00 1970
Last time of change : Tue Oct 20 18:09:54 2026
Size of msg queue : 16384 Bytes
Number of msgs in queue : 0 
Max bytes allowed  : 16384 Bytes
PID of last msg sent : 0 
PID of last msg recieved : 0 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q25$ 
*/
