#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
두 개의 자연수를 입력받아 최대 공약수와 최소 공배수를 출력하는 프로그램을 작성하시오.

첫째 줄에는 두 개의 자연수가 주어진다. 이 둘은 10,000이하의 자연수이며 사이에 한 칸의 공백이 주어진다.
*/

/*
1. 최대공약수 

큰 수를 a, 작은 수를 b라고 하면



2. 최소공배수
최대공약수를 찾았으면, 주어진 수를 최대공약수로 나누고 그 값들의 최소공배수를 구한 다음 최대공약수를 곱한다. 
*/

// greatest common measure = GCM
// least common multiple = LCM



// 최대공약수 찾기
int fnGCM(int a, int b) {

	// a,b중에 큰 것이 
	int big = (a > b) ? a : b;
	int small = a + b - big;

	int smallerOne = (small < big - small) ? small : big - small;

	int div = 2;
	int ans = 1;
	// 만약 a,b 둘중 하나가 1인경우 
	if (a == 1 || b == 1) {
		ans *= 1;
	}
	// a == b인 경우
	if (a == b) {
		ans *= a;
	}
	else {
		while (div <= smallerOne) {
			if (a%div == 0 && b%div == 0) {
				ans *= div;
				a /= div;
				b /= div;
			}
			else {
				div++;
			}
		}
	}

	return ans;
}

// 최소공배수 찾기
int fnLCM(int a, int b) {

	int gcm = fnGCM(a, b);
	
	int LCM_a = a / gcm;
	int LCM_b = b / gcm;

	int ans = LCM_a * LCM_b * gcm;

	return ans;
}

int main() {

	int a;
	int b;

	scanf("%d %d", &a, &b);

	printf("%d\n", fnGCM(a, b));
	printf("%d\n", fnLCM(a, b));

	return 0;
}