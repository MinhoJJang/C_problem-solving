#include <stdio.h>
#include <stdlib.h> // malloc, rand, atoi ..동적메모리, 난수, 문자열 변환
#include <string.h> //strcpy.. 문자열함수. memcpy.. 메모리블럭 함수
#pragma warning(disable:4996) // scnaf() 등 전통 c함수중 버퍼문제. 
#pragma warning(disable:4477) // unsigned <--> signed 관련 warning 무시 


/*
https://www.acmicpc.net/problem/2751
첫째 줄에 수의 개수 N(1 ≤ N ≤ 1,000,000)이 주어진다. 둘째 줄부터 N개의 줄에는 수가 주어진다. 이 수는 절댓값이 1,000,000보다 작거나 같은 정수이다. 수는 중복되지 않는다.
*/

// 배열 두개값 바꾸기
void Swap(int arr[], int idx1, int idx2)
{
	int temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
}

// 배열 정렬 영역 쪼개기 (쪼갤 index 리턴)
int Partition(int arr[], int left, int right) {

	int pivot = arr[left]; // 피벗의 위치는 가장 왼쪽! (값)
	int low = left + 1; // low 는 피벗 오른쪽에서 시작 (index)
	int high = right; // high 는 right 부터 시작 (index)

	// 
	while (low <= high) {
		//low 우측 이동, pivot 보다 큰 것을 만날때까지
		while (arr[low] <= pivot && low <= high) {
			low++;
		}

		// high 좌측 이동, pivot 보다 작은 것을 만날때까지!
		while (arr[high] >= pivot && high >= (left + 1)) {
			high--;
		}

		// low와 high가 멈추면
		if (low <= high) // low, high가 교차되지 않은 상태라면 Swap 진행
			Swap(arr, low, high);
	}

	// pivot과 high가 가리키는 대상교환
	Swap(arr, left, high);

	return high; // 옮겨진 피벗의 위치정보 리턴
}

// 재귀적으로 퀵정렬 수행
void QuickSort(int arr[], int left, int right)
{
	if (left <= right)
	{
		int pivot = Partition(arr, left, right); // pivot 정하고, 둘로쪼갬
		QuickSort(arr, left, pivot - 1); // pivot 왼쪽영역을 퀵정렬
		QuickSort(arr, pivot + 1, right); // pivot 오른쪽영역을퀵정렬
	}
}

#define MAX 1000005
int newArr[MAX];

void printArr(int N) {
	for (int i = 0; i < N; i++) {
		printf("%d\n", newArr[i]);
	}
}

void inputData(int N) {
	for (int i = 0; i < N; i++) {
		scanf("%d", &newArr[i]);
	}
}

int main() {

	int N;
	scanf("%d", &N);

	inputData(N);
	QuickSort(newArr, 0, N-1);
	printArr(N);

	return 0;
} // 시간초과 