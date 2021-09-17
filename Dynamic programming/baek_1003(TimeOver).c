#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

// 포인터를 아주 잘 알아야 풀듯

int fn(int N, int *count_zero, int *count_one) {
	if (N == 0) {
		*count_zero += 1;
		return 0;
		
	}
	else if (N == 1) {
		*count_one += 1;
		return 1;
		
	}
	else {
		return fn(N - 2, count_zero, count_one) + fn(N - 1, count_zero, count_one);
	}
}

void showArr(int Testcase, int(*arr)[2]) {

	for (int i = 0; i < Testcase; i++) {
		printf("%d %d\n", arr[i][0], arr[i][1]);
	}

}

int main() {

	int Testcase;
	int testArr[100][2];
	int N;
	
	scanf("%d", &Testcase);

	for (int i = 0; i < Testcase; i++) {

		int count_zero = 0;
		int count_one = 0;

		scanf("%d", &N);
		fn(N, &count_zero ,&count_one);
		testArr[i][0] = count_zero;
		testArr[i][1] = count_one;
	}

	showArr(Testcase, testArr);

	return 0;
} // 하지만 실3문제를 너무 날로먹을라고 했다. 바로 시간초과