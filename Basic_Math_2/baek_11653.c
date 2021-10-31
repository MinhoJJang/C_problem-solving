#include <stdio.h>
#include <math.h>
#pragma warning (disable:4996)
/*
정수 N이 주어졌을 때, 소인수분해하는 프로그램을 작성하시오.

입력
첫째 줄에 정수 N (1 ≤ N ≤ 10,000,000)이 주어진다.

출력
N의 소인수분해 결과를 한 줄에 하나씩 오름차순으로 출력한다. N이 1인 경우 아무것도 출력하지 않는다. */

// 일단 체를 갖고오자 

#define PRIME 0
#define NOTPRIME -1
#define MAX 10000005 // sqrt 10,000,000 = 3162.2776...

int n = 0;
int arr[MAX] = { PRIME }; // 전부 PRIME 이라고 가정 

void putData() {
	scanf("%d", &n);
}

int findNextPrime(int a) {
	int primeIdx = a + 1;
	while (arr[primeIdx] != PRIME) {
		primeIdx++;
	}
	return primeIdx;
}

void mainLogic(int n) {

	// 0, 1은 소수가 아님
	// 1-based 배열
	arr[0] = NOTPRIME;
	arr[1] = NOTPRIME;

	// 가장 마지막으로 조사한 수 
	// 일단 위에서 1까지 조사했으니까
	int currentPrime = findNextPrime(1);

	// 체 거르기
	int maxPrime = sqrt(n);
	while (currentPrime <= maxPrime) {
		for (int i = currentPrime; i*currentPrime <= n; i++) {
			// 여기서 OutOfBounds 오류 발생.
			// i*currentPrime의 최댓값에 주의
			arr[i*currentPrime] = NOTPRIME;
		}
		currentPrime = findNextPrime(currentPrime);
	}
}

void mainFunction(int input) {
	int currentPrime = 2;

	while (input != 1) {
		if (input % currentPrime == 0) {
			input /= currentPrime;
			printf("%d\n", currentPrime);
			continue;
		}
		currentPrime = findNextPrime(currentPrime);
	}
}

int main() {

	putData();
	mainLogic(n);
	mainFunction(n);

	return 0;
}

// 맞았습니다!