#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 
#define MAX 310

int maxSum[MAX];
int wine[MAX];

//계단값 입력함수
void inputNum(int N) {
	for (int i = 1; i < N+1; i++) {
		scanf("%d", &wine[i]);
	}
}

// N번째 계단까지의 최댓값을 구하는 함수
int fn(int N) {

	if (N == 1) {
		maxSum[N] = wine[N];
	}
	else if (N == 2) {
		maxSum[N] = wine[N] + wine[N-1];
	}
	else if (N == 3) {
		maxSum[N] = (wine[N - 2] >= wine[N - 1]) ? wine[N - 2] + wine[N] : wine[N - 1] + wine[N];
	}
	// N이 3초과이고 maxSum값을 모르면..
	else if( maxSum[N] == 0){
		maxSum[N] = (fn(N - 2) > fn(N - 3) + wine[N - 1]) ? maxSum[N - 2] + wine[N] : maxSum[N - 3] + wine[N - 1] + wine[N];
	}
	return maxSum[N];
}


int main() {

	int N;
	scanf("%d", &N);

	inputNum(N);
	printf("%d", fn(N));

	return 0;
}

// 이문제는 진짜 쓸게많겠다^^ 