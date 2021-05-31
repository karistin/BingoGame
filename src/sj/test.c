#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <arpa/inet.h>
#include <signal.h>
void print_msg();

void print_account(int peo_num); 
int get_account(FILE * fp);

typedef struct people_information{
	char name[30];
	char pwd[30];
	int lg_in;//1는 로그인중 0는 로그아웃 
}people_info;


int a=6; // global 
people_info people[100];


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
	
	/*
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
	*/
	
	FILE *fp =fopen("data.txt","rw");
	int peo_num;
	
	
	char buffer[1001]; 
	char setn[1]="1";
	int pos =0;
	// for(int i=0; i<pos; i++)
	// 	fgets(buffer, 1001, fp);//전부 읽어오기  
	fseek(fp , 7 , SEEK_SET);
	fputs(setn , fp);
	//fwrite("1", sizeof(char) , 1,fp );
	
	

	// peo_num = get_account(fp);
	// print_account(peo_num);

// 	char buffer[1001],*token;
// 	int i=0;
// 	int idx = 0;
	
// 	fgets(buffer, 1001, fp);
	
// 	printf("buffer :%s\n" , buffer);
// 	token = strtok(buffer, " ");
//     while (token!=NULL)               // 자른 문자열이 나오지 않을 때까지 반복
//     {
        
// 		printf("%s\n", token);   // 자른 문자열 출력
// 		if (i == 0) {
// 			strcpy(people[idx].name, token);
// 		}
// 		else if (i == 1) {
// 			strcpy(people[idx].pwd, token);
// 		}
// 		else if(i==2){
// 			people[idx].lg_in =atoi(token);
// 		}
// 		i++;
		
//         token = strtok(NULL, " ");      // 다음 문자열을 잘라서 포인터를 반환
// 	}
// 	printf("%s %s %d \n", people[0].name, people[0].pwd ,people[idx].lg_in );
	
}

int get_account(FILE * fp) //data.txt에서 데이터를 읽어옴 
{		
	char buffer[1001],*token; 
 
    int i=0;
    int idx = 0;
    while (!feof(fp)) {
        i = 0;//i초기화
        fgets(buffer, 1001, fp);//전부 읽어오기  
		printf("buffer :%s\n" , buffer);
        token = strtok(buffer, " "); // 스페이스 기준으로 짜르기 
		//printf("before :%s\n" , token);
        while (token != NULL) {
 
            if (i == 0) {
                strcpy(people[idx].name, token);
            }
            else if (i == 1) {
                strcpy(people[idx].pwd, token);
            }
			else if(i==2){
				people[idx].lg_in =atoi(token);
			}
			// else if(token = "\0"){
			// 	break;
			// }
            i++;
            token = strtok(NULL, " ");
			//printf("after :%s\n" , buffer);
        }
        idx++;
    }
	
	fclose(fp); // 파일 닫기
	return idx;
}
void print_account(int peo_num) //data.txt에서 데이터 print
{
	for (int i = 0; i < peo_num; i++) {
		//if(i<peo_num-1)
			//people[i].lg_in[strlen(people[i].pwd) - 1] = '\0';//enter 개행 문자 제거
		//읽은 내용이 잘 저장됐는지 출력
        printf("%s %s %d\n", people[i].name, people[i].pwd, people[i].lg_in);
    }
}
void print_msg()
{
	printf("자식이 종료되었습니다.");
	
}