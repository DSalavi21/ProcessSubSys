#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
 int flag=0;
 char Arr[256],Brr[256],buffer[sizeof(int)];
 int fd1,ret1,fd2,ret2,countfd,ret;
 int cap1=0,cap2=0;
 char *val1, *val2 ;
 printf("Parent Process\n");
 
 countfd=creat(argv[3],0x777);
 if(countfd == -1)
 {
	printf("Unable to create file : already exist\n");
 }
 else
 {
  if(fork()==0)
  {
	printf("\nProcess_1\n");
	flag=1;
		fd1=open(argv[1],O_RDONLY);
		if(fd1==-1)
			printf("Can't open file %s \n",argv[1]);
	
		else
		{
		printf("file \"%s\" opened with fd = %d\n",argv[1],fd1);
		while((ret1=read(fd1,Arr,sizeof(Arr)))!=0)
		{
		  ret1--;
	 	  while(ret1>=0)
	 	  {	
			if((Arr[ret1]>='A')&&(Arr[ret1]<='Z'))
			{
		  	 cap1++;
			}
		   ret1--;
	 	  }
		  memset(Arr,0,sizeof(Arr));
		}
		printf("cap1 = %d\n",cap1);
		sprintf(val1,"%d",cap1);
		write(countfd,val1,sizeof(val1));
		printf("file \"%s\" is Closed\n",argv[1]);
		close(fd1);
		}

	if(fork()==0)
	 {
	  printf("\nProcess_2\n");
	  flag=0;
		fd2=open(argv[2],O_RDONLY);
		if(fd2==-1)
			printf("Can't open file %s \n",argv[2]);
	
		else
		{
		printf("file \"%s\" opened with fd = %d\n",argv[2],fd2);
		while((ret2=read(fd2,Brr,sizeof(Brr)))!=0)
		{
		  ret2--;
	 	  while(ret2>=0)
	 	  {	
			if((Brr[ret2]>='A')&&(Brr[ret2]<='Z'))
			{
		  	 cap2++;
			}
		   ret2--;
	 	  }
		  memset(Brr,0,sizeof(Brr));
		}
		printf("cap2 = %d\n",cap2);
		printf("current offset = %d\n",lseek(countfd,0,SEEK_CUR));
		sprintf(val2,"%d",cap2);
		write(countfd,val2,sizeof(val2));
		printf("file \"%s\" is Closed\n",argv[2]);
		close(fd2);
		}
	  }
	
	if(flag==1)
	{
	  printf("Wait call by Process_1\n");
	  wait(10);
	}

	if(flag==0)
	{
	  printf("\nProcess_2 Terminated\n");
	  exit(0);
	}
	flag=1;
  }

  if(flag==0)
  {
   printf("Wait call by Parent\n");
   wait(10);
  }

  if(flag==1)
  {
   printf("Process_1 Terminated\n");
   exit(0);
  }


 
 close(countfd);
 }


printf("Parent Terminated\n");

return 0;
}


/*	OUTPUT

// ./myexe demo.txt hello.txt count.txt

Parent Process
Wait call by Parent

Process_1
file "demo.txt" opened with fd = 4
cap1 = 9
file "demo.txt" is Closed
Wait call by Process_1

Process_2
file "hello.txt" opened with fd = 4
cap2 = 10
current offset = 8
file "hello.txt" is Closed

Process_2 Terminated
Process_1 Terminated
Parent Terminated



*/
