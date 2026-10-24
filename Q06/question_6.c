#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *handleThread(void *args)
{
    // sleep(2);
    printf("Thread executed\n");
}
int main()
{
    pthread_t threads[3];
    printf("Thread Creation started...\n");

    for (int i = 0; i < 3; i++)
    {
        int threadStatus = pthread_create(&threads[i], NULL, handleThread, NULL);
        if (threadStatus != 0)
        {
            perror("pthread create failed\n");
            return 1;
        }
    }
    printf("Waiting for threads to finish...\n");

    for (int i = 0; i < 3; i++)
    {
        int joinStatus = pthread_join(threads[i], NULL);
        if (joinStatus != 0)
        {
            perror("pthread join failed\n");
            return 1;
        }
    }
    printf("Main Thread finished\n");
    return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q06$ nano question_6.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q06$ cc question_6.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q06$ ./a.out
Thread Creation started...
Thread executed
Waiting for threads to finish...
Thread executed
Thread executed
Main Thread finished
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q06$ 

*/
