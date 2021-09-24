#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*https://www.acmicpc.net/problem/1463
정수 X에 사용할 수 있는 연산은 다음과 같이 세 가지 이다.

X가 3으로 나누어 떨어지면, 3으로 나눈다.
X가 2로 나누어 떨어지면, 2로 나눈다.
1을 뺀다.
정수 N이 주어졌을 때, 위와 같은 연산 세 개를 적절히 사용해서 1을 만들려고 한다. 연산을 사용하는 횟수의 최솟값을 출력하시오.

첫째 줄에 1보다 크거나 같고, 10^6보다 작거나 같은 정수 N이 주어진다.
*/
#define MAX 1000005
#define FINDMIN(IDX1, IDX2) IDX1 < IDX2 ? IDX1 : IDX2;

int arr[MAX];

int fn(int X) {

	switch (X)
	{
	case 1: 
		return 0;
		break;
	case 2: case 3:
		return 1;
		break;
	}

	if (arr[X] != 0) {
		return arr[X];
	}
	// X가 3으로 나눠떨어지면 그냥 그렇게 해서 바로 구한다.  
	if (X % 6 == 0) {
		arr[X] = FINDMIN(fn(X / 2) + 1, fn(X / 3) + 1);
	}
	else if (X % 3 == 0) {
		arr[X] = FINDMIN(fn(X - 1) + 1, fn(X / 3) + 1);	
	}
	else if (X % 2 == 0) {
		arr[X] = FINDMIN(fn(X - 1) + 1, fn(X / 2) + 1);
	}
	else {
		arr[X] = fn(X - 1) + 1;
	}

	return arr[X];
}


int main() {

	int N;
	scanf("%d", &N);

	printf("%d", fn(N));
	
	return 0;
} // 맞았습니다!
