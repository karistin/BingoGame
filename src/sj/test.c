#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <arpa/inet.h>
#include <signal.h>
void print_msg();
int a=6; // global 


void read_childproc(int sig){
	int status;
	pid_t id = waitpid(-1, &status, WNOHANG);
	
	if (WIFEXITED(status)){
		printf("kill\n");
	}
}

int main ()
{
	
	
	// char a[20]="ksj";
	// char b[20]="kakak";
	// char c[20]="ksj";
	
	// if(!strcmp(a,b))
	// 	printf("a와 b 같음 ");
	// if(!strcmp(b,c))
	// 	printf("b와 c 같음 ");
	// if(!strcmp(a,c))
	// 	printf("a와 c 같음 ");
	
	// int sk = 10;
	// char a[1];
	
	// printf("%s", itoa(sk , a , 10));
	
	
	
	// int fp;
	
	// FILE* fp = fopen("data.txt","rw");
	// if(fp==NULL)
	// 	printf("연결 실패");
	// fputs("\n Hello World!" , fp);
	
	
// 	 FILE *fp = fopen("data.txt", "a");    // hello.txt 파일을 쓰기 모드(w)로 열기.
//                                            // 파일 포인터를 반환
// 	char *a ="난나나나나나나나나나난";
//     fputs(a, fp);   // 파일에 문자열 저장

//     fclose(fp);    // 파일 포인터 닫기

//     return 0;
	
	// int b =0;
	// int status;
	
	// pid_t pid;
	
	// b = 88;
	
	// printf("Before fork\n");
	
	// pid = fork();
	
	// printf("This is the pid value :: %d  // %d \n" , pid ,getpid());
	
	// if(pid == 0)
	// {
	// 	a++;b++;
		
	// 	printf("This is the child and the test number is %d %d // %d\n" ,a ,b ,getpid());
		
		
	// }
	
	// else 
	// {
	// 	wait(&status);
		
	// 	printf("This is the parent and the test number is %d %d // %d \n" , a,b,getpid());
	// }
	
	// return 0;
		
	// //전역 변수는 포크시 만들어감 다만 내용의 변화는 서로 다르다. 
	
	pid_t pid;
	
	struct sigaction act;
	act.sa_handler = read_childproc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	
	
	printf("부모 PID : %d \n" ,getpid());
	pid = fork();
	
	if(pid == 0)
	{
		
		sleep(5);
		printf("자식 PID %d\n" ,getpid());
		return 0;
	}
	
	else 
	{
		printf("1\n");
		if(sigaction(SIGCHLD, &act, 0))
			print_msg();
		printf("2\n");
		printf("3\n");
		//if(!signal(SIGALRM , print_msg()))
		//print_msg();
		
		
		
	}

}

void print_msg()
{
	printf("자식이 종료되었습니다.");
	
}