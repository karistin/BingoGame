#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
int main ()
{
	// char a[20]="ksj";
	// char b[20]="kakak";
	// char c[20]="ksj";
	
	// if(!strcmp(a,b))
	// 	printf("a와 b 같음 ");
	// if(!strcmp(b,c))
	// 	printf("b와 c 같음 ");
	// if(!strcmp(a,c))
	// 	printf("a와 c 같음 ");
	
	int sk = 10;
	char a[1];
	
	printf("%s", itoa(sk , a , 10));
	
}