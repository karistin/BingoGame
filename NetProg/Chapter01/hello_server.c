#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

void errror_handling(char *message);
int main(int argc , char * argv[])
{
	int ser_sock;
	int clnt_sock;
	
	//char * message ="Hello my name is ksj. Nice to meet you\0";
	char message[]= "Hello my name is ksj. Nice to meet you";
	if(argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	struct sockaddr_in ser_addr;
	struct sockaddr_in clnt_addr;
	
	socklen_t clnt_addr_size;
	
	ser_sock=socket(PF_INET,SOCK_STREAM,0);
	if(ser_sock == -1)
		printf("socket 에러");
	
	memset(&ser_addr,0,sizeof(ser_addr));
	
	ser_addr.sin_family=AF_INET;
	ser_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	ser_addr.sin_port=htons(atoi(argv[1]));
	
	printf("IP : %d\n",INADDR_ANY);
	printf("PORT : %d\n",atoi(argv[1]));
	
	if(bind(ser_sock, (struct sockaddr *)&ser_addr ,sizeof(ser_addr))==-1 )
		errror_handling("bind() error");
	
	if(listen(ser_sock , 5) ==-1)
		errror_handling("accept() error");
	
	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(ser_sock , (struct sockaddr *)&clnt_addr, &clnt_addr_size);
	
	if(clnt_sock ==-1)
		errror_handling("accept() error");
	
	write(clnt_sock , message , sizeof(message));
	close(clnt_sock);
	close(ser_sock);
	
	return 0;
		
}

void errror_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
	