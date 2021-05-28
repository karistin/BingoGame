#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h> //-
#define BOARD_SIZE 5
#define BACKLOG 3 //연결대기 큐 숫자
#define CLNT_BUF_SIZE 256 //-
#define MSG_SIZE 100

void socket_settings(char *port); //소켓의 세팅
void error_check(int validation, char *message); //실행 오류 검사
void client_game_init(); //클라이언트 빙고판 생성
void * client_game_init2(void * arg);

int server_board[BOARD_SIZE][BOARD_SIZE]; //서버 보드판 배열
int client_board[BOARD_SIZE][BOARD_SIZE]; //클라이언트 보드판 배열
int check_number[BOARD_SIZE*BOARD_SIZE+1]={0}; //중복검사용 배열
int server_fd, client_fd; //소켓 파일디스크립터

int clnt_buf [CLNT_BUF_SIZE];
int clnt_count = 1;
pthread_mutex_t mutx;
int child_clnt_buf [2];
int clnt_real_count = 0;
int test = 0; // test용 나중에 삭제해

pthread_t t_id[2];

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
	pid_t pid = 1;
	pthread_mutex_init(&mutx, NULL);
	server_fd=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //TCP 소켓 생성
	error_check(server_fd, "소켓 생성");

	memset(&client_adr, 0, sizeof(client_adr)); //구조체 변수 값 초기화
	memset(&server_adr, 0, sizeof(server_adr)); //구조체 변수 값 초기화
	server_adr.sin_family=AF_INET; //IPv4
	server_adr.sin_port=htons(atoi(port)); //포트 할당
	server_adr.sin_addr.s_addr=htonl(INADDR_ANY); //IP주소 할당
	
	
	error_check(bind(server_fd, (struct sockaddr *)&server_adr,sizeof(server_adr)), "소켓주소 할당"); //주소 바인딩
	error_check(listen(server_fd, BACKLOG), "연결요청 대기");

	
	while (1){
		client_adr_size=sizeof(client_adr);
		client_fd=accept(server_fd, (struct sockaddr *)&client_adr, &client_adr_size); //특정 클라이언트와 데이터 송수신용 TCP소켓 생성
		printf("* %s:%d의 연결요청\n", inet_ntoa(client_adr.sin_addr), ntohs(client_adr.sin_port));
		error_check(client_fd, "연결요청 승인");
		
		clnt_buf[clnt_count % CLNT_BUF_SIZE] = client_fd;
		clnt_count ++;
		clnt_real_count ++;
		// user over 2 waiting
		if(clnt_real_count >= 2){
			if( pid != 0 )pid = fork();
		
			// child_process
			if (pid == 0){
				close(server_fd);
				child_clnt_buf[0] = clnt_buf[clnt_count - 2];
				child_clnt_buf[1] = clnt_buf[clnt_count - 1];
				
				test = 1;
				for (int i = 0; i < 2 ; i ++){
				//	write(child_clnt_buf[i], "connect with other clinet\n", 28);
					pthread_create(&t_id[i], NULL, client_game_init2 , (void *) &child_clnt_buf);
					sleep(1);
					// mutex 해야됨 (동기화 문제 발생 가능)
					test ++ ;
				}
				pthread_join(t_id[0], NULL);
				pthread_join(t_id[1], NULL);
				
				return;
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
	}
	
}


