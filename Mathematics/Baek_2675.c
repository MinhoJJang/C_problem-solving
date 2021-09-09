#include <stdio.h> //표준 입출력헤더 
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996) //scanf()등 ANSI C함수 에러 메세지 무시

/*
문자열 S를 입력받은 후에, 각 문자를 R번 반복해 새 문자열 P를 만든 후 출력하는 프로그램을 작성하시오. 즉, 첫 번째 문자를 R번 반복하고, 두 번째 문자를 R번 반복하는 식으로 P를 만들면 된다. S에는 QR Code "alphanumeric" 문자만 들어있다.

QR Code "alphanumeric" 문자는 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ\$%*+-./: 이다.

첫째 줄에 테스트 케이스의 개수 T(1 ≤ T ≤ 1,000)가 주어진다. 각 테스트 케이스는 반복 횟수 R(1 ≤ R ≤ 8), 문자열 S가 공백으로 구분되어 주어진다. S의 길이는 적어도 1이며, 20글자를 넘지 않는다.
*/

int main() {

	int Test, t; // (1<= T <= 1000)
	int R; // 반복횟수 (1 <= R <= 8)
	char S[30] = { 0 }; // 문자열 길이 1 <= S <= 20
	char Answer[1000000] = { 0 };

	scanf("%d", &Test);

	for (t = 0; t < Test; t++) {

		scanf("%d", &R);
		scanf("%s", S);
		int len = strlen(S);
		char Scpy[10] = { 0 }; 

		// 배열개수 8개로 하면 문제생김
		// https://www.acmicpc.net/status?user_id=ahchjang&problem_id=2675&from_mine=1 런타임 에러 이유

		char Newstr[200] = { 0 };

		for (int j = 0; j < len; j++) {
			for (int i = 0; i < R; i++) {
				Scpy[i] = S[j];
			}
			strcat(Newstr, Scpy);
		}	
		strcat(Answer, Newstr);
		strcat(Answer, "\n");
	}
	
		printf("%s", Answer);

	return 0;
} //맞았습니다!