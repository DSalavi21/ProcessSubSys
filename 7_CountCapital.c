#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
 int flag=0;
 char Arr[256],Brr[256];
 int fd1,ret1,fd2,ret2,countfd;
 int cap1=0,cap2=0;
 char *val1, *val2 ;
 printf("Parent Process\n");

  if(fork()==0)
  {
	printf("Process_1\n");
	flag=1;
		fd1=open(argv[1],O_RDONLY);
		if(fd1==-1)
			printf("Can't open file %s \n",argv[1]);
	
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
		}
		close(fd1);

	if(fork()==0)
	 {
	  printf("Process_2\n");
	  flag=0;
		fd2=open(argv[2],O_RDONLY);
		if(fd2==-1)
			printf("Can't open file %s \n",argv[2]);
	
		while((ret2=read(fd2,Brr,sizeof(Brr)))!=0)
		{
		  ret2--;
	 	  while(ret2>=0)
	 	  {	
			if((Arr[ret2]>='A')&&(Arr[ret2]<='Z'))
			{
		  	 cap2++;
			}
		   ret2--;
	 	  }
		}
		close(fd2);
	  }
	
	if(flag==1)
	{
	  printf("Counting characters from %s\n",argv[1]);
	  printf("Wait call by Process_1\n");
	  wait(10);
	}

	if(flag==0)
	{
	  printf("Counting characters from %s\n",argv[2]);
	  printf("Process_2 Terminates\n");
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
  printf("Process_1 Terminates\n");
  exit(0);
}


	countfd=creat(argv[3],0x777);
	if(countfd == -1)
	{
		printf("Unable to create file : already exist\n");
	}
	else
	{
		printf("%s File is successfully created with file descriptor %d \n",argv[3],countfd);
		sprintf(val1,"%d",cap1);
		sprintf(val2,"%d",cap2);
		  write(countfd,val1,sizeof(val1));
		  write(countfd,val2,sizeof(val2));

		close(countfd);
	}


printf("Process_1 Terminates\n");

return 0;
}


/*	OUTPUT

// ./myexe demo.txt hello.txt count.txt

Parent Process
Wait call by Parent
Process_1
Counting characters from demo.txt
Wait call by Process_1
Process_2
Counting characters from hello.txt
Process_2 Terminates
Process_1 Terminates
count.txt File is successfully created with file descriptor 3 
Process_1 Terminates


*/
