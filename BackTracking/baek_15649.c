#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 
#define YES 1
#define NO 0

/*
자연수 N과 M이 주어졌을 때, 아래 조건을 만족하는 길이가 M인 수열을 모두 구하는 프로그램을 작성하시오.

1부터 N까지 자연수 중에서 중복 없이 M개를 고른 수열
*/
void printarr(int arr[], int len) {

	int idx = 0;

	while (idx != len) {
		printf("%d ", arr[idx]);
		idx++;
	}

	printf("\n");
}

int IsDuplicate(int arr[], int len) {

	for (int idx = len - 1; idx >= 0; idx--) {
		int dup = arr[idx];
		for (int i = idx - 1; i >= 0; i--) {
			if (dup == arr[i]) {
				return YES;
			}
		}
	}
	return NO;
}

void fn(int NumberofNum, int len) {
	
	int select[8]; 
	int num = 0;

	while (num != len) {
		select[num] = num + 1;
		num++;
	}

	// sel 배열은 index 0부터 M-1까지 숫자가 들어있을 것
	// M-1번쨰부터 1씩 더하기 시작해서, 1 더한 숫자가 NumberofNum보다 크면  십의자리수 올리기 
	int idx = len - 1;

	while (select[0] != NumberofNum+1) {

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

		// 최대숫자보다는 작지만, 중복인가 아닌가? 
		else {
			if (IsDuplicate(select, len) == NO) {
				printarr(select, len);								
			}
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