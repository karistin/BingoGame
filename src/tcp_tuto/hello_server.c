#include<stdio.h>
//기본 in out 라이브러리
#include<stdlib.h> 
//동적 데이터 문자열 반환 (atol .. )
#include <string.h>
//문자열 복사 비교 
#include <unistd.h>
// close sleep write read
#include <arpa/inet.h>
//htonl() in_addr_t 
 //bind() 함수에 주소정보를 전달하기 위한 주소정보 구조체가 들어있습니다.
#include <sys/socket.h>
// socket bind listen accept 
//socket관련 함수가 들어있습니다.
void error_handling(char *message);

int main(int argc, char *argv[])
{
	//argc : main에 전달되는 데이터 갯수 
	//char* argv[] : main 함수에 전달되는 실제적인 데이터 , char형 포인터 배열
	//argv[0] : 디폴트는 프로그램 실행 경로 
	
	int serv_sock;
	int clnt_sock;
	 //serv_sock 이라는 변수를 선언합니다. 이는 socket() 의 반환값을 받기 위함입니다.
	//clnt_sock 이라는 변수를 선업합니다. 이는 accept() 의 반환값을 받기 위함입니다.
	//서버는 소켓이 2개이다.
	struct sockaddr_in serv_addr;
	 //server에 해당하는 주소체계에 대한 구조체 변수를 선언합니다.
	struct sockaddr_in clnt_addr;
	//clnt에 해당하는 주소체계에 대한 구조체 변수를 선언합니다.
	socklen_t clnt_addr_size;

	char message[]="Hello World!";
	
	if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error");
	
	printf("file descriptor : %d \n" , serv_sock);
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	//컴퓨터 랜카드 IP = INADDR_ANY
	printf("%d/n",INADDR_ANY);
	
	serv_addr.sin_port=htons(atoi(argv[1]));
	
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1 )
		error_handling("bind() error"); //실패 -1
	
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	clnt_addr_size=sizeof(clnt_addr);  
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock==-1)
		error_handling("accept() error");  
	
	write(clnt_sock, message, sizeof(message));
	close(clnt_sock);	
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
/*
표준 스트림 
1) 표준 입력 FILE* stdin
2) 표준 출력 FILE* stdout
3) 표준 에러 FILE* stderr
https://sjh836.tistory.com/41
*/
