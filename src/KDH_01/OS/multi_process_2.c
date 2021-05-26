#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <time.h>
#include <limits.h>
#include <sys/mman.h>
#include <sys/wait.h>
#define CLK_TCK sysconf(_SC_CLK_TCK)

int (*g_count) = 0;

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
	
	g_count = mmap(NULL, sizeof *g_count, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	for (int i = 0; i < count ; i ++)
		if(pid != 0) pid = fork();

	if (pid == 0){
		while (*g_count < repeat){
			(void)getpid();
			*g_count += 1;		
		}
	}
	else{
		for (int h = 0 ; h < count ; h ++){
		wait(&status);
		printf("%d\n", *g_count);
		}

		 if ((t2 = times(&mytms)) == -1){
			perror("times2");
			exit(1);
		 }
		printf("Real time : %.2f sec\n", (double) (t2 - t2) / CLK_TCK);
		printf("User time : %.2f sec\n", (double) mytms.tms_utime / CLK_TCK);
		printf("System time : %.2f sec\n", (double) mytms.tms_stime / CLK_TCK);
		printf("Average child uesr time : %.2f sec\n", (double) mytms.tms_cutime / CLK_TCK / count);
		printf("Average child system time : %.2f sec\n", (double) mytms.tms_cstime / CLK_TCK / count);
		return 0 ;
	}

	if ((t2 = times(&mytms)) == -1){
		perror("times2");
		exit(1);
	}

	return 0;

	
	
}
