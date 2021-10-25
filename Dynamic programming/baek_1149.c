#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
RGB거리에는 집이 N개 있다. 거리는 선분으로 나타낼 수 있고, 1번 집부터 N번 집이 순서대로 있다.

집은 빨강, 초록, 파랑 중 하나의 색으로 칠해야 한다. 각각의 집을 빨강, 초록, 파랑으로 칠하는 비용이 주어졌을 때, 아래 규칙을 만족하면서 모든 집을 칠하는 비용의 최솟값을 구해보자.

1번 집의 색은 2번 집의 색과 같지 않아야 한다.
N번 집의 색은 N-1번 집의 색과 같지 않아야 한다.
i(2 ≤ i ≤ N-1)번 집의 색은 i-1번, i+1번 집의 색과 같지 않아야 한다.
*/

/*
첫째 줄에 집의 수 N(2 ≤ N ≤ 1,000)이 주어진다. 둘째 줄부터 N개의 줄에는 각 집을 빨강, 초록, 파랑으로 칠하는 비용이 1번 집부터 한 줄에 하나씩 주어진다. 집을 칠하는 비용은 1,000보다 작거나 같은 자연수이다.
*/

// 각 지점마다 최솟값을 구하자
#define MAX 1005
#define COLOR 3

int num[MAX][COLOR] = { 0 };
int minSum[MAX][COLOR] = { 0 };

int N; // NumberofHouse

void putData() {

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < COLOR; j++) {
			scanf("%d", &num[i][j]);
		}
	}
}

int returnSmallOne(int a, int b) {
	if (a < b) {
		return a;
	}
	return b;
}

int doNotOverColor(int a) {
	if (a >= COLOR) {
		return a - COLOR;
	}
	return a;
}

// i = 1부터 시작해서 N이 될때까지
void fn(int i, int N) {

	while (i != N+1) {
		// 일단 첫번째 줄은 당연히 그 값 자체가 최소이다. 
		if (i == 1) {
			int idx = 0;
			while (idx != COLOR) {
				minSum[i-1][idx] = num[i-1][idx];
				idx++;
			}
		}
		// N >= 2일때부터...
		else {
			int idx = 0;
			while (idx != COLOR) {
				minSum[i - 1][idx] = num[i - 1][idx] + returnSmallOne(minSum[i - 2][doNotOverColor(idx + 1)], minSum[i - 2][doNotOverColor(idx + 2)]);
				idx++;
			}
		}
		i++;
	}
}

int findAnswer(int N) {
	int min = minSum[N - 1][0];

	if (min > minSum[N - 1][1]) {
		min = minSum[N - 1][1];
	}
	if (min > minSum[N - 1][2]) {
		min = minSum[N - 1][2];
	}

	return min;
}

int main() {

	putData();
	fn(1, N);
	printf("%d", findAnswer(N));

	return 0;
}
 
// 이야 이걸 한번에 맞네 
