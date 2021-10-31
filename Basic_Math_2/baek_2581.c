#include <stdio.h>
#include <math.h>
#pragma warning (disable: 4996)

#define PRIME 0
#define NOTPRIME -1

#define MAX 10005

int arr[MAX] = { PRIME }; // 전부 PRIME 이라고 가정 

int low, high;

void putData() {
	scanf("%d%d", &low, &high);
}

int findNextPrime(int a) {
	int primeIdx = a + 1;
	while (arr[primeIdx] != PRIME) {
		primeIdx++;
	}
	return primeIdx;
}

void mainLogic() {

	// 0, 1은 소수가 아님
	// 1-based 배열
	arr[0] = NOTPRIME;
	arr[1] = NOTPRIME;

	// 가장 마지막으로 조사한 수 
	// 일단 위에서 1까지 조사했으니까
	int currentPrime = findNextPrime(1);

	// 체 거르기
	int Maxprime = (int)sqrt(high);
	while (currentPrime <= Maxprime) {
		for (int i = currentPrime; i*currentPrime <= high; i++) {
			arr[i*currentPrime] = NOTPRIME;
		}
		currentPrime = findNextPrime(currentPrime);
	}
}

int primeCount = 0;
int lowestPrime;
int primeSum = 0;

void findAllPrime() {
	for (int currentNum = low; currentNum <= high; currentNum++) {
		if (arr[currentNum] == PRIME) {
			primeCount++;
			if (primeCount == 1) {
				lowestPrime = currentNum;
			}
			primeSum += currentNum;
		}
	}
}

void printAnswer() {
	if (primeCount > 0) {
		printf("%d\n%d", primeSum, lowestPrime);
	}
	else {
		printf("-1");
	}
}

int main() {
	putData();
	mainLogic();
	findAllPrime();
	printAnswer();
}
// 맞았습니다! 