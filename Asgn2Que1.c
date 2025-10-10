#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int ret;
	int status;
	int i;
	for(i=0;i<5;i++)
	{
		ret=fork();
		if(ret==-1)
		{
			printf("Fork failed to create a new process!!!!\n");
			exit(1);
		}
		else if(ret==0)
		{
		for(int count=1;count<=5;count++)
		{
				printf("child:%d pid=%d count=%d\n",i+1,getpid(),count);
				sleep(1);
		}
               	exit(0);
		}

	}
	for(i=0;i<5;i++)
	{
		wait(&status);
				printf("exit status off child = %d\n", WEXITSTATUS(status));
	}

	printf("Parent PID=%d All Proceess are cleaned\n",getpid());
	return 0;
}





