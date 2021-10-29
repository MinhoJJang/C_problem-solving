#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
수열 A가 주어졌을 때, 가장 긴 증가하는 부분 수열을 구하는 프로그램을 작성하시오.

예를 들어, 수열 A = {10, 20, 10, 30, 20, 50} 인 경우에 가장 긴 증가하는 부분 수열은 A = {10, 20, 10, 30, 20, 50} 이고, 길이는 4이다.
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

#define MAX 1005
#define LEFT -10
#define RIGHT 10
#define SAME 0

#define LENGTH 0
#define LATEST_NUM 1
#define JUST_BEFORE_NUM 2
#define JUST_BEFORE_NUM_INDEX 3
#define CURRENT_NUM_INDEX 4

int arr[5][MAX] = { 0 };
int num[MAX] = { 0 };
int N;

void putData() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &num[i]);
	}
}

int whichIsBig(int a, int b) {
	if (a > b) {
		return LEFT;
	}
	else if (a < b){
		return RIGHT;
	}
	else {
		return SAME;
		// LCS 마지막 숫자와 지금 조사하는 정수의 값이 같다면 새로운 조사식을 도입해야 한다. 
	}
}

int idx = 0;
int point = 0; 
int flag;


// int checkMax(int a){

// 	if(a==1){
// 		return 1;
// 	}

// 	return checkMax(a-1)*2 + 1;

// 	// 4294967295 모든 경우의 수를 저장한다는 건 말도안되는 소리 
// }

void fn(int N) {

	while (idx != N) {
		// 맨 첫번째 수는 당연히 N=1일때 가장 긴 증가하는 수열일 것이다.
		if (idx == 0) {
			arr[LENGTH][idx] = 1;
			arr[LATEST_NUM][idx] = num[idx];
			arr[CURRENT_NUM_INDEX][idx] = idx;
		}
		else {
			// ideas
			// idx >= 1일때...
			// 두 가지 경우로 나뉜다. A,B일때 A<B이거나 A>=B이거나. 
			// A=B일때는 일단 적어도 증가하지는 않으니까..
			// flag = whichIsBig(num[idx - 1], num[idx]); 바로 전 정수와 비교하는 것은 의미가 없다. 

			// 1. 일단, 입력된 전체 수열의 정수는 곧 어떤 LCS의 시작 부분이 될 수 있다. 따라서 일단 idx를 올릴 때, 그 정수를 배열에 넣어주자.
			arr[LENGTH][idx] = 1;
			arr[LATEST_NUM][idx] = num[idx];
			arr[CURRENT_NUM_INDEX][idx] = idx;

			// 2. 그리고, 지금까지 생성된 모든 가능한 경우의 LCS에 대하여, 현재 정수가 과연 그 LCS에 포함될 수 있는가에 대하여 조사해야 한다. 포함될 수 있는 경우와 아닌 경우로 나눈다. 만약 숫자가 같다면 논리가 추가된 로직을 만들어야한다. 
			for(int search = 0; search < idx; search++){
				// 모든 LCS의 마지막 값과 현재 숫자값을 비교한다. 
				flag = whichIsBig(arr[LATEST_NUM][search], num[idx]);

				// 만약 LCS의 마지막 값이 현재 숫자값보다 크다면..
				if(flag == LEFT) {
					
					// 예를 들어 1 5 2 3 같은 경우..? 

					// 1 저장
					// 1 에다 5를 더하는게 아니라, 1과 1,5, 5 이렇게 세 개를 저장해야됨. 
					// 그러니까 2차례가 되면 1, 1,5, 1,2, 5, 2 이렇게 저장해야 되는것. 
			
					// 1 2 3 4 면

					// 1
					// 1, 12, 2
					// 1, 12 ,2, 13, 123, 23, 3
					// ... 

					

					
					
				}
				// 만약 LCS의 마지막 값이 현재 숫자값보다 작다면..
				else if(flag == RIGHT){

					arr[LENGTH][search]++; 
					// 수열의 길이를 올려준다.

					arr[JUST_BEFORE_NUM][search] = arr[LATEST_NUM][search]; 
					// 수열에서 방금전까지 최댓값이었던 값을 저장한다.

					arr[JUST_BEFORE_NUM_INDEX][search] = arr[CURRENT_NUM_INDEX][search]; 
					// 수열에서 방금전까지 최댓값 위치에 있던 인덱스를 저장한다. 

					arr[LATEST_NUM][search] = num[idx];
					// 이제 변경된 수열의 최댓값을 현재 입력된 배열의 숫자값으로 바꿔준다.

					arr[CURRENT_NUM_INDEX][search] = idx;
					// 그 숫자값의 인덱스를 저장한다. 
				}
				// 만약 LCS의 마지막 값이 현재 숫자값보다 같다면..
				else if(flag == SAME){
					// 숫자값이 같아지면 문제가 조금 복잡해진다. 현재 LCS의 최댓값 숫자 위치부터 그 최댓값과 같은 현재 숫자의 위치 바로 전까지를 알아야 한다.
					// 예를 들어 10, 20, 50, 10, 25,30, 50 이런 경우를 생각해볼 때, 50과 50 사이 위치에 있는 모든 숫자에 대해 20보다 크고 50보다 작은지 검사한다. 즉 FOR문을 다시 돌려야 한다. 

					int startIdx;
					int endIdx;
					int newLargestNum;
					int newSearch;
					int newFlag;

					// 현재 LCS의 가장 큰 수의 위치를 저장
					startIdx = arr[CURRENT_NUM_INDEX][search];

					// 현재 num[idx] 의 위치를 저장
					endIdx = idx;

					// 그 LCS의 최댓값을 임시로 바로 전까지 최댓값이었던 값으로 바꿔준다. 
					newLargestNum = arr[JUST_BEFORE_NUM][search];

					// LCS의 개수도 일단 1개 줄여주자.
					arr[LENGTH][search]--;

					// 그리고 조사에 들어간다. 
					for(newSearch = startIdx + 1; newSearch <= idx; newSearch++){
						newFlag = whichIsBig(newLargestNum, num[newSearch]);

						// 일단 그 사이에 같은 값이 있을 수가 없다. 있다면 로직이 잘못된 것. 
					}

				}
			}
			

			
		}

		idx++;
	}
}

int main() {

	// putData();
	// fn(N);
	// QuickSortMain(arr[LENGTH], N);
	// printf("%d", arr[LENGTH][N-1]);
	printf("%ld",checkMax(1000));

	return 0;
}