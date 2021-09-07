#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 
#define YES 1
#define NO 0

/*
자연수 N과 M이 주어졌을 때, 아래 조건을 만족하는 길이가 M인 수열을 모두 구하는 프로그램을 작성하시오.

1부터 N까지 자연수 중에서 M개를 고른 수열
같은 수를 여러 번 골라도 된다.
*/
void printarr(int arr[], int len) {

	int idx = 0;

	while (idx != len) {
		printf("%d ", arr[idx]);
		idx++;
	}

	printf("\n");
}

void fn(int NumberofNum, int len) {

	int select[8];
	int num = 0;

	while (num != len) {
		select[num] = 1;
		num++;
	}

	int idx = len - 1;

	while (select[0] != NumberofNum + 1) {

		// 최대숫자보다 클경우
		if (select[idx] > NumberofNum) {
			for (int i = idx; i >= 1; i--) {

				select[i] = 1;
				select[i - 1]++;

				if (select[i - 1] > NumberofNum) {
					continue;
				}
				else {
					break;
				}
			}
		}

		if (select[0] != NumberofNum+1) {
			printarr(select, len);
			select[idx]++;
		}
	}
}

int main() {

	int N = 0;
	int M = 0;

	scanf("%d%d", &N, &M);

	fn(N, M);

	return 0;
} // 맞았습니다!! 