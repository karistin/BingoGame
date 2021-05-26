#include <sys/types.h>
#include <sys/times.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
# define CLK_TCK sysconf(_SC_CLK_TCK)

int count = 0;
void* time_test (){

	int i = 0;
	
	while (count < 100000000){
		(void)getpid();
		count++;
	}
}


int main (int argc, char * argv []){
	int repeat = atoi(argv[1]);
	int count = atoi(argv[2]);
	int tmp = repeat/count;
	
	time_t t;
	struct tms mytms;
	clock_t t1, t2;

	pthread_t * t_id = (pthread_t)malloc(sizeof(pthread_t) * count);
	

	if ((t1 = times(&mytms)) == -1){ 
		perror("times 1");
		exit(1);
	}

	for (int i = 0; i < count; i ++){
		pthread_create(&(t_id[i]), NULL, time_test, NULL);
	}

	for (int j = 0 ; j < count ; j++){
		pthread_join(t_id[j], NULL);
	}
	if ((t2 = times(&mytms)) == -1) {
		perror("times 2");
		exit(1);
	}
	 printf("Real time : %.2f sec\n", (double)(t2 - t1) / CLK_TCK);
	 printf("User time : %.2f sec\n", (double)mytms.tms_utime / CLK_TCK);
	 printf("System time : %.2f sec\n", (double)mytms.tms_stime / CLK_TCK);
	 return 0;

}
