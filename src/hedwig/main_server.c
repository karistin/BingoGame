#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#define MSG_BUF_SIZE 256
#define CLNT_BUF_SIZE 256

void * handle_clnt(void * arg);
void send_msg (char * msg, int len);
void send_number(char * msg);


int clnt_buf [CLNT_BUF_SIZE];
int clnt_count = 1;
pthread_mutex_t mutx;
int child_clnt_buf [2];
int clnt_real_count = 0;

pthread_t t_id[2];


int main (int argc, char * argv[]){
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int clnt_adr_sz;
	pid_t pid = 1;
	
	pthread_mutex_init(&mutx, NULL);
	// server socket setting

	memset(&serv_adr, 0 ,sizeof(serv_adr));
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1){
		perror("bind");
		exit(1);
	}
	if (listen(serv_sock, 5) == -1){
		perror("listen");
		exit(1);
	}
	
	//m main server loop (endless)
	while (1){
		clnt_adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_adr, &clnt_adr_sz);
		clnt_buf[clnt_count % CLNT_BUF_SIZE] = clnt_sock;
		clnt_count ++;
		clnt_real_count ++;
		// user over 2 waiting
		if(clnt_real_count >= 2){
			if( pid != 0 )pid = fork();
		
			// child_process
			if (pid == 0){
				close(serv_sock);
				child_clnt_buf[0] = clnt_buf[clnt_count - 2];
				child_clnt_buf[1] = clnt_buf[clnt_count - 1];
				
				for (int i = 0; i < 2 ; i ++){
					write(child_clnt_buf[i], "connect with other clinet\n", 28);
					pthread_create(&t_id[i], NULL, handle_clnt, (void *) &child_clnt_buf[i]);
				}
				pthread_join(t_id[0], NULL);
				pthread_join(t_id[1], NULL);
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


void* handle_clnt(void * arg){
	int clnt = *((int *) arg);
	int str_len = 0;
	char msg [MSG_BUF_SIZE];

	while((str_len = read(clnt, msg, sizeof(msg))) != 0){
		if (msg[0] == '='){
			printf("optional \n");
			send_number(msg);
		}
		else{
			send_msg(msg, str_len);
		}
	}
}


void send_number(char * msg){
	char num[3];
	
	num[0] = msg[1];
	num[1] = msg[2];
	num[2] = '\0';

	for (int i = 0; i < 2 ; i ++){
		write(child_clnt_buf[i], num, 3);
	}
}

void send_msg(char * msg, int len){
	for (int i = 0; i < 2 ; i ++){
		write(child_clnt_buf[i], msg, len);
	}
}
