#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *handleThread(void *args)
{
    int thread_id = *((int *)args);
    printf("Thread executed with : %d\n",thread_id);
}
int main()
{
    pthread_t threads[3];
    int ids[3] = {1,2,3};
    printf("Thread Creation started...\n");

    for (int i = 0; i < 3; i++)
    {

        int threadStatus = pthread_create(&threads[i], NULL, handleThread, &ids[i]);
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
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q07$ nano question_7.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q07$ cc question_7.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q07$ ./a.out
Thread Creation started...
Waiting for threads to finish...
Thread executed with : 1
Thread executed with : 2
Thread executed with : 3
Main Thread finished
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q07$ 

*/
