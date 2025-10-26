#include<stdio.h>
#include<unistd.h>
int main()
{
	int ret,count=0;
	printf("Program Started\n");
	while(1)
	{
		ret=fork();
		if(ret==-1)
		{
			printf("fork() is failed\n");
			_exit(0);
		}

		else if(ret==0)
		{
			for(int i=1;i<=5;i++)
			{
				sleep(1);
			}
			_exit(0);
		}
		else
		{
			count++;
			printf("Process count =%d\n",count);
		}
	}


	printf("Program finished\n");
	return 0;
}
