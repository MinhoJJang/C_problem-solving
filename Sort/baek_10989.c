#include <stdio.h>
#include <stdlib.h> // malloc, rand, atoi ..동적메모리, 난수, 문자열 변환
#include <string.h> //strcpy.. 문자열함수. memcpy.. 메모리블럭 함수
#pragma warning(disable:4996) // scnaf() 등 전통 c함수중 버퍼문제. 
#pragma warning(disable:4477) // unsigned <--> signed 관련 warning 무시 

#define MAX 10002
int arr[MAX] = { 0 };

void printArr(int N) {

	// 입력된 수가 자연수이므로 
	int idx = 1;
	int k;
	
	for (k = arr[idx]; idx < MAX; idx++) {
		
		for (int i = 0; i < k; i++) {
			printf("%d\n", idx);
		}

		k = arr[idx + 1];
	}

}

void inputData(int N) {
	int idx;
	for (int i = 0; i < N; i++) {
		scanf("%d", &idx);
		arr[idx]++;
	}
}

int main() {

	int N;
	scanf("%d", &N);
	inputData(N);
	printArr(N);

	return 0;
} // 메모리초과????? 

// 1. 입력을저장하지 않고 푸는 법
// 2. 입력되는 정수의 범위가 10000개 뿐이므로, 이것을 이용
// 어케?

// 배열 arr[10005] = {0};를 만들고, 입력된 숫자가 i면 arr[i]++되도록 만들자.

// 맞았습니다!! 