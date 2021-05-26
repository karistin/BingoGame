#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <time.h>
#include <limits.h>

#define CLK_TCK sysconf(_SC_CLK_TCK)

int main (int argc, char* argv[]){
	int repeat = atoi(argv[1]);
	int count = atoi(argv[2]);
	int status;	
	int child_repeat = repeat/count;
	
	time_t t;
	struct tms mytms;
	clock_t t1, t2;

	char tmp[100];

	sprintf(tmp, "%d", child_repeat);

	pid_t pid = 1;
	char* child_argv[3];
	
	if ((t1 = times(&mytms)) == -1){
		perror("time1");
		exit(1);
	}

	for (int i = 0; i < count ; i ++)
		if(pid != 0) pid = fork();

	if (pid == 0){

		child_argv[0] = "/home/student/cestudent/17/ce17b011/OS/teamProject/time_test";
		child_argv[1] = tmp;
		child_argv[2] = NULL;

		if(execv("/home/student/cestudent/17/ce17b011/OS/teamProject/time_test", child_argv) == -1){
			perror("execv");
			exit(1);
		}
	}

	else{
		for (int h = 0 ; h < count ; h ++){
		wait(&status);
		}
	}

	if ((t2 = times(&mytms)) == -1){
		perror("times2");
		exit(1);
	}

	printf("Real time : %.2f sec\n", (double) (t2 - t2) / CLK_TCK);
	printf("User time : %.2f sec\n", (double) mytms.tms_utime / CLK_TCK);
	printf("System time : %.2f sec\n", (double) mytms.tms_stime / CLK_TCK);
	printf("Average child uesr time : %.2f sec\n", (double) mytms.tms_cutime / CLK_TCK / count);
	return 0 ;

	
	
}
