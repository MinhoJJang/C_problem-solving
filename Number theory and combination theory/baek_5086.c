#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
https://www.acmicpc.net/problem/5086
4 × 3 = 12이다.

이 식을 통해 다음과 같은 사실을 알 수 있다.

3은 12의 약수이고, 12는 3의 배수이다.

4도 12의 약수이고, 12는 4의 배수이다.

두 수가 주어졌을 때, 다음 3가지 중 어떤 관계인지 구하는 프로그램을 작성하시오.

첫 번째 숫자가 두 번째 숫자의 약수이다.
첫 번째 숫자가 두 번째 숫자의 배수이다.
첫 번째 숫자가 두 번째 숫자의 약수와 배수 모두 아니다.
*/

#define FACTOR 1
#define MULTIPLE 2
#define NEITHER 3

int fn(int a, int b) {

	if (a%b == 0 && a > b) {
		return MULTIPLE;
	}
	else if (b > a && b%a == 0) {
		return FACTOR;
	}
	else {
		return NEITHER;
	}
}

int main() {

	int a;
	int b;

	int save;

	while (1) {
		scanf("%d %d", &a, &b);

		if (a == 0 && b == 0) {
			break;
		}

		save = fn(a, b);

		if (save == 1) {
			printf("factor\n");
		}
		else if (save == 2) {
			printf("multiple\n");
		}
		else {
			printf("neither\n");
		}
	}

	return 0;
} // 맞았습니다!! 