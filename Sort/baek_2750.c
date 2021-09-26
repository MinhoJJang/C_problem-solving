#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
https://www.acmicpc.net/problem/2750
N개의 수가 주어졌을 때, 이를 오름차순으로 정렬하는 프로그램을 작성하시오.
*/


// 단순하게 1번2번, 2번3번, 3번4번 이렇게 비교하여 n-1번n번 까지 정렬하는게 1사이클. 그렇게 사이클을 반복한다. 
void BubbleSort(int arr[], int n) // 버블 정렬
{
	int i, j;
	int temp;

	// cycle 회전 횟수
	for (i = 0; i < n - 1; i++) {

		// 비교횟수
		for (j = 0; j < (n - i) - 1; j++) {

			// 1. 인접한 두개 비교 
			if (arr[j] > arr[j + 1]) // 2. 크기가 반대라면.. <<비교>>
			{
				temp = arr[j];		 // <<이동>> 한 사이클당 최대 (n-i)-1번 발생 (그냥 위 for문의 j최대치만큼 발생한다는 소리임)
				arr[j] = arr[j + 1]; // <<이동>>
				arr[j + 1] = temp;  // <<이동>>
			}
		}
	}
}

// 1번을 2번~n번까지 훑으면서 제일 작은 수와 위치를 바꿈. 그래서 '선택'정렬임. 제일 작은 수를 '선택'하니까
void SelectionSort(int arr[], int n) {

	int i, j;
	int temp;

	for (i = 0; i < n - 1; i++) // 비교 사이클 횟수 = n- 1번
	{
		int index = i;

		for (j = i + 1; j < n; j++)
			// 비교 arr[i] 와 arr[i+1]~arr[n-1]까지
		{
			if (arr[index] > arr[j]) {
				// arr[index]값보다 '더' 작은값을 찾아야하니까 if 조건식을 저렇게 쓰는 게 맞다. 나는 처음에 arr[i] > arr[j] 라고 써서 오류가 생겼다. 
				//<<비교>>
				index = j;
			}
		}

		if (index != i)
		{
			temp = arr[i];			 // <<이동>> 1사이클당 많아야 1번. 
			arr[i] = arr[index];	 // <<이동>>
			arr[index] = temp;		 // <<이동>>
		}
	}
}

// n개의 데이터 중에서 앞에서부터 i개 만큼을 정렬한다. 정렬 방식은 버블정렬과 비슷하나 뒤에서부터 정렬시작한다는 점, 정렬된 순간부터 break된다는 점에서 차이가 있음. 
void InsertionSort(int arr[], int n)
{
	int i, j;
	int insData; // 데이터 임시 보관소

	for (i = 1; i < n; i++) {

		insData = arr[i];

		for (j = i - 1; j >= 0; j--) {
			if (insData < arr[j]) { // 비교
				arr[j + 1] = arr[j];	  // <<이동>>
				// 바로 바로 값 바꿔주어야함
				// P.S. 그냥 위치를 찾는게 더 빠르지 않을까? 값을 바꾸는것보다..? 
				// 어차피 위치를 찾아도 자리이동해야하네..
			}
			else {
				break;
			}
		}
		arr[j + 1] = insData;  // <<이동>> 1사이클당 1번
	}
}

#define MAX 1005
int arr[MAX];

void printArr(int N) {
	for (int i = 0; i < N; i++) {
		printf("%d\n", arr[i]);
	}
}

void inputData(int N) {
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
}

int main() {

	int N;
	scanf("%d", &N);

	inputData(N);
	//InsertionSort(arr, N);
	//BubbleSort(arr, N);
	SelectionSort(arr, N);
	printArr(N);



	return 0;
}
