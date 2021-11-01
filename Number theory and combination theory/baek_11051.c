#include <stdio.h>
#include <math.h>
// 이것도 마찬가지로 하면 되지 않을까? 1010 참고 

#pragma warning (disable:4996)
/*
arr[30] 이렇게 만들어서 arr[i] = i 가 되도록 만든 다음, 입력받은 숫자를 보고 구해보자.
*/

#define MAX 1005
#define DIV 10007
#define PRIME 0
#define NOTPRIME -1

#define MOM 0
#define SON 1 // save배열에서 사용할 것 
#define DIFF 2

int arr[MAX] = { PRIME }; // 전부 PRIME 이라고 가정 
int numCount[3][MAX] = { 0 };
int son;
int mom;

// numerator 분모
// denominator 분자 

void putData() {
	scanf("%d%d", &son, &mom);
}

// 10C2 or 10C6 같은 경우, 2와 8을 비교하고 2를 가져온다. 10C6의 경우 4.
int returnSmall(int a, int b) {
	// a<b
	int diff = b - a;
	if (a < diff) {
		return a;
	}
	return diff;
}

int searchNextPrime(int a) {
	int primeIdx = a + 1;
	while (arr[primeIdx] != PRIME) {
		primeIdx++;
	}
	return primeIdx;
}

void findEveryPrime() {

	// 0, 1은 소수가 아님
	// 1-based 배열
	arr[0] = NOTPRIME;
	arr[1] = NOTPRIME;

	// 가장 마지막으로 조사한 수 
	// 일단 위에서 1까지 조사했으니까
	int currentPrime = searchNextPrime(1);

	// 체 거르기
	int maxPrime = (int)sqrt(son);
	while (currentPrime <= maxPrime) {
		for (int i = currentPrime; i*currentPrime <= son; i++) {
			arr[i*currentPrime] = NOTPRIME;
		}
		currentPrime = searchNextPrime(currentPrime);
	}
}

void factorization(int n, int SonOrMom) {

	int currentPrime = 2;
	// 주어진 숫자를 소인수분해한다. 예를 들어 6이면 numCount[SonOrMom][2]++; numCount[SonOrMom][3]++
	while (n != 1) {
		if (n % currentPrime == 0) {
			numCount[SonOrMom][currentPrime]++;
			n /= currentPrime;
		}
		else {
			currentPrime = searchNextPrime(currentPrime);
		}
	}
}

// 이제 분모분자를 배열에다 담자. 물론, 소인수분해해서 
void numberSwitch() {

	// 10C3, 10C7 이 같지만 10C3이 계산이 더 빠르므로 바꿔주자. 
	int lower = returnSmall(mom, son);
	mom = lower;

	// 분모를 소인수분해하여 넣고 
	for (int i = mom; i > 1; i--) {
		factorization(i, MOM);
	}

	for (int i = son; i > son - mom; i--) {
		factorization(i, SON);
	}
}

// 이제 numCount 배열을 정리해주자 
void organizeNumCount() {
	for (int i = 2; i <= son; i++) {
		numCount[DIFF][i] = numCount[SON][i] - numCount[MOM][i];
	}
}

// 이제 남은 숫자들을 전부 곱해주면 된다.
// 이때, 곱하다가 DIV을 넘어가는 순간 나누어주자. 
int multiflyNumCount() {
	int answer = 1;

	for (int i = 2; i <= son; i++) {
		while (numCount[DIFF][i] > 0) {
			answer *= i;
			numCount[DIFF][i]--;

			if (answer > DIV) {
				answer %= DIV;
			}
		}
	}

	return answer;
}

int main() {

	putData();
	findEveryPrime();
	numberSwitch();
	organizeNumCount();
	int ans = multiflyNumCount();

	printf("%d", ans);

	return 0;
}
