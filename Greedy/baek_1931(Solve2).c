#include <stdio.h>
#include <stdlib.h> // malloc, rand, atoi ..동적메모리, 난수, 문자열 변환
#include <string.h> //strcpy.. 문자열함수. memcpy.. 메모리블럭 함수
#pragma warning(disable:4996) // scnaf() 등 전통 c함수중 버퍼문제. 
#pragma warning(disable:4477) // unsigned <--> signed 관련 warning 무시

#define MAX 100050

#define SUCCESS 1
#define FAIL 0

#define GET_PARENT_IDX(idx) ((idx) >> 1) 
#define GET_LEFT_IDX(idx) ((idx) << 1) 
#define GET_RIGHT_IDX(idx) (((idx) << 1) + 1) 

#define COMP_ASC(d1, d2) ((d2)-(d1))  // 오름차순
#define COMP_DESC(d1, d2) ((d1)-(d2))  // 내림차순

/* Heap의 데이터*/

typedef int HData;

typedef int fnPriorityComp(HData d1, HData d2);
// d1의 우선순위가 높다면 0보다 큰 값 리턴 
// d2의 우선순위가 높다면 0보다 작은 값 리턴 
// d1 = d2면 0리턴

typedef struct _time {

	int startTime;
	int endTime;

} Time;
// 굉장히 오랜 시간 고민해서 만들었다.. Time이라는 구조체 형식을 갖는 배열 자체를 endTime을 키값으로 정렬시키면 되잖아?! 라는 생각을 하기까지.....ㅋㅋㅋ
// 이건 내가 힙 공부를 많이 안해서 그랬던것 같음

typedef struct _heap
{
	int numData; // 담고있는 데이터개수 
	Time *heapArr; // 동적메모리로 구현

} Heap;

// 힙정렬
Heap *g_hp;

// 함수 
int getHighPriority(Heap *ph, int idx)
{
	if (GET_LEFT_IDX(idx) > ph->numData) return 0;
	if (GET_LEFT_IDX(idx) == ph->numData) return GET_LEFT_IDX(idx);
	if (COMP_ASC(ph->heapArr[GET_LEFT_IDX(idx)].endTime, ph->heapArr[GET_RIGHT_IDX(idx)].endTime) < 0) {
		idx = GET_RIGHT_IDX(idx);
	}
	else {
		idx = GET_LEFT_IDX(idx);
	}

	return idx;
}

void heap_init(Heap *ph, int len) {
	ph->numData = 0; 
	ph->heapArr = (Time*)malloc(sizeof(Time)*(len + 1));

	g_hp = ph; 
}

int heap_is_empty(Heap *ph) {
	if (ph->numData == 0) return SUCCESS;
	return FAIL;
}

void heap_insert(Heap *ph, Time arr) {

	int idx = ph->numData + 1;

	while (idx != 1) 
	{	
		if (COMP_ASC(arr.endTime, ph->heapArr[GET_PARENT_IDX(idx)].endTime) > 0) 
		{	
			ph->heapArr[idx] = ph->heapArr[GET_PARENT_IDX(idx)];
			idx = GET_PARENT_IDX(idx);
		}
		else
		{
			break;
		}
	}

	ph->heapArr[idx] = arr;
	ph->numData++;
}

// startTime정렬용 함수
void start_heap_insert(Heap *ph, Time arr) {

	int idx = ph->numData + 1;
	while (idx != 1)
	{
		if (COMP_ASC(arr.startTime, ph->heapArr[GET_PARENT_IDX(idx)].startTime) > 0)
		{
			ph->heapArr[idx] = ph->heapArr[GET_PARENT_IDX(idx)];
			idx = GET_PARENT_IDX(idx);
		}
		else
		{
			break;
		}
	}

	ph->heapArr[idx] = arr;
	ph->numData++;
}

// 힙에 데이터 빼기 delete. 삭제는 root에서 발생 
Time heap_delete(Heap *ph) {

	Time rootData = ph->heapArr[1]; 
	Time lastElement = ph->heapArr[ph->numData];
	
	int idx = 1; 
	int childIdx;

	while (childIdx = getHighPriority(ph, idx))
	{
		if (COMP_ASC(lastElement.endTime, ph->heapArr[childIdx].endTime) >= 0) break;

		ph->heapArr[idx] = ph->heapArr[childIdx];
		idx = childIdx;
	}

	ph->heapArr[idx] = lastElement;
	ph->numData--;

	return rootData;
}

// startTime정렬용 함수
Time start_heap_delete(Heap *ph) {

	Time rootData = ph->heapArr[1];
	Time lastElement = ph->heapArr[ph->numData];

	int idx = 1;
	int childIdx;

	while (childIdx = getHighPriority(ph, idx))
	{
		if (COMP_ASC(lastElement.startTime, ph->heapArr[childIdx].startTime) >= 0) break;

		ph->heapArr[idx] = ph->heapArr[childIdx];
		idx = childIdx;
	}

	ph->heapArr[idx] = lastElement;
	ph->numData--;

	return rootData;
}

