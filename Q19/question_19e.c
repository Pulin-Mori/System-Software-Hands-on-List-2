#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *args[])
{
	if (argc != 2)
	{
		perror("Usage: <pipe_name>\n");
		return 1;
	}
	char *pipe_name = args[1];
	mode_t permissions = 0744;
	int creation_res = mkfifo(pipe_name, permissions);

	if (!creation_res)
		printf("FIFO Pipe created with name : %s\n", pipe_name);
	else
		perror("Unable to create\n");
	return 0;
}
/*
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q19$ nano question_19e.c
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q19$ cc question_19e.c 
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q19$ ./a.out pipe2
FIFO Pipe created with name : pipe2
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q19$ ls -l pipe2
prwxr--r-- 1 pulin pulin 0 Oct 20 19:25 pipe2
pulin@pulin-VMware-Virtual-Platform:~/Desktop/HOL2/Q19$
*/
