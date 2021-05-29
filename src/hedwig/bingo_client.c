#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <ctype.h>
#include <pthread.h> 

#define BOARD_SIZE 5
#define MSG_SIZE 100
void socket_settings(char *ip, char *port); //소켓의 세팅
void error_check(int validation, char *message); //실행 오류 검사
void game_init(); //빙고판 생성
void game_print(int number, int turn_count); //게임진행
bool check_winner();
void send_winner();
void * send_msg(void * arg);
void * recv_msg(void * arg);
	
int bingo_check(int board[][BOARD_SIZE]);
int board[BOARD_SIZE][BOARD_SIZE]; //보드판 배열
int check_number[BOARD_SIZE*BOARD_SIZE+1]={0}; //중복검사용 배열
int socket_fd; //소켓 파일디스크립터

int turn[4]; //어플리케이션 프로토콜 정의
/*
	turn[0]=플레이어 숫자선택
	turn[1]=클라이언트 빙고 수 (선공 빙고수)
	turn[2]=서버 빙고 수	(후공 빙고 수)
	turn[3]=게임종료여부(0=진행중, 1=클라이언트 승리, 2=서버 승리, 3=무승부)

*/
int turn_order[1]; // 
/*
	turn_order[0]= (턴 순서 1=선공, 2=후공)
*/
int now_turn = 0;

int other_turn;

pthread_t re_t, se_t;

typedef struct p_token{
	int p_turn[4];
	char p_msg[MSG_SIZE];
} p_token;


p_token p;

