// program which creates new process which is responsible to write all file names, which are present on Desktop,
// in demo file which should be created newly.

#include<stdio.h>
#include<unistd.h>

int main()
{
int status;
pid_t pid;

	if(fork() == 0)
	{
		printf("Inside Child Process\n");
		execl("./myexe",NULL,NULL);         // executable of WriteFile.c -> myexe
		
	}
	else
	{
		printf("Inside Parent process\n");
		pid = wait(&status);

		printf("Child process having PID %d terminates with exit status %d\n",pid,status);
		printf("Execution of parent process completed\n");
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*	OUTPUT
// gcc 6_Program.c
// ./a.out

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
Inside Parent process
Inside Child Process

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

Child process having PID 5268 terminates with exit status 0
Execution of parent process completed


*/
