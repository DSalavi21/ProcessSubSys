// This program demonstates directory file handling
// responsible to write all file names which are present on Desktop in demo file which should be created newly.


#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>

int main(int argc,char *argv[]) 
{
	int fd,ret,ret1,ret2;
	char ch1;
	char buff[256];	
	DIR *dir;
	struct dirent *entry;

	if ((dir = opendir("/home/suraj/Desktop")) == NULL)
	{
		printf("Unable to open specified directory\n");
		return -1;
	}
		// opendir() system call opens directory and returns pointer to DIR structure
		// opendir() accept only one parameter that is name of the directory to be open

	fd = creat("demo.txt",0x777);	// 0x777 : "rwx rwx rwx" (permissions of user, owner, group)

	if(fd == -1)
	{
		printf("Unable to create file : already exist\n");
	}
	else
	{
		printf("\"demo.txt\" File is successfully created with file descriptor %d \n",fd);

		while ((entry = readdir(dir)) != NULL)
		{
		  ret1 = write(fd,entry->d_name,sizeof(buff));
		  memset(buff,0,sizeof(buff));
		}
		// readdir() system call returns NULL when it reach end of the directory
		// closedir() close the directory which is opened by opendir()	
		close(fd);
	}
	

	printf("Want to read contents from this file ? ( y / n ) : ");
	scanf("%c",&ch1);
	if(ch1=='y')
	{
		fd = open("demo.txt",O_RDONLY);

		while((ret2 = read(fd,buff,sizeof(buff))) != 0)	
		{
		  printf("%s\n",buff);
		}
	}
	close(fd);
	
	// remove("demo.txt");		//
	closedir(dir);
return 0;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
/*	OUTPUT

// gcc WriteFile.c -o myexe
// ./myexe

//////////////////////////////////////////////////////////////////////////////////////////////////////////

"demo.txt" File is successfully created with file descriptor 4 
Want to read contents from this file ? ( y / n ) : y
.
Assignment 3(Process)
1000 Linux Command Tutorials - Sanfoundry_files
MOS_Assignments.zip
..
1000 Linux Command Tutorials - Sanfoundry.html
NPAT Problems
Multi-OS-Marvellous
bhal.c


*/
