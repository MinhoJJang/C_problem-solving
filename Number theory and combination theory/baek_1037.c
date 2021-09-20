#include <stdio.h>
#include <stdlib.h> // malloc, rand, atoi ..동적메모리, 난수, 문자열 변환
#include <string.h> //strcpy.. 문자열함수. memcpy.. 메모리블럭 함수
#pragma warning(disable:4996) // scnaf() 등 전통 c함수중 버퍼문제. 
#pragma warning(disable:4477) // unsigned <--> signed 관련 warning 무시 
#include <math.h>

#ifndef __HEAP_H__
#define __HEAP_H__

/*
https://www.acmicpc.net/problem/1037
양수 A가 N의 진짜 약수가 되려면, N이 A의 배수이고, A가 1과 N이 아니어야 한다. 어떤 수 N의 진짜 약수가 모두 주어질 때, N을 구하는 프로그램을 작성하시오.

첫째 줄에 N의 진짜 약수의 개수가 주어진다. 이 개수는 50보다 작거나 같은 자연수이다. 둘째 줄에는 N의 진짜 약수가 주어진다. 1,000,000보다 작거나 같고, 2보다 크거나 같은 자연수이고, 중복되지 않는다.
*/

/* Heap의 데이터*/

typedef int HData;

typedef int fnPriorityComp(HData d1, HData d2);
// d1의 우선순위가 높다면 0보다 큰 값 리턴 
// d2의 우선순위가 높다면 0보다 작은 값 리턴 
// d1 = d2면 0리턴

typedef struct _heap
{
	int numData; // 담고있는 데이터개수 
	HData *heapArr; // 동적메모리로 구현
	fnPriorityComp *comp; // 우선순위 비교함수 

} Heap;

/* Heap의 동작*/

// 힙 초기화
void heap_init(Heap *ph, int len);
void heap_destroy(Heap *ph);

// 힙이 비어있는지? 
int heap_is_empty(Heap *ph);

// 힙에 데이터 추가 insert
void heap_insert(Heap *ph, HData data);

// 힙에 데이터 빼기 delete
HData heap_delete(Heap *ph);

// 힙정렬
Heap *g_hp;
void HeapSort(int arr[], int n);

#endif

#define SUCCESS 1
#define FAIL 0

#define GET_PARENT_IDX(idx) ((idx) >> 1) 
#define GET_LEFT_IDX(idx) ((idx) << 1) 
#define GET_RIGHT_IDX(idx) (((idx) << 1) + 1) 

#define COMP_ASC(d1, d2) ((d2)-(d1)) 
#define COMP_DESC(d1, d2) ((d1)-(d2)) 

int getHighPriority(Heap *ph, int idx)
{
	if (GET_LEFT_IDX(idx) > ph->numData) return 0;
	if (GET_LEFT_IDX(idx) == ph->numData) return GET_LEFT_IDX(idx);
	if (COMP_ASC(ph->heapArr[GET_LEFT_IDX(idx)], ph->heapArr[GET_RIGHT_IDX(idx)]) < 0) {
		idx = GET_RIGHT_IDX(idx);
	}
	else {
		idx = GET_LEFT_IDX(idx);
	}

	return idx;
}

void heap_init(Heap *ph, int len) {
	ph->numData = 0;
	ph->heapArr = (int*)malloc(sizeof(int)*(len + 1));

	g_hp = ph;
}

int heap_is_empty(Heap *ph) {
	if (ph->numData == 0) return SUCCESS;
	return FAIL;
}

void heap_insert(Heap *ph, HData data) {

	int idx = ph->numData + 1;

	while (idx != 1)
	{
		if (COMP_ASC(data, ph->heapArr[GET_PARENT_IDX(idx)]) > 0)
		{
			ph->heapArr[idx] = ph->heapArr[GET_PARENT_IDX(idx)];
			idx = GET_PARENT_IDX(idx);
		}
		else
		{
			break;
		}
	}

	ph->heapArr[idx] = data;
	ph->numData++;
}

// 힙에 데이터 빼기 delete. 삭제는 root에서 발생 
HData heap_delete(Heap *ph) {

	HData rootData = ph->heapArr[1];
	HData lastElem = ph->heapArr[ph->numData];

	int idx = 1;
	int childIdx;

	while (childIdx = getHighPriority(ph, idx))
	{
		if (COMP_ASC(lastElem, ph->heapArr[childIdx]) >= 0) break;

		ph->heapArr[idx] = ph->heapArr[childIdx];

		idx = childIdx;
	}
	ph->heapArr[idx] = lastElem;
	ph->numData--;

	return rootData;
}

void HeapSort(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		heap_insert(g_hp, arr[i]);
	}
	for (i = 0; i < n; i++)
	{
		arr[i] = heap_delete(g_hp);
	}
	// 그냥 insert하고 그대로 delete하면 arr에 정렬된 순서대로 데이터가 들어올것임.
}

#define MAX 100

int numArr[MAX] = { 0 };

int main() {

	Heap hp;

	int numberofNum;
	
	scanf("%d", &numberofNum);

	for (int i = 0; i < numberofNum; i++) {
		scanf("%d", &numArr[i]);
	}

	if (numberofNum > 1) {
		heap_init(&hp, numberofNum);
		HeapSort(numArr, numberofNum);
		printf("%d", numArr[0] * numArr[numberofNum - 1]);
	}
	else {
		long t = (long)pow(numArr[0], 2);
		printf("%ld", t);
	}

	return 0;
} // 맞았습니다