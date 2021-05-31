#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h> //-
#include <signal.h>

#define BOARD_SIZE 5
#define BACKLOG 3 //연결대기 큐 숫자
#define CLNT_BUF_SIZE 256 //-
#define MSG_SIZE 100

void socket_settings(char *port); //소켓의 세팅
void error_check(int validation, char *message); //실행 오류 검사
void client_game_init(); //클라이언트 빙고판 생성
void * client_game_init2(void * arg);
int get_account(FILE * fp);
void print_account(int peo_num);
void login();
void *menu();
void sign_up(); 
void write_ID_PWD(FILE * fp);
void *ginit();

int server_board[BOARD_SIZE][BOARD_SIZE]; //서버 보드판 배열
int client_board[BOARD_SIZE][BOARD_SIZE]; //클라이언트 보드판 배열
int check_number[BOARD_SIZE*BOARD_SIZE+1]={0}; //중복검사용 배열
int server_fd, client_fd; //소켓 파일디스크립터

int login_buf[CLNT_BUF_SIZE];
int clnt_buf [CLNT_BUF_SIZE];
int clnt_count = 1;
pthread_mutex_t mutx;
int child_clnt_buf [2];
int clnt_real_count = 0;
int test = 0; // test용 나중에 삭제해

pthread_t t_id[2];
pthread_t t_id_t;

int turn[4]; //어플리케이션 프로토콜 정의
/*
	turn[0]=플레이어 숫자선택
	turn[1]=클라이언트 빙고 수
	turn[2]=서버 빙고 수
	turn[3]=게임종료여부(0=진행중, 1=클라이언트 승리, 2=서버 승리, 3=무승부)

*/
int turn_order[1]; // 
/*
	turn_order[0]=턴 순서 1=선공, 2=후공
*/

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
pid_t pid = 1;//getpid 부모 넣기
//int status; // 좀비 종료 
char flag[1]; //로그인 데이터 저장 

typedef struct p_token{
	int p_turn[4];
	char p_msg[MSG_SIZE];
} p_token;

p_token p;

void main(int argc, char *argv[])
{
	int i, j;

	if(argc!=2)
	{
		fprintf(stderr, "./실행파일 port번호 형식으로 입력해야합니다\n");
		exit(1);
	}

	socket_settings(argv[1]);
	printf("빙고게임을 시작합니다.\n");
}

