#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
           int retA,retB,retC,retD;
           int status;
           int i;
	   printf("Program Started!!!\n");
	   printf("ParentA PID=%d \n",getpid());

	  if(retA==-1)
	  {
		  printf("fork failed to create a new process\n");
	  }
	  else if(retA==0)
	  {
		  retB=fork();
		  printf("Inside Parent Process A Child Process B is Created :\n");
		  

		  for(int count=1;count<=5;count++)
		  {
			  printf("child:%d pid=%d count=%d\n",i+1,getpid(),count);
			  sleep(1);
		  }
		  exit(0);
		  if(retB==0)
		  {
			  retC=fork();
			  printf("Inside Child Process B child process C is created:\n");
			  
			  for(int count=1;count<=5;count++)
			  {
				  printf("child:%d pid=%d count=%d\n",i+1,getpid(),count);
				  sleep(1);
			  }
			  exit(0);
			  if(retC==0)
			  {
				  retD=fork();
				    printf("Inside Child Process C Child Process D is Created :\n");

				  for(int count=1;count<=5;count++)
				  {
					  printf("child:%d pid=%d count=%d\n",i+1,getpid(),count);
					  sleep(1);
				  }
				  exit(0);
			  }
		  }
	  }

	  for(i=0;i<4;i++)
	{
		wait(&status);
				printf("exit status off child = %d\n", WEXITSTATUS(status));
	}

	printf("Parent PID=%d All Proceess are cleaned\n",getpid());
	return 0;
}
