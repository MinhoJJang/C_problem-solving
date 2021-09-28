#include <stdio.h> //표준 입출력헤더 
#pragma warning(disable:4996) //scanf()등 ANSI C함수 에러 메세지 무시

/*
위의 그림과 같이 육각형으로 이루어진 벌집이 있다. 
그림에서 보는 바와 같이 중앙의 방 1부터 시작해서 이웃하는 방에
돌아가면서 1씩 증가하는 번호를 주소로 매길 수 있다. 숫자 N이 
주어졌을 때, 벌집의 중앙 1에서 N번 방까지 최소 개수의 방을 지나서 
갈 때 몇 개의 방을 지나가는지(시작과 끝을 포함하여)를 계산하는 
프로그램을 작성하시오. 

예를 들면, 13까지는 3개, 58까지는 5개를 지난다.
*/

int main() {

	int N;
	int i;
	int x = 0;
	int count = 0;

	scanf("%d", &N);

	for (i = 0; ; i++) {
		
		int p = 0;
		p += i;
		x += 6*p;

		if (N - (x+1) > 0) {
			count++;
		}
		else {
			break;
		}
	}
	printf("%d\n", count+1);

	return 0;
} //맞았습니다!!