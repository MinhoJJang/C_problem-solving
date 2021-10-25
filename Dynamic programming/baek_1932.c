#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
정수 삼각형

삼각형에 있는 모든 숫자에 대해, 그 숫자를 무조건 포함시킬 때 가능한 최댓값을 저장한다. 

*/

// ===========QUICKSORT===========
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
		// 오류있었음 (high인데 low라 적엇음)
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

void QuickSortMain(int arr[], int n)
{
	QuickSort(arr, 0, n - 1);
}
// =========QUICKSORT=========

#define MAX 505

int intTriangle[MAX][MAX] = { 0 };
int maxSum[MAX][MAX] = { 0 };
int N = 1;

// index 1부터 시작하자. 계산의 편의를 위해 
void putData() {

	scanf("%d", &N);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= i; j++) {
			scanf("%d", &intTriangle[i][j]);
		}
	}
}

int returnBigOne(int a, int b) {
	if (a < b) {
		return b;
	}
	return a;
}

// N = 1 부터 시작해서 입력받은 N까지 계속 구한다. 
void saveEveryMaxSum(int N, int inputN) {
	 
	while (N != inputN+1) {
		// 일단 당연히, 삼각형 맨 위에서는 그 숫자가 최대합이다. 
		if (N == 1) {
			maxSum[N][N] = intTriangle[N][N];
		}
		else {
			int idx = 1;
			while (idx != N + 1) {
				maxSum[N][idx] = intTriangle[N][idx] + returnBigOne(maxSum[N - 1][idx - 1], maxSum[N - 1][idx]);
				idx++;
			}
		}

		N++;
	}
}

void returnFinalMaxSum(int inputN) {

	QuickSortMain(maxSum[inputN], inputN+1);
	printf("%d", maxSum[inputN][inputN]);
}

int main() {

	putData();
	saveEveryMaxSum(1, N);
	returnFinalMaxSum(N);

	return 0;
}

// 맞았습니다! 
// 와 이걸 이렇게 한번에? 갑자기? 