void socket_settings(char *port)
{
	struct sockaddr_in server_adr, client_adr;
	socklen_t client_adr_size;
	
	struct sigaction sa; //시그널 관련 코드 시작
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigaction(SIGCHLD, &sa, NULL); // 시그널 관련 코드 종료

	server_fd=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //TCP 소켓 생성
	error_check(server_fd, "소켓 생성");

	memset(&client_adr, 0, sizeof(client_adr)); //구조체 변수 값 초기화
	memset(&server_adr, 0, sizeof(server_adr)); //구조체 변수 값 초기화
	server_adr.sin_family=AF_INET; //IPv4
	server_adr.sin_port=htons(atoi(port)); //포트 할당
	server_adr.sin_addr.s_addr=htonl(INADDR_ANY); //IP주소 할당
	
	
	error_check(bind(server_fd, (struct sockaddr *)&server_adr,sizeof(server_adr)), "소켓주소 할당"); //주소 바인딩
	error_check(listen(server_fd, BACKLOG), "연결요청 대기");
	
	int index_ = 0;
	pthread_t tmp;
	pthread_create(&tmp, NULL, ginit, NULL);
	while (1){
		
		// user over 2 waiting
		client_adr_size=sizeof(client_adr);
		client_fd=accept(server_fd, (struct sockaddr *)&client_adr, &client_adr_size);
		printf("* %s:%d의 연결요청\n", inet_ntoa(client_adr.sin_addr), ntohs(client_adr.sin_port));
		error_check(client_fd, "연결요청 승인");
		
		pthread_create(&t_id_t, NULL, menu, (void *) &client_fd);
		
		

	}	
	
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


void* client_game_init2(void * arg)
{
	int check_number[BOARD_SIZE*BOARD_SIZE]={0};
	int i, j;
	int array_len;
	int* clnt_buf = (int *) arg;
	int my_num;
	printf("client game init 2 test : %d\n" , test);
	my_num=test;
	
	int my_clnt, other_clnt;
	
	if (my_num == 1){
		my_clnt = clnt_buf[0];
		other_clnt = clnt_buf[1];
	}
	
	else if(my_num == 2){
		my_clnt = clnt_buf[1];
		other_clnt = clnt_buf[0];
	}
	
	else{
		printf("wrong my_num");
	}

//	write(child_clnt_buf[i], msg, sizeof(msg));	
//	srand(time(NULL)+(i*100)); //서버 보드판과 다르게 하기위해 100을 추가
	
	
	srand(time(NULL)+100);
	for(i=0; i < BOARD_SIZE; i++)
	{
		for(j=0; j < BOARD_SIZE; j++)
		{
			while(1)
			{
				int temp = rand()%25; //0~24 난수 발생
			
				if(check_number[temp]==0) //중복제거 알고리즘
				{
					check_number[temp]=1;
					client_board[i][j]=temp+1;
					break;
				}
			}
		}
	}    
		array_len=write(my_clnt, client_board, sizeof(client_board));
		printf("%d 바이트를 전송하였습니다\n", array_len);
		error_check(array_len, "데이터전송");
		turn_order[0] = test;
		array_len=write(my_clnt, turn_order, sizeof(turn_order));
		printf("%d 바이트를 전송하였습니다\n", array_len);
		error_check(array_len, "데이터전송");

	int recv_len=0;//, array_len;
	int recv_count;
	
	
	while(1){
		while (recv_len != sizeof(p)){
			recv_count=read(my_clnt, &p, sizeof(p));
			error_check(recv_count, "데이터수신");
			if(recv_count==0) break;
				printf("%d 바이트: 클라이언트의 턴 정보를 수신하였습니다\n", recv_count);
			recv_len+=recv_count;
		}
		
		array_len=write(other_clnt, &p, sizeof(p));
		printf("%d 바이트: 클라이언트의 턴 정보를 전송하였습니다\n", array_len);
		error_check(array_len, "데이터전송");
		recv_len = 0;
		
		if (p.p_turn[3] != 0){
			
			break;
		}
		
	}
	
	while (recv_len != sizeof(ID)){
		recv_count=read(my_clnt, &ID, sizeof(ID));
		error_check(recv_count, "데이터수신");
		if(recv_count==0) break;
		printf("%d 바이트: 클라이언트의 ID 정보를 수신하였습니다\n", recv_count);
		recv_len+=recv_count;
	}
	
	FILE* fp = fopen("data.txt","rw");
	
	
	
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

void * menu(void* arg) //사용자에게 물어봄 
{
	int clnt = *((int*) arg);
	while(1){
		int lens;
		char send[1];
		while(1){
			if(sizeof(send)==sizeof(char))
			{
			lens = read(clnt,send,sizeof(send));
			error_check(lens , "사용자 메뉴 입력 읽기");
			break;
			}
		}
		printf("%s\n", send);
	
		if(send[0]=='1')
			login(clnt);
		else if(send[0]=='2')
			sign_up(clnt);
		else
			printf("메뉴 에러");
		
		if(flag[0] =='1'){
			printf("로그인 성공\n");
			flag[0] = '0';
			break;
		}
		
	}	
	return NULL;
}

void sign_up(int clnt) // 사용자가 회원 가입 
{
	
	//int status; 좀비 프로세스 삭제 과정 필요 
	int lens;
	while(1){
		if(sizeof(ID)==30)
		{
			lens = read(clnt, ID, sizeof(ID));
			//printf("%d",lens);
			error_check(lens, "회원가입 데이터 읽기");
			printf("ID : %s\n",ID);
			break;
		}
	}
	
	
	while(1){
		if(sizeof(ID)==30)
		{
			lens = read(clnt, pwd , sizeof(pwd));
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
void login(int clnt) // 사용자의 로그인 과정 
{
	int lens;
	//char flag[1];//login error 0, in 1
	//flag[0] ='0';
		//연결완료후 로그인

	lens = read(clnt, ID, sizeof(ID));
		//printf("%d",lens);
	error_check(lens, "로그인 데이터 읽기");

	printf("ID : %s\n",ID);
	lens = read(clnt, pwd , sizeof(pwd));
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
					printf("================================\n");
					lens = write(clnt, flag, sizeof(flag));
					error_check(lens , "로그인 결과 전송");
					people[i].lg_in =1; //텍스트에 접근하여 고치기 
					
					clnt_buf[clnt_count % CLNT_BUF_SIZE] = clnt;
					clnt_count ++;
					clnt_real_count ++;
					printf("clnt count: %d\n", clnt_real_count);
					return;
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
	return;
	
}


void *ginit(){
	while(1){
		
		if(clnt_real_count >= 2){
			printf("clnt_real_count : %d\n" , clnt_real_count);
			if( pid != 0 )pid = fork();

				// child_process
			if (pid == 0){
				//close(server_fd);
				child_clnt_buf[0] = clnt_buf[clnt_count - 2];
				child_clnt_buf[1] = clnt_buf[clnt_count - 1];

				test = 1;
				for (int i = 0; i < 2 ; i ++){
				//	write(child_clnt_buf[i], "connect with other clinet\n", 28);
						
					//printf("client game init 2 test : %d\n" , test);
					pthread_create(&t_id[i], NULL, client_game_init2 , (void *) &child_clnt_buf);
					sleep(1);
					// mutex 해야됨 (동기화 문제 발생 가능)
					test ++ ;
					
				}
				
				pthread_join(t_id[0], NULL);
				pthread_join(t_id[1], NULL);
				return NULL;
			}

			// parent_process
			if (pid > 0){
				close(clnt_buf[clnt_count - 2]);
				close(clnt_buf[clnt_count - 1]);
				clnt_real_count -= 2;
			}
				// fork error
			else{
				perror("fork");
				exit(1);
			}
		}
	}
	
	return NULL;
}
