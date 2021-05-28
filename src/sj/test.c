#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <arpa/inet.h>

void print_msg();
int a=6; // global 
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
	printf("부모 PID : %d \n" ,getpid());
	pid = fork();
	
	if(pid == 0)
	{
		printf("자식 PID %d\n" ,getpid());
		sleep(10);
	}
	
	else 
	{
		//signal(SIGCHLD , print_msg());
		// signal(SIGALRM , print_msg());
		//printf("자식이 종료 되었습니다.\n");
	}
	
	
	return 0;
}

void print_msg()
{
	printf("자식이 종료되었습니다.");
}