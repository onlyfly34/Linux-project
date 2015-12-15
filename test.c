#include <linux/sched.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#define  REPEAT_TIME      10
#define  MEMORY_SIZE      700000

main()
{	/*int    i,pid;
  	char   result[MEMORY_SIZE];
  	// Definition of other varialbes you need to use in your program

  	// Your initialization code
  	printf("Input the PID of the process that you want to observe:");
  	scanf("%d", &pid);
  	for(i=0;i<REPEAT_TIME;i++)
  	{
    		linux_survey_TT(pid,result);

    		// Code to process results contained in rslt[5000]

    		sleep(120);
  	}*/
    		// Code to report the final results
    	int pause = 123;
    	int pause1 = 212;
    	printf("%d", getpid());
    	scanf("%d",&pause1);
    	syscall(351,getpid());

	system("pause");
	scanf("%d",&pause);
	printf("A%d" ,pause1);
}
