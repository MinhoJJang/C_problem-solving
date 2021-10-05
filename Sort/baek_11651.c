#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

#define X 0
#define Y 1
#define MAX 100005

/*
구조체 타입의 배열선언 후 배열을 정렬하는 키를 바꾸는 문제
*/

typedef struct _coordinate {
	int x;
	int y;
} cord;

cord inputArr[MAX] = { 0 };

// == QuickSort ==

// 배열 두개값 바꾸기
void Swap(cord arr[], int idx1, int idx2)
{
	cord temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
}

// 배열 정렬 영역 쪼개기 (쪼갤 index 리턴)
int Partition(cord arr[], int left, int right) {

	int pivot = arr[left].y; // 피벗의 위치는 가장 왼쪽! (값)
	int low = left + 1; // low 는 피벗 오른쪽에서 시작 (index)
	int high = right; // high 는 right 부터 시작 (index)

	// 
	while (low <= high) {
		//low 우측 이동, pivot 보다 큰 것을 만날때까지
		while (arr[low].y <= pivot && low <= high) {
			low++;
		}

		// high 좌측 이동, pivot 보다 작은 것을 만날때까지!
		// 오류있었음 (high인데 low라 적엇음)
		while (arr[high].y >= pivot && high >= (left + 1)) {
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
void QuickSort(cord arr[], int left, int right)
{
	if (left <= right)
	{
		int pivot = Partition(arr, left, right); // pivot 정하고, 둘로쪼갬
		QuickSort(arr, left, pivot - 1); // pivot 왼쪽영역을 퀵정렬
		QuickSort(arr, pivot + 1, right); // pivot 오른쪽영역을퀵정렬
	}
}

void QuickSortMain(cord arr[], int n)
{
	QuickSort(arr, 0, n - 1);
}

// ==== 
void QuickSort_X(cord arr[], int left, int right)
{
	if (left <= right)
	{
		int pivot = Partition_X(arr, left, right); // pivot 정하고, 둘로쪼갬
		QuickSort_X(arr, left, pivot - 1); // pivot 왼쪽영역을 퀵정렬
		QuickSort_X(arr, pivot + 1, right); // pivot 오른쪽영역을퀵정렬
	}
}

void QuickSortMain_X(cord arr[], int start, int end)
{
	QuickSort_X(arr, start, end);
}

int Partition_X(cord arr[], int left, int right) {

	int pivot = arr[left].x; // 피벗의 위치는 가장 왼쪽! (값)
	int low = left + 1; // low 는 피벗 오른쪽에서 시작 (index)
	int high = right; // high 는 right 부터 시작 (index)

	// 
	while (low <= high) {
		//low 우측 이동, pivot 보다 큰 것을 만날때까지
		while (arr[low].x <= pivot && low <= high) {
			low++;
		}

		// high 좌측 이동, pivot 보다 작은 것을 만날때까지!
		// 오류있었음 (high인데 low라 적엇음)
		while (arr[high].x >= pivot && high >= (left + 1)) {
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
// ==Additional Method==

// y값이 같으면 x좌표를 정렬해야 하니까 
void x_cord_sort(int N) {
	for (int i = 0; i < N - 1; i++) {
		// 만약 i번째 y값과 i+1번쨰 y값이 같으면 조사 시작.
		if (inputArr[i].y == inputArr[i + 1].y) {
			int startIdx = i; // 시작위치 
			int tempIdx = i + 1; // 임시위치설정
			// i+1부터 또 y값이 같은 좌표가 있는지 검사 
			while (inputArr[tempIdx].y == inputArr[tempIdx + 1].y) {
				tempIdx++;
			}
			int endIdx = tempIdx; // 다 찾았으면 마지막 위치를 설정
			i = endIdx; // endIdx다음부터 다시 찾으면 되므로

			// 이제 정렬한다.
			QuickSortMain_X(inputArr, startIdx, endIdx);
		}
	}
}

void setData(int N) {
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &inputArr[i].x, &inputArr[i].y);
	}
}

void printData(int N) {
	for (int i = 0; i < N; i++) {
		printf("%d %d\n", inputArr[i].x, inputArr[i].y);
	}
}

int main() {

	int N;
	scanf("%d", &N);

	setData(N);
	QuickSortMain(inputArr, N);

	// 이상태의 배열에서 y값이 같은게 있는지 조사 
	x_cord_sort(N);

	printData(N);

	return 0;
} // 맞았습니다! 

// 11650이랑 똑같은문제임 그냥