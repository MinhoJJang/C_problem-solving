#include <stdio.h> //표준 입출력헤더 
#pragma warning(disable:4996) //scanf()등 ANSI C함수 에러 메세지 무시

/*
https://www.acmicpc.net/problem/10250
*/

int main() {

	int H = 0; //호텔 층수
	int W = 0; //호텔 층당 방 개수
	int N = 0; // N번째 손님
	int Test,t;
	int ans[999];

	scanf("%d", &Test);

	for (t = 0; t < Test; t++) {

		scanf("%d%d%d", &H,&W,&N);

		int Y = N % H; //손님 H명당 같은 방번호를 사용. 101,201,301,...
		//즉 호텔의 층수를 알려주는 값
		int X = N / H + 1; //방번호

		if (Y != 0) {
			ans[t] = 100 * Y + X;
		}
		else {
			int ex = X - 1;
			ans[t] = 100 * H + ex;
			
		}
		H, W, N = 0;
	}
	
	for (t = 0; t < Test; t++) {
		printf("%d\n", ans[t]);
	}

	return 0;
} //맞았습니다!!