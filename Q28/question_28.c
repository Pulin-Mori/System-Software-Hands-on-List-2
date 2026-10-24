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
    printf("Original Access Mode (octal): %d\n", info.msg_perm.mode);
    printf("changing permission to 0644..\n");
    info.msg_perm.mode = 0644;

    int editStatus = msgctl(msgid, IPC_SET, &info);
    if (editStatus == -1)
    {
        perror("msgctl failed\n");
        return 1;
    }
    printf("permission changed\n");

    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q28$ nano question_28.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q28$ cc question_28.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q28$ ./a.out
accessing message queue info with id : 0
Original Access Mode (octal): 438
changing permission to 0644..
permission changed
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q28$ ipcs -q -i 0

Message Queue msqid=0
uid=1000	gid=1000	cuid=1000	cgid=1000	mode=0644
cbytes=0	qbytes=16384	qnum=0	lspid=7574	lrpid=7594
send_time=Tue Oct 20 18:18:13 2026  
rcv_time=Tue Oct 20 18:18:31 2026  
change_time=Tue Oct 20 18:20:47 2026  

pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q28$ 
*/
