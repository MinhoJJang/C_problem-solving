#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*https://www.acmicpc.net/problem/2231
어떤 자연수 N이 있을 때, 그 자연수 N의 분해합은 N과 N을 이루는 각 자리수의 합을 의미한다. 어떤 자연수 M의 분해합이 N인 경우, M을 N의 생성자라 한다. 예를 들어, 245의 분해합은 256(=245+2+4+5)이 된다. 따라서 245는 256의 생성자가 된다. 물론, 어떤 자연수의 경우에는 생성자가 없을 수도 있다. 반대로, 생성자가 여러 개인 자연수도 있을 수 있다.

자연수 N이 주어졌을 때, N의 가장 작은 생성자를 구해내는 프로그램을 작성하시오.
*/

// 입력된 수가 N이면 N을 1씩 빼고 그 분해합을 구해서 그 합이 원래 N이면 종료

int fn(int N, int FirstN) {

	int sum = 0;
	int basic = N;
	int rest;

	do {

		rest = basic % 10;
		basic = basic / 10;
		sum += rest;

	} while (basic != 0);

	if (FirstN == sum + N) {
		return N;
	}

	if (N == FirstN+1) {
		return 0;
	}

	return fn(N + 1, FirstN);
}

int main() {

	int N;
	scanf("%d", &N);
	printf("%d", fn( 1, N));

	return 0;
}