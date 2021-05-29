#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>

#define BACKLOG 3 //연결대기 큐 숫자

void socket_settings(char *port); //소켓의 세팅
void error_check(int validation, char *message); //실행 오류 검사
int get_account(FILE * fp);
void print_account(int peo_num);
void login();
void menu();
void sign_up(); 
void write_ID_PWD(FILE * fp);


int server_fd, client_fd; //소켓 파일디스크립터
typedef struct people_information{
	char name[30];
	char pwd[30];
	int lg_in;//1는 로그인중 0는 로그아웃 
}people_info;
people_info people[100]; //최대 100명 구조체 배열 

int peo_num;

//int fp;// ID , PWD 파일 디스크립터
//FILE *fp;
char ID[30] , pwd[30]; //ID , PWD 저장 
int turn[4]; //어플리케이션 프로토콜 정의
pid_t pid;//getpid 부모 넣기
//int status; // 좀비 종료 
char flag[1]; //로그인 데이터 저장 


void main(int argc, char *argv[])
{
	int i, j;
	if(argc!=2)
	{
		fprintf(stderr, "./실행파일 port번호 형식으로 입력해야합니다\n");
		exit(1);
	}

	
			
	flag[0] ='0';
	FILE* fp = fopen("data.txt","rw");
	if(fp == NULL)
	 	printf("fail to read file");
	printf("account success\n");
	
	for (int i = 0; i < peo_num; i++){
		people[i].lg_in =0;
	}
	
	peo_num = get_account(fp); // 데이터 접근 

	print_account(peo_num);
	

	
	
	pid = getpid();	


	printf("부모 pid : %d\n" , pid);
	
	
	
	
	socket_settings(argv[1]);
	
	

}
int get_account(FILE * fp) //data.txt에서 데이터를 읽어옴 
{		
	char buffer[1001],*token; 
 
    int i=0;
    int idx = 0;
    while (!feof(fp)) {
        i = 0;//i초기화
        fgets(buffer, 1001, fp);//전부 읽어오기  
        token = strtok(buffer, " "); // 스페이스 기준으로 짜르기 
        while (token != NULL) {
 
            if (i == 0) {
                strcpy(people[idx].name, token);
            }
            else if (i == 1) {
                strcpy(people[idx].pwd, token);
            }
            i++;
            token = strtok(NULL, " ");
        }
        idx++;
    }
	
	fclose(fp); // 파일 닫기
	return idx;
}
void print_account(int peo_num) //data.txt에서 데이터 print
{
	for (int i = 0; i < peo_num; i++) {
		if(i<peo_num-1)
			people[i].pwd[strlen(people[i].pwd) - 1] = '\0';//enter 개행 문자 제거
		//읽은 내용이 잘 저장됐는지 출력
        printf("%s %s %d\n", people[i].name, people[i].pwd, people[i].lg_in);
    }
}
void socket_settings(char *port) //네트워크 연결 후 자식 포켓 
{
	struct sockaddr_in server_adr, client_adr;
	socklen_t client_adr_size;

	
	server_fd=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //TCP 소켓 생성
	error_check(server_fd, "소켓 생성");

	memset(&client_adr, 0, sizeof(client_adr)); //구조체 변수 값 초기화
	memset(&server_adr, 0, sizeof(server_adr)); //구조체 변수 값 초기화
	server_adr.sin_family=AF_INET; //IPv4
	server_adr.sin_port=htons(atoi(port)); //포트 할당
	server_adr.sin_addr.s_addr=htonl(INADDR_ANY); //IP주소 할당

	error_check(bind(server_fd, (struct sockaddr *)&server_adr,sizeof(server_adr)), "소켓주소 할당"); //주소 바인딩
	error_check(listen(server_fd, BACKLOG), "연결요청 대기");

	while(1){
		
		client_adr_size=sizeof(client_adr);

		client_fd=accept(server_fd, (struct sockaddr *)&client_adr, &client_adr_size); //특정 클라이언트와 데이터 송수신용 TCP소켓 생성
		printf("* %s:%d의 연결요청\n", inet_ntoa(client_adr.sin_addr), ntohs(client_adr.sin_port));
		error_check(client_fd, "연결요청 승인");
		
		// if(client_fd ==-1)
		// 	continue;
		// else 
		// 	puts("새로운 사용자 접속");
		
		if(pid != 0){
			pid = fork();//부모	
			// wait(&status);
			// if(WIFEXITED(status))
			// 	printf("좀비 종료 성공적 \n");
		}
		if(pid == -1)
		{
			close(client_fd);
			continue;
		}
		if(pid == 0)
		{
			close(server_fd);
			menu();
			
		}
	}
}
void error_check(int validation, char* message) //에러 체크 
{
	if(validation==-1)
	{
		fprintf(stderr, "%s 오류\n", message);
		exit(1);
	}
	else
	{
		fprintf(stdout, "%s 완료\n", message);
	}
}
void menu() //사용자에게 물어봄 
{
	
	while(1){
		int lens;
		char send[1];
		while(1){
			if(sizeof(send)==sizeof(char))
			{
			lens = read(client_fd,send,sizeof(send));
			error_check(lens , "사용자 메뉴 입력 읽기");
			break;
			}
		}
		printf("%s\n", send);
	
		if(send[0]=='1')
			login();
		else if(send[0]=='2')
			sign_up();
		else
			printf("메뉴 에러");
		
		if(flag[0] =='1'){
			printf("로그인 성공\n");
			break;
		}
		
	}
	
	
	exit(1);
}
void sign_up() // 사용자가 회원 가입 
{
	
	//int status; 좀비 프로세스 삭제 과정 필요 
	int lens;
	while(1){
		if(sizeof(ID)==30)
		{
			lens = read(client_fd, ID, sizeof(ID));
			//printf("%d",lens);
			error_check(lens, "회원가입 데이터 읽기");
			printf("ID : %s\n",ID);
			break;
		}
	}
	
	
	while(1){
		if(sizeof(ID)==30)
		{
			lens = read(client_fd, pwd , sizeof(pwd));
			error_check(lens , "비밀번호 쓰기");	
			printf("PWD  : %s\n",pwd);
			break;
		}
	}
	
	FILE* fp = fopen("data.txt","a");
	if(fp == NULL)
	 	printf("fail to read file");
	printf("account success\n");
	
	
	write_ID_PWD(fp); //ID와 PWD는 전역 변수 
	
	
	printf("메모장에 데이터 작성 \n");
	

	fclose(fp);
	//waitpid(pid , &status , WNOHANG ); 
	
	
	
}
void write_ID_PWD(FILE * fp)//사용자의 정보 기록 
{
	fputs("\n", fp);
	fputs(ID, fp);
	fputs(" ", fp);
	fputs(pwd , fp);
}
void login() // 사용자의 로그인 과정 
{
	int lens;
	//char flag[1];//login error 0, in 1
	//flag[0] ='0';
		//연결완료후 로그인

	lens = read(client_fd, ID, sizeof(ID));
		//printf("%d",lens);
	error_check(lens, "로그인 데이터 읽기");

	printf("ID : %s\n",ID);
	lens = read(client_fd, pwd , sizeof(pwd));
	error_check(lens , "비밀번호 쓰기");	
	printf("PWD  : %s\n",pwd);

		//printf("peo_num :%d\n",peo_num);
		//id 확인 
	FILE* fp = fopen("data.txt","rw");
	if(fp == NULL)
	 	printf("fail to read file");
	printf("account success\n");
	
	peo_num = get_account(fp); 
	print_account(peo_num);
	
	//printf("%s\n",people[0].pwd);
		//printf("%d\n",strcmp(people[0].pwd,pwd));
		//printf("%d\n",strcmp(people[1].pwd,pwd));
	for(int i=0; i<peo_num; i++)
	{
		if((strcmp(people[i].name , ID)) == 0)
		{
			if(strcmp(people[i].pwd , pwd) == 0)
			{
				if(people[i].lg_in == 0){
					printf("아이디와 비밀번호 일치\n");
					flag[0] ='1';
					//people[i].lg_in =1; 텍스트에 접근하여 고치기 
				}
				else 
					printf("접속중인 아이디 입니다.\n");
			}
			else
			{
				printf("비밀번호가 다름\n");
			}		
		}
		else
		{
			printf("아이디와 비밀번호가 다름\n");
		}
	}
	printf("================================\n");
	lens = write(client_fd, flag, sizeof(flag));
	error_check(lens , "로그인 결과 전송");
	

	
}

