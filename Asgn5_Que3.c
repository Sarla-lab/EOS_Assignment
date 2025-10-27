#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>


int main(void)
{
	int arr[2];
	pipe(arr);

	// who | wc

	int pid1 = fork();
	if(pid1 == 0)
	{
		// writer
		close(arr[0]);
		
		// output redirection
		dup2(arr[1], 1);
		close(arr[1]);

		execl("/usr/bin/who", "who", NULL);
	}

	int pid2 = fork();
	if(pid2 == 0)
	{
		// reader
		close(arr[1]);
		
		// input redirection
		dup2(arr[0], 0);
		close(arr[0]);

		execl("/usr/bin/wc", "wc", NULL);
	}

	close(arr[0]);
	close(arr[1]);
	int s;
	for(int i = 0 ; i < 2 ; i++)
		wait(&s);

	return 0;
}












