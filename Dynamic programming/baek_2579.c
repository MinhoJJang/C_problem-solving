#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 
#define MAX 310

int maxSum[MAX];
int stair[MAX];

//계단값 입력함수
void inputNum(int N) {
	for (int i = 1; i < N+1; i++) {
		scanf("%d", &stair[i]);
	}
}

// N번째 계단까지의 최댓값을 구하는 함수
int fn(int N) {

	if (N == 1) {
		maxSum[N] = stair[N];
	}
	else if (N == 2) {
		maxSum[N] = stair[N] + stair[N-1];
	}
	else if (N == 3) {
		maxSum[N] = (stair[N - 2] >= stair[N - 1]) ? stair[N - 2] + stair[N] : stair[N - 1] + stair[N];
	}
	// N이 3초과이고 maxSum값을 모르면..
	else if( maxSum[N] == 0){
		maxSum[N] = (fn(N - 2) > fn(N - 3) + stair[N - 1]) ? maxSum[N - 2] + stair[N] : maxSum[N - 3] + stair[N - 1] + stair[N];
	}
	// ??? 어째서 순서만 바꿨는데 값이 다르지?

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