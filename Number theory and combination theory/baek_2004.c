#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
nCm 의 끝자리 $0$의 개수를 출력하는 프로그램을 작성하시오.
*/

/*
그냥 분자 분모 5의 개수 구하면 되지 않나? 

분자의 5개수 - 분모의 5개수 하면 될듯? 

nCm 이니까, n의 5개수 - (m의 5개수 + n-m의 5개수)
물론 2의 개수도 세야됨 
*/
int n;
int m;

int numberOfZero_five(int a) {

	int cnt_five = 0;

	while (a >= 5) {
		cnt_five += (a / 5);
		a /= 5;
	}

	return cnt_five;
}

int numberOfZero_two(int b) {

	int cnt_two = 0;
	while (b >= 2) {
		cnt_two += (b / 2);
		b /= 2;
	}

	return cnt_two;
}


void putData() {
	scanf("%d %d", &n, &m);
}

int returnSmallOne(int a, int b) {
	if (a < b) {
		return a;
	}
	return b;
}

void fn() {
	
	int five = 0;
	int two = 0;

	five = numberOfZero_five(n) - (numberOfZero_five(m) + numberOfZero_five(n - m));

	two = numberOfZero_two(n) - (numberOfZero_two(m) + numberOfZero_two(n - m));

	printf("%d",returnSmallOne(five, two));
}

int main() {

	putData();
	fn();

	return 0;
}

// 맞았습니다! 