void HeapSort(Time arr[], int n)
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

// startTime정렬용 함수
void newHeapSort(Time arr[], int n, int startP, int finishP)
{
	int i;
	for (i = startP; i <= finishP; i++)
	{
		start_heap_insert(g_hp, arr[i]);
	}
	for (i = startP; i <= finishP; i++)
	{
		arr[i] = start_heap_delete(g_hp);
	}
	// 그냥 insert하고 그대로 delete하면 arr에 정렬된 순서대로 데이터가 들어올것임.
}

// 구조체 타입의 배열을 전역변수로 설정.
Time arr[MAX];

void putDataTime(int N) {

	for (int i = 0; i < N; i++) {
		scanf("%d %d", &arr[i].startTime, &arr[i].endTime);
	}
}

void sortEndTime(int N) {
	Heap hp;
	heap_init(&hp, N);
	HeapSort(arr, N);
}

// 오답이유_>만약 끝나는 시간이 같을 때, 시작하는 시간도 정렬해야함. 
/*
끝나는 시간이 같다면 -> 처음 y값을 변수에 저장. 이후로 idx++시키면서 y 값과 변수값이 같은지 확인

1. 같다면 -> 그 idx값을 따로 저장하고, 그 뒤로 계속 조사하면서 다른 y값이 나올때까지 범위 찾는다. 이후 y값이 같은 x들 끼리 heapsort시킨다. 그게 끝나면 다른 y값이 나오는 지점에 idx를 박아넣고 다시 진행.

2. 다르다면 -> 변수에 그 y값 넣고 다시 진행

--> 더이상 조사할 y가 없을 때까지 진행
*/
void sortStartTimesIfEndTimeIsSame(int N) {

	// y값을 저장하는 변수
	int storeCurrentEndTime;
	int endTimeIndex = 0;

	// 일단 맨 처음의 endtime
	storeCurrentEndTime = arr[endTimeIndex].endTime;

	// 더이상 y를 조사할 수 없을 때까지 
	while(endTimeIndex < N-1) {

		// 그 다음 endtime이랑 같은지 조사 
		// 만약 같으면 
		if (storeCurrentEndTime == arr[endTimeIndex + 1].endTime) {

			int startIndex = endTimeIndex; // 시작 위치 저장하고 
			int finishIndex; // 마지막 위치도 저장

			int searchIndex = startIndex + 2; // 시작위치 +2 부터 조사 

			// 계속 다음 endtime 조사.. 다른 endtime이 나오거나, N이 되기 전 까지 지속
			while (arr[searchIndex].endTime == storeCurrentEndTime && searchIndex < N) {
				searchIndex++;
			}
			// 만약 searchIndex가 N-2를 넘어서지 않았다면, storeCurrentEndTime 새로 바꿔줌
			if (searchIndex <= N - 2) {
				storeCurrentEndTime = arr[searchIndex].endTime;
			}

			finishIndex = searchIndex - 1; // 마지막 위치는 서치-1임
			endTimeIndex = searchIndex; // endTime위치 바꿔줌

			// startTime을 startindex부터 finish까지 정렬
			Heap startHeap;
			heap_init(&startHeap, finishIndex - startIndex + 1);
			newHeapSort(arr, finishIndex - startIndex + 1, startIndex, finishIndex);
		}
		// 다르면 
		else {
			storeCurrentEndTime = arr[endTimeIndex + 1].endTime;
			endTimeIndex++;
		}
	}
}

int findMaxNumberOfMeeting(int N) {

	int meetCount = 0;
	int idx = 0;

	int saveLastEndTime;

	// 맨 처음 회의는 무조건 할 것임. 
	saveLastEndTime = arr[idx].endTime;
	meetCount++;
	idx++;

	// 더이상 찾을 수 있는 회의가 없을때까지
	while (idx != N) {

		// 만약 그 다음 회의의 시작시간이 전 회의의 끝나는 시간보다 같거나 크다면
		if (arr[idx].startTime >= saveLastEndTime) {
			meetCount++;
			saveLastEndTime = arr[idx].endTime;
		}

		idx++;
	}

	return meetCount;
}

// 테스트용
void testPrint(int N) {
	for (int i = 0; i < N; i++) {
		printf("%d %d\n", arr[i].startTime, arr[i].endTime);
	}
}

int main() {

	int N;
	scanf("%d", &N);
	
	putDataTime(N);
	sortEndTime(N);
	sortStartTimesIfEndTimeIsSame(N);
	
	printf("%d", findMaxNumberOfMeeting(N));

	return 0;
} 

// 맞았습니다!!!!
// 이게 실버 2라고??? 아니 왜?
// 2차원 정렬하는법 배운 굉장히 좋은 문제 
