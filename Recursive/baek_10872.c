#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

//https://www.acmicpc.net/problem/10872
//문제
//0보다 크거나 같은 정수 N이 주어진다.이때, N!을 출력하는 프로그램을 작성하시오.
//
//입력
//첫째 줄에 정수 N(0 ≤ N ≤ 12)이 주어진다.


int fn(int N) {

	if (N == 0) {
		return 1;
	}
	else {
		return N * fn(N - 1);
	}

}

int main() {

	int N;
	scanf("%d", &N);

	printf("%d", fn(N));


	return 0;
} // 맞았습니다!!