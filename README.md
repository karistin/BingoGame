# TCP
* 서버 접속 
	>  ssh -p 55795 root@13.124.191.220
* 네트워 프로그램 

	socket 
	> icmp 프로토몰을 사용하는 ping 명령어
	> icmp 프로토콜을 사용하는  traceroute 명령어
	
	dns nslookup
	
	네트웍 상태 확인 netstat / ifconfig /ipconfig ㅣㄴ
	
	
	TCP 내부 동작 원리
소켓에 존재하는 입출력 퍼버 => socket()
 입	출
S	  C	
 출	입
불러오지 못한다. 
상대 소켓 과의 연결 
=>bind() listen() accept() coonect()

상대 소켓 대이터 송수신 
read() / write()

상대 소켓 데이터 연결 종료 
close()


	