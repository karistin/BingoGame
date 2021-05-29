#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BOARD_SIZE 5

void socket_settings(char *ip, char *port); //소켓의 세팅
void error_check(int validation, char *message); //실행 오류 검사
void login();
int menu();
void sign_up();
int socket_fd; //소켓 파일디스크립터
char ID[30] , pwd[30]; //ID / PWD 저장 
char flag[1];
int turn[4]; //어플리케이션 프로토콜 정의
/*
	turn[0]=플레이어 숫자선택
	turn[1]=클라이언트 빙고 수
	turn[2]=서버 빙고 수
	turn[3]=게임종료여부(0=진행중, 1=클라이언트 승리, 2=서버 승리, 3=무승부)
*/

void main(int argc, char *argv[])
{
	int i, j;
	int menu_value;
	if(argc!=3)
	{
		printf("./실행파일 IP주소 PORT번호 형식으로 실행해야 합니다.\n");
		exit(1);
	}

	
	flag[0] =='0'; 
	
	socket_settings(argv[1], argv[2]);

	system("clear");
	
	
	while(1){
		menu_value =menu();

		if(menu_value == 1)
			login();
		else if (menu_value == 2)
			sign_up();
		else 
			printf("비정상 종료");
		
		if (flag[0] =='1')
		{
			printf("로그인 성공\n");
			break;
		}
	}
	
	
	exit(1);
	printf("빙고게임을 시작합니다.\n");

	

}
void socket_settings(char *ip, char *port)
{
	struct sockaddr_in server_adr;

	socket_fd=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //TCP소켓 생성
	error_check(socket_fd, "소켓 생성");

	memset(&server_adr, 0, sizeof(server_adr)); //구조체 변수 값 초기화
	server_adr.sin_family=AF_INET; //IPv4
	server_adr.sin_port=htons(atoi(port)); //포트 할당
	server_adr.sin_addr.s_addr=inet_addr(ip); //IP 할당

	error_check(connect(socket_fd, (struct sockaddr *)&server_adr, sizeof(server_adr)), "연결 요청");
}
void error_check(int validation, char* message)
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
int menu()
{
	
	int value;//사용자 입력
	int c;//숫자 확인 
	char send[1];//보낼 문자열
	int lens;
	printf("서버 접속을 성공했습니다!!\n");
	
	while(1){
		
		printf("1번 입력시 로그인 \n2번 입력시 회원 가입\n");
		//scanf("%d",&value );
		
		if (!scanf("%d",&value ))
		{
			printf("숫자를 입력해야 됩니다.\n");
			while(c=getchar()!='\n'&& c!=EOF );//버퍼에 남은 값 삭제
		}
		else if((value ==1)||(value ==2))
			break;
		else 
			printf("올바른 숫자를 입력하시오\n");
		
	}
	if(value ==1)
		send[0]='1';//숫자를 문자열로 바꾸어야 한다. 
	else if(value ==2)
		send[0]='2';
	
	
	printf("%s\n", send); 
	lens = write(socket_fd, send, sizeof(send));
	
	error_check(lens , "사용자 메뉴 입력 보내기");
	return value;
}
void login()
{
	int lens;
	
	system("clear");
	//printf("서버 접속을 성공했습니다!!\n");
	printf("=======================\n");
	
	printf("ID를 입력하시오 : ");
	scanf("%s",ID);
	lens = write(socket_fd, ID, sizeof(ID));
	error_check(lens, "로그인 데이터 쓰기");
	printf("PWD를 입력하시오 : ");
	scanf("%s" , pwd);
	lens = write(socket_fd , pwd , sizeof(pwd));
	error_check(lens, "비밀 번호 데이터 쓰기");

	
	
	printf("로그인 확인 중 입니다.\n");
	//sleep(1);
	//연결완료후 로그인 
	//char flag[1]; //login error 0, in 1

	while(1){
		if(sizeof(flag)==sizeof(char))
		{
			lens = read(socket_fd, flag , sizeof(flag));
			break;
		}
	}
	error_check(lens , "로그인 확인 결과");
	printf("%s\n",flag);
	
	if(flag[0] =='1' )
		printf("로그인 성공\n");
	else{
		system("clear");
		printf("로그인 실패\n");
		
	}

}
void sign_up()
{
	int lens;
	system("clear");
	//printf("서버 접속을 성공했습니다!!\n");
	printf("===========================\n");
	printf("=========회원가입 과정=======\n");
	printf("ID를 입력하시오 : \n");
	scanf("%s",ID);
	lens = write(socket_fd, ID, sizeof(ID));
	error_check(lens, "회원가입 아이디 데이터 쓰기");
	
	printf("PAWORD를 입력해 주세요 \n");
	scanf("%s",pwd);
	lens = write(socket_fd , pwd , sizeof(pwd));
	error_check(lens, "회원가입 비밀번호 데이터 쓰기");	
}
