#include <stdio.h> //표준 입출력헤더 
#pragma warning(disable:4996) //scanf()등 ANSI C함수 에러 메세지 무시

/*
https://www.acmicpc.net/problem/1011
입력의 첫 줄에는 테스트케이스의 개수 T가 주어진다. 각각의 테스트 케이스에
대해 현재 위치 x 와 목표 위치 y 가 정수로 주어지며, x는 항상 y보다 작은 값을
갖는다. (0 ≤ x < y < 2^31)
*/
			// 예를 들어 차이가 9면 n=3에서 break;
			// z는 (n-1)제곱< z <=n제곱 사이.
			// n제곱이 2n-1개로 이루어진 조합의 마지막 수이므로 
			// z가 n제곱 - n < z 이면 2n-1개, 아니면 2n-2개. 
			//16  17 18 19 20  21 22 23 24 25
			//7			8					9

int main() {

	int x, y, z;
	int Test,t;
	
	scanf("%d", &Test);

	int ans[100] = { 0 };

	for (t = 0; t < Test; t++) {

		scanf("%d%d", &x, &y);

		z = y - x;
		int n;

		for (n = 0; ; n++)
		{
			if (z - n * n <= 0) {
				break;
			}
		}			

		if (z > n*n - n) {
			ans[t] = 2 * n - 1;
		}
		else {
			ans[t] = 2 * n - 2;
		}

		x = 0;
		y = 0;
	}

	for (t = 0; t < Test; t++) {
		printf("%d\n", ans[t]);
	}

	return 0;
} //시간초과 