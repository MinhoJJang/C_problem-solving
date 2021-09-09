#include <stdio.h> //표준 입출력헤더 
#pragma warning(disable:4996) //scanf()등 ANSI C함수 에러 메세지 무시

/*
N개의 숫자가 공백 없이 쓰여있다. 이 숫자를 모두 합해서 출력하는 프로그램을 작성하시오.

첫째 줄에 숫자의 개수 N (1 ≤ N ≤ 100)이 주어진다. 둘째 줄에 숫자 N개가 공백없이 주어진다.
*/

int main() {

	int MaxNum = 0;
	int total = 0;
	char num[100];

	scanf("%d", &MaxNum);
    scanf("%s", num);

	for (int i = 0; i < MaxNum; i++) {
		total += (num[i]-48);
	}
	
	printf("%d", total);

	return 0;
} //맞았습니다!