void main(int argc, char *argv[])
{
	int i, j;

	if(argc!=3)
	{
		printf("./실행파일 IP주소 PORT번호 형식으로 실행해야 합니다.\n");
		exit(1);
	}

	socket_settings(argv[1], argv[2]);

	printf("대전 상대를 기다리고 있습니다.\n");
	game_init();
	now_turn = turn_order[0];
	
	if (turn_order[0] == 1){
		other_turn = 2;
	}
	
	else{
		other_turn = 1;
	}
	
	game_print(0, 1);
	
	
	printf("turn main %d\n", now_turn);
	
	pthread_create(&re_t, NULL, recv_msg, NULL);
	pthread_create(&se_t, NULL, send_msg, NULL);
	
	
	pthread_join(re_t, NULL);
	pthread_join(se_t, NULL);
	
	close(socket_fd);

	printf("빙고게임을 종료합니다\n");
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

void game_init()
{
	int i, j; //카운트용 변수
	int recv_len, recv_count;

	recv_len=0;
	while(recv_len!=sizeof(board)) // 패킷이 잘려서 올수도 있으므로 예외처리를 위한 조건문
	{
		recv_count=read(socket_fd, board, sizeof(board));
		error_check(recv_count, "데이터수신");
		if(recv_count==-0) break;
		printf("%d 바이트: board를 수신하였습니다\n", recv_count);
		recv_len+=recv_count;
	}
	
	recv_len=0;
	while(recv_len!=sizeof(turn_order)) // 패킷이 잘려서 올수도 있으므로 예외처리를 위한 조건문
	{
		recv_count=read(socket_fd,turn_order, sizeof(turn_order));
		error_check(recv_count, "데이터수신");
		if(recv_count==-0) break;
		printf("%d 바이트: Turn_order 수신하였습니다\n", recv_count);
		recv_len+=recv_count;
	}
}
void game_print(int number, int turn_count)
{
	int i, j;

	system("clear"); //동적 효과를 위한 화면 초기화
	printf("%c[1;33m",27); //터미널 글자색을 노랑색으로 변경
	
	printf("@------ 클라 빙고판 ------@\n");
	printf("진행 턴수: %d\n", turn_count); 
	printf("+----+----+----+----+----+\n"); 
	for(i=0; i < BOARD_SIZE; i++)
	{
		for(j=0; j < BOARD_SIZE; j++)
		{
			if(board[i][j]==0)
			{
				printf("| ");
				printf("%c[1;31m",27);
				printf("%2c ", 88); 
				printf("%c[1;33m",27);
			}
			else
				printf("| %2d ", board[i][j]); 
		}
		printf("|\n");
		printf("+----+----+----+----+----+\n"); 
	}      
	printf("%c[0m", 27); //터미널 글자색을 원래색으로 변경
	if(turn_count!=0)
	{
		printf("숫자: %d\n", p.p_turn[0]);
		printf("나의 빙고수: %d\n", p.p_turn[turn_order[0]]);
		printf("상대의 빙고수: %d\n", p.p_turn[other_turn]);
	}
}


void send_winner()
{
	int array_len, recv_len=0;	
	array_len=write(socket_fd, &p, sizeof(p));
	printf("%d 바이트: 클라이언트의 승리 정보를 전송하였습니다\n", array_len);
	error_check(array_len, "데이터전송");

}

int bingo_check(int board[][BOARD_SIZE])
{
	int i,j;
	int count=0;
	
	for(i=0; i < BOARD_SIZE; i++)
	{
		for(j=0; j < BOARD_SIZE; j++)
		{
			if(board[i][j]==p.p_turn[0])
				board[i][j]=0; //X표 처리
		}
	}   
	
	for(i=0; i < BOARD_SIZE; i++) //가로
	{
		if(board[i][0]==0&&board[i][1]==0&&board[i][2]==0&&board[i][3]==0&&board[i][4]==0) //가로
		{
			count++;
		}
		if(board[0][i]==0&&board[1][i]==0&&board[2][i]==0&&board[3][i]==0&&board[4][i]==0) //세로
			count++;
	}
	if(board[0][0]==0&&board[1][1]==0&&board[2][2]==0&&board[3][3]==0&&board[4][4]==0)
		count++;
	if(board[0][4]==0&&board[1][3]==0&&board[2][2]==0&&board[3][1]==0&&board[4][0]==0)
		count++;
	return count;
}
bool check_winner()
{
	if(p.p_turn[1]>=5&&p.p_turn[2]>=5){
		p.p_turn[3]=3; //무승부
		return true;
	//	printf("무승부 입니다.");
	}
	else if(p.p_turn[1]>=5){
		p.p_turn[3]=1; //선공 승리
		return true;
	//	printf("당신은 승리하셨습니다.");
	}
	else if(p.p_turn[2]>=5){
		p.p_turn[3]=2; //후공 승리
		return true;
	//	printf("당신은 패배하셨습니다.");
	}
	return false;
}


void * recv_msg(void * arg) // read thread main
{
    int str_len;
	char temp[3];
	int number;
    while(1)
    {
        str_len=read(socket_fd, &p, sizeof(p));
        if(str_len==-1)
        	return (void*)-1;
		
		

        p.p_msg[str_len]='\0';
		  
		if (p.p_msg[0] == '='){
			p.p_turn[turn_order[0]]=bingo_check(board);
			check_number[p.p_turn[0]] = 1;
			game_print(p.p_turn[0], now_turn);
			if(check_winner()){
				send_winner();
				return NULL;
			}
			printf("recv number %d\n", p.p_turn[0]);
			now_turn++;
		}
		else{		  
        	fputs(p.p_msg, stdout);
		}
		
		if (p.p_turn[other_turn] >= 5){
			printf("defeat.... \n");
			return NULL;
		}
    }
    return NULL;
}



 void * send_msg(void * arg)   // send thread main
{
	char temp[3];
	int number = 0;
    while(1)
    {
		if (p.p_turn[3] != 0){
			return NULL;
		}
		printf(">>> ");
        fgets(p.p_msg, MSG_SIZE, stdin);
		fflush(stdout);
		// 옵션 사용시
		if (p.p_msg[0] == '='){
			
			if (now_turn % 2 == 0){
				printf("other player turn \n");
				printf("%d\n", now_turn);
				continue;
			}
			
			if (strlen(p.p_msg) > 4){
				printf("worng options try again sizeof \n");
				continue;
			}
			
			if (strlen(p.p_msg) == 3){
				if (isdigit(p.p_msg[1])){
					temp[0] = p.p_msg[1];
					temp[1] = '\0';
				}
				
				else{
					printf("worng options try again isdigit 2\n");
					continue;
				}
			}
			
			else if (strlen(p.p_msg) == 4){
				if ((isdigit(p.p_msg[1])) && (isdigit(p.p_msg[2]))){
					temp[0] = p.p_msg[1];
					temp[1] = p.p_msg[2];
					temp[2] = '\0';
				}
				else{
					printf("worng options try again isdigit 3\n");
					continue;
				}
			}
		
			else{
				printf("worng options try again isdigit4 \n");
				continue;
			}
			
			number = atoi(temp);
			
			if ((number >= 1) && (number <= 25) && (check_number[number] == 0)){
				
				p.p_turn[0] = number;
				if (check_number[p.p_turn[0]] == 0){
					p.p_turn[turn_order[0]]=bingo_check(board);	
					game_print(p.p_turn[0], now_turn);
					check_number[p.p_turn[0]] = 1;
					now_turn++;
					write(socket_fd, &p, sizeof(p));
					if(check_winner()){
						send_winner();
						return NULL;
					}
				}
				else{
					printf("already check try again \n");
					continue;
				}
			}
			
			else{
				printf("worng number try again \n");
				continue;
			}
		}
	
		else{
			write(socket_fd, &p, sizeof(p));
		}
		 
        
    }
    return NULL;
}
