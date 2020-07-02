
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#define TEST_SIZE 2048
 
typedef struct _BOX
{
	int  flag;
	char szMsg[TEST_SIZE];
}Box;
 
int main()
{
	int shmid = shmget((key_t)1234, sizeof(Box), 0666|IPC_CREAT);
	void *shm = shmat(shmid, 0, 0);
	Box *pBox = (Box*)shm;
	
	int tmp;
	memcpy(&tmp, (void *)&shm, 4);
	printf("%d\n",tmp);
 	
	if(shm > (void *)0)
	{
		printf("success\n");
	}
	else if(shm == (void *)-1)
	{
		printf("error\n");
	}
	
	while(1)
	{
		if(pBox->flag == 1)
		{
			printf("msg from writer is [%s]\n", pBox->szMsg);
			pBox->flag = 0;
		}
	}
	
	shmdt(shm);
	shmctl(shmid, IPC_RMID, 0);
	return 0;
}
