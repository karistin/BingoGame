#include <stdio.h>


int main(int argc, char *argv[])      // 옵션의 개수와 옵션 문자열을 배열로 받음
{
	printf("문자열의 총 개수는 %d이다.\n",argc);
    for (int i = 0; i < argc; i++)    // 옵션의 개수만큼 반복
    {
        printf("%d번 문자열 : %s\n", i, argv[i]);      // 옵션 문자열 출력
    }
	
    return 0;
}