#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<string.h>
#include<dirent.h>
void recursive_dir_list(char *dirpath);
int main(int argc,char *argv[])
{
	char *dirpath;
	struct  stat st;
	if(argc != 2)
	{
		printf("Directory path is not mentioned....\n");
		printf("Run as: %s<dir path>\n",argv[0]);
		exit(1);
	}
	dirpath=argv[1];
	recursive_dir_list(dirpath);
	return 0;
}

void recursive_dir_list(char *dirpath)
{
	DIR *dp=NULL;
	struct dirent *ent;
	dp=opendir(dirpath);
	if(dp==NULL)
	{
		printf("%s directory is not opened....\n",dirpath);
		return;
	}
	printf("Directory Content: \n");
	while((ent=readdir(dp))!=NULL)
	{
		if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0)
		{
			continue;
		}
		else{
			if(ent->d_type==DT_DIR)
			{
				printf("DIR: %s\n",ent->d_name);
				strcat(dirpath,"/");
				strcat(dirpath,ent->d_name);
				printf("---------------------------------------------------------\n");
				recursive_dir_list(dirpath);
				printf("---------------------------------------------------------\n");
			}
			else
				printf("%s\n",ent->d_name);
		}
	}
	closedir(dp);
}

