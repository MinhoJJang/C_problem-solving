#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <math.h>
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

#define INIT -1
#define NOTPRIME 0
/*
 소수 찾기
*/
int arr[101] = { 0 };

void putData(int N) {
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
}

int findPrimeNumber(int N) {
	
	int countPrime = 0;

	for (int i = 0; i < N; i++) {

		// 만약 주어진 숫자가 제곱수이면 어차피 소수가 아니니까.. 제곱근 취한 값부터 1씩 감소시키면서 나눠지는지 검사 
		if (arr[i] != 1 && arr[i] != 2) {

			int squareRoot = sqrt(arr[i]);
			int flag = INIT;

			// 1은 제외하고 나눈다. 
			while (squareRoot > 1) {
				// 나누어 떨어지면 소수가 아님
				if (arr[i] % squareRoot == 0) {
					flag = NOTPRIME;
					break;
				}
				squareRoot--;
			}

			// squareRoot가 2까지 도달했으면
			if (flag == INIT) {
				countPrime++;
			}
		}
		else if (arr[i] == 2) {
			countPrime++;
		}

	}

	return countPrime;
}

int main() {

	int N;
	scanf("%d", &N);

	putData(N);
	printf("%d", findPrimeNumber(N));

	return 0;
} // 맞았습니다