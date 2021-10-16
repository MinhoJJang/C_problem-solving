#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
자연수 \(N\)과 정수 \(K\)가 주어졌을 때 이항 계수
\(\binom{N}{K}\)를 10,007로 나눈 나머지를 구하는 프로그램을 작성하시오.

첫째 줄에 \(N\)과 \(K\)가 주어진다. (1 ≤ \(N\) ≤ 1,000, 0 ≤ \(K\) ≤ \(N\))

*/
#define MAX 1005
#define DIV 10007

typedef unsigned long long unlong;

unlong factorialNum[MAX] = { 0 };
unlong arr[MAX][MAX] = { 0 };

unlong fact(int i) {
	if (factorialNum[i] == 0) {
		if (i == 1 || i == 0) {
			factorialNum[i] = 1;
			return 1;
		}
		else {
			factorialNum[i] = i * fact(i - 1);
			return factorialNum[i];
		}
	}
	else {
		return factorialNum[i];
	}
}

unlong mainFn(int n, int k) {
	
	if (arr[n][k] == 0) {
		arr[n][k] = (fact(n) / (fact(k) * fact(n - k))) % DIV;
		arr[n][n - k] = arr[n][k];
	}

	return arr[n][k];
}

int n;
int k;

void putData() {
	scanf("%d %d", &n, &k);
}

int main() {

	putData();

	int answer = mainFn(n, k);
	printf("%d", answer);

	return 0;
}