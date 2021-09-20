#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
https://www.acmicpc.net/problem/1934

두 자연수 A와 B에 대해서, A의 배수이면서 B의 배수인 자연수를 A와 B의 공배수라고 한다. 이런 공배수 중에서 가장 작은 수를 최소공배수라고 한다. 예를 들어, 6과 15의 공배수는 30, 60, 90등이 있으며, 최소 공배수는 30이다.

두 자연수 A와 B가 주어졌을 때, A와 B의 최소공배수를 구하는 프로그램을 작성하시오.

첫째 줄에 테스트 케이스의 개수 T(1 ≤ T ≤ 1,000)가 주어진다. 둘째 줄부터 T개의 줄에 걸쳐서 A와 B가 주어진다. (1 ≤ A, B ≤ 45,000)

유클리드 호제법 -> a>b일떄 a를 b로 나눈 나머지를 r이라 하자. 이제 b를 r로 나눈 나머지를 r1이라 하자. r을 r1으로 나눈 나머지를 ... 해서 나머지가 0이 될 때의 나눈 수가 바로 최소공배수. 
*/

int ansArr[1005] = { 0 };

// 최소공배수 구하기
int findGCM(int a, int b) {

	// x>y
	int x = (a > b) ? a : b;
	int y = a + b - x;

	int rest = x % y;
	if (rest == 0) {
		return y;
	}
	
	return findGCM(y, rest);
}

int findLCM(int a, int b) {

	return a * b / findGCM(a, b);
}

int setAns(int Testcase) {

	int a;
	int b;

	for (int i = 0; i < Testcase; i++) {
		scanf("%d%d", &a, &b);
		ansArr[i] = findLCM(a, b);
	}

	for (int i = 0; i < Testcase; i++) {
		printf("%d\n", ansArr[i]);
	}
}

int main() {

	int Testcase;
	scanf("%d", &Testcase);
	
	setAns(Testcase);

	return 0;
}