#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>

int main(int argc,char *argv[])
{
	char *dirpath;
	DIR *dp;
	struct dirent *ent;
	struct stat st;

	if(argc !=2)
	{
		printf("Directory Path not mentioned,,,\n");
		printf("Run as: %s <dir path>\n",argv[0]);
		exit(1);

	}

	dirpath=argv[1];
	chdir(dirpath);

	dp=opendir(dirpath);
	if(dp==NULL)
	{
		printf("Directory is not opened!!!\n");
		exit(1);
	}

	printf("Directory content : \n");
	while((ent=readdir(dp))!=NULL)
	{
		stat(ent->d_name,&st);
		printf("%u %u %lu %u %u %u %s\n",ent->d_type, st.st_mode, st.st_nlink, st.st_uid, st.st_gid, st.st_size, ent->d_name);
	}
	closedir(dp);
	return 0;
}
