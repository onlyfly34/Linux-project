#include <linux/sched.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#define  REPEAT_TIME      10
#define  MEMORY_SIZE      900000

main()
{	int    i,pid;
  	char   result[MEMORY_SIZE];
	int    j;
  	// Definition of other varialbes you need to use in your program

  	// Your initialization code
	//printf("%d \n", getpid());
  	printf("Input the PID of the process that you want to observe:");
  	scanf("%d", &pid);
	//printf("%d\n", pid);
  	/*for(i=0;i<REPEAT_TIME;i++)
  	{
    		linux_survey_TT(pid,result);

    		// Code to process results contained in rslt[5000]

    		sleep(120);
  	}*/
    		// Code to report the final results
	syscall(351, pid, result);

	for(j = 0; result[j] != '\0';j++)
	{
	  printf("%c", result[j]);
	}

}
