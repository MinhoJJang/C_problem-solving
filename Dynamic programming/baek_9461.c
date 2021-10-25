#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*

*/

unsigned long long arr[105] = { 0 };

unsigned long long fn(int N) {

	if (N < 5) {
		if (N < 3) {
			arr[N] = 1;
		}
		else {
			arr[N] = 2;
		}
	}
	else if (arr[N] == 0) {
		arr[N] = fn(N-5) + fn(N - 1);
	}

	return arr[N];
}

int main() {

	int Testcase = 0;
	int N;
	unsigned long long ans[105] = { 0 };

	scanf("%d", &Testcase);

	for (int i = 0; i < Testcase; i++) {
		scanf("%d", &N);
		ans[i] = fn(N - 1);
	}

	for (int i = 0; i < Testcase; i++) {
		printf("%lld\n", ans[i]);
	}

	return 0;
} // 맞았습니다!
