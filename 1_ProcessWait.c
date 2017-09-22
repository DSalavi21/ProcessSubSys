// program in which parent process waits till its child process terminates


#include<stdio.h>
#include<unistd.h>

int main()
{
 int flag=0;
 printf("Parent\n");

  if(fork()==0)
  {
	printf("Child\n");
	flag=1;
  }

if(flag==0)
{
	printf("Wait call by parent\n");
	wait(10);
}

	if(flag==1)
	{
	  printf("Child ends\n");
	  exit(0);
	}
printf("Parent ends\n");

return 0;
}

/*	OUTPUT
Parent
Wait call by parent
Child
Child ends
Parent ends
*/
