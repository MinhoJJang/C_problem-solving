#include <stdio.h>
#include <stdlib.h> // malloc, rand, atoi ..동적메모리, 난수, 문자열 변환
#include <string.h> //strcpy.. 문자열함수. memcpy.. 메모리블럭 함수
#pragma warning(disable:4996) // scnaf() 등 전통 c함수중 버퍼문제. 
#pragma warning(disable:4477) // unsigned <--> signed 관련 warning 무시 

/*
크기가 N인 수열 A = A1, A2, ..., AN이 있다. 수열의 각 원소 Ai에 대해서 오큰수 NGE(i)를 구하려고 한다. Ai의 오큰수는 오른쪽에 있으면서 Ai보다 큰 수 중에서 가장 왼쪽에 있는 수를 의미한다. 그러한 수가 없는 경우에 오큰수는 -1이다.

예를 들어, A = [3, 5, 2, 7]인 경우 NGE(1) = 5, NGE(2) = 7, NGE(3) = 7, NGE(4) = -1이다. A = [9, 5, 4, 8]인 경우에는 NGE(1) = -1, NGE(2) = 8, NGE(3) = 8, NGE(4) = -1이다.

첫째 줄에 수열 A의 크기 N (1 ≤ N ≤ 1,000,000)이 주어진다. 둘째에 수열 A의 원소 A1, A2, ..., AN (1 ≤ Ai ≤ 1,000,000)이 주어진다.

총 N개의 수 NGE(1), NGE(2), ..., NGE(N)을 공백으로 구분해 출력한다.
*/

int arr[1000005] = { 0 };
// 전역변수로 선언시 백만개 배열도 선언가능

int main() {

	int N = 0;
	int idx = 0;
	int num = 0;

	scanf("%d", &N); // 수열 A의 크기 

	for (int i = 0; i < N; i++) {
		scanf("%d", &num);
		arr[i] = num;
	} // 배열에 수 담기 

	for (int k = 0; k < N; k++) {
		for (int t = k + 1; t <= N; t++) {

			idx = arr[t] - arr[k];

			if (idx > 0) {
				arr[k] = arr[t];
				break;
			}
			if (t == N)
			{
				arr[k] = -1;
				break;
			}
		}

	}

	for (int s = 0; s < N; s++) {
		printf("%d ", arr[s]);
	}

	return 0;
} // 시간초과 - 38%

// O(n^2) 이기 때문에.. 