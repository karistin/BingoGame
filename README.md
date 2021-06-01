# TCP 프로그래밍 3차 과제
* 프로그램 파일 위치 

	TCP/src/hedwig/
		> bingo_server.c 
		> bingo_client.c 
		> Makefile
		> data.txt
		

 * data.txt
 
 	사용자의 ID 와 PWD를 저장하는 텍스트 파일 
	
	ID PWD 형식으로 이루어짐 
	
 * Makefile
 	
 * bingo_server.c 
 
 	실행 명령어 
		 /.bingo_server <port>
	
	핵심 함수
	
	menu() : 클라이언트의 로그인 회원가입 결정
	
	login() : 입력한 ID/PWD를 data.txt에서 확인 
	
	signup() : 입력한 내용 data.txt에 저장 
	
	