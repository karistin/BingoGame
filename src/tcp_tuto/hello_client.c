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
#include <sys/socket.h>
// socket bind listen accept 

void error_handling(char* message);

int main(int argc, char* argv[])
{
	//argc : main에 전달되는 데이터 갯수 
	//char* argv[] : main 함수에 전달되는 실제적인 데이터 , char형 포인터 배열
	//argv[0] : 디폴트는 프로그램 실행 경로 
	int sock;
	
	struct sockaddr_in serv_addr;
	
	char message[30];
	
	int str_len;
	
	printf("%d %s %s",argc ,argv[0] ,argv[1]);
	
	
	if(argc!=3){
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	sock=socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
		
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) 
		error_handling("connect() error!");
	
	str_len=read(sock, message, sizeof(message)-1);//read의 리턴값이 0이 되면 않되기에 그렇다. (바이트 수가 들어가야한다.) read 함수가 message을 읽다가 EOF을 만나면 0을 반환하기에 그걸 막기 위해서 파일의 끝을 읽지 않는다.
	if(str_len==-1)
		error_handling("read() error!");
	
	printf("Message from server: %s \n", message);  
	close(sock);
	return 0;
}





void error_handling(char* message)
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
