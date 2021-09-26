#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
N!에서 뒤에서부터 처음 0이 아닌 숫자가 나올 때까지 0의 개수를 구하는 프로그램을 작성하시오.
*/

// 뒤에 0이 있으려면, 2와 5가 1개씩 있어야 한다. 그 개수를 세자.

#define MAX 502
#define TWO 0
#define FIVE 1

int arr[MAX][2] = { 0 };
int totalTwo = 0;
int totalFive = 0;

void NumberOfTwoAndFive(int N) {

	while (N > 1) {
		int Test;

		// 2의 개수
		Test = N;
		while (Test % 2 == 0) {
			arr[N][TWO]++;
			Test /= 2;
		}

		// 5의 개수
		Test = N;
		while (Test % 5 == 0) {
			arr[N][FIVE]++;
			Test /= 5;
		}

		totalTwo += arr[N][TWO];
		totalFive += arr[N][FIVE];
		N--;
	}
}

int findZero() {
	if (totalFive > totalTwo) {
		return totalTwo;
	}
	return totalFive;
}

int main() {

	int N;
	scanf("%d", &N);
	
	NumberOfTwoAndFive(N);
	printf("%d", findZero());

	return 0;
}