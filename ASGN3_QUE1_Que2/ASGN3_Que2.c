#include<stdio.h>

#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	int status ,pid;
	pid=fork();
	if(pid==0)
	{
		execlp("gcc", "gcc" , "-c","circle.c",NULL);
		perror("execlp circle");
		exit(1);
	}
	wait(&status);
	if(WEXITSTATUS(status) !=0)
	{
		printf("circle.c cmpilation failed!!!\n");
		exit(1);
	}

	printf("circle.c compiled successfully!!!\n");

	pid=fork();

	if(pid==0)
	{
		execlp("gcc","gcc","-c","square.c",NULL);
		perror("execlp square");
		exit(1);
	}
	wait(&status);
	if (WEXITSTATUS(status)!=0)
	{
		printf("square.c compilation failed!!!\n");
		exit(1);
	}
	printf("square.c compiled successfully\n");

	pid=fork();

	if(pid==0)
	{
		execlp("gcc","gcc","-c","rectangle.c",NULL);
		perror("execlp rectangle");
		exit(1);
	}
	wait(&status);
	if (WEXITSTATUS(status)!=0)
	{
		printf("rectangle.c compilation failed!!!\n");
		exit(1);
	}
	printf("rectangle.c compiled successfully\n");


	pid=fork();

	if(pid==0)
	{
		execlp("gcc","gcc","-c","main.c",NULL);
		perror("execlp main");
		exit(1);
	}
	wait(&status);
	if (WEXITSTATUS(status)!=0)
	{
		printf("main.c compilation failed!!!\n");
		exit(1);
	}
	printf("main.c compiled successfully\n");


	pid=fork();
	if(pid==0)
	{
		execlp("gcc","gcc","-o","program.out","circle.o","square.o","rectangle.o","main.o",NULL);
		perror("execlp link");
		exit(1);
	}
	printf("Linking Successfull !!! program.out created.\n");


	pid=fork();
	if(pid==0)
	{
		execl("./program.out","./program.out",NULL);
		perror("execl run");
		exit(1);
	}

	wait(&status);
//	printf("program.out exited with status %d \n",WEXITSTATUS(status));



	return 0;
}
