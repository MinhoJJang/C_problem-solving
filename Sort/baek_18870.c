#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
수직선 위에 N개의 좌표 X1, X2, ..., XN이 있다. 이 좌표에 좌표 압축을 적용하려고 한다.
Xi를 좌표 압축한 결과 X'i의 값은 Xi > Xj를 만족하는 서로 다른 좌표의 개수와 같아야 한다.
X1, X2, ..., XN에 좌표 압축을 적용한 결과 X'1, X'2, ..., X'N를 출력해보자.
*/

/*
1. 일단 입력받은 수의 위치와 그 수의 값을 저장한다. 
2. 가장 작은 수에 있는 인덱스의 값을 0으로 하고, 수가 점점 커짐에 따라서 1,2,3...이렇게 증가시켜서 넣어준다. 

*/

#define MAX_INPUT 1000005

typedef struct _coordinate {
	int index;
	int num;
} cor;

cor arr[MAX_INPUT] = { 0 };

// 수 입력받기 
void putData(int n){

	for (int i = 0; i < n; i++) {
		arr[i].index = i;
		scanf("%d", &arr[i].num);
	}
}

// arr을 정렬하는데, arr[i].num 값을 키로 정렬한다. 
void Swap(cor arr[], int idx1, int idx2)
{
	cor temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
}

// 배열 정렬 영역 쪼개기 (쪼갤 index 리턴)
int Partition(cor arr[], int left, int right) {

	int pivot = arr[left].num; // 피벗의 위치는 가장 왼쪽! (값)
	int low = left + 1; // low 는 피벗 오른쪽에서 시작 (index)
	int high = right; // high 는 right 부터 시작 (index)

	// 
	while (low <= high) {
		//low 우측 이동, pivot 보다 큰 것을 만날때까지
		while (arr[low].num <= pivot && low <= high) {
			low++;
		}

		// high 좌측 이동, pivot 보다 작은 것을 만날때까지!
		while (arr[high].num >= pivot && high >= (left + 1)) {
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
void QuickSort(cor arr[], int left, int right)
{
	if (left <= right)
	{
		int pivot = Partition(arr, left, right); // pivot 정하고, 둘로쪼갬
		QuickSort(arr, left, pivot - 1); // pivot 왼쪽영역을 퀵정렬
		QuickSort(arr, pivot + 1, right); // pivot 오른쪽영역을퀵정렬
	}
}

//void printArr(int n) { // 테스트함수
//	for (int i = 0; i < n; i++) {
//		printf("%d ", arr[i].num);
//	}
//}

int answerArr[MAX_INPUT] = { 0 };

void fn(int n) {

	int beforeNum = 0;
	int currentNum = 0;

	for (int i = 0; i < n; i++) {

		if (i == 0) {
			// 맨 처음은 무조건 0일테니까
			answerArr[arr[i].index] = 0;
		}
		// 바로 전에 num값과 현재 num값을 비교하여 같은지 다른지에 따라 if, else 해주자 
		else {
			beforeNum = arr[i - 1].num;
			currentNum = arr[i].num;
			if (beforeNum == currentNum) {
				// 값이 같으니 당연히 좌표압축한 값도 같아야 한다. 
				answerArr[arr[i].index] = answerArr[arr[i-1].index];
			}
			else {
				answerArr[arr[i].index] = answerArr[arr[i - 1].index] + 1;
			}
		}
	}
}

void printAnswer(int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", answerArr[i]);
	}
}

int main() {

	int n;
	scanf("%d", &n);
	putData(n);
	QuickSort(arr, 0, n-1);
	// 이때, 맨 처음 인덱스 번호에다가 0을 넣고, 그 다음에 숫자비교해서 같으면 0, 크면 1넣고..이런식
	fn(n);
	printAnswer(n);

	return 0;
}