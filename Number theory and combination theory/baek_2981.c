#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <math.h>
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

#define SUCCESS 1
#define FAIL 0

typedef int HData;

typedef int fnPriorityComp(HData d1, HData d2);
// 두 데이터를 비교해 어떤 것이 크거나 같은지 알아내는 함수-의 타입을 정의한것임.. 
// d1의 우선순위가 높다면 0보다 큰 값 리턴 
// d2의 우선순위가 높다면 0보다 작은 값 리턴 
// d1 = d2면 0리턴

typedef struct _heap
{
	int numData; // 담고있는 데이터개수 
	HData *heapArr; // 동적메모리로 구현
	fnPriorityComp *comp; // 우선순위 비교함수 
	// 함수타입 포인터 comp
} Heap;

// 힙정렬
Heap *g_hp;

// -----------------------------------------
// 노드 인덱스 계산 매크로 (성능 향상)
#define GET_PARENT_IDX(idx) ((idx) >> 1) // idx/2 우측으로 shift동작
// 함수호출이 아니라 해당 함수를 그냥 대입시킴. 시간적 이득
#define GET_LEFT_IDX(idx) ((idx) << 1) // idx*2 = 좌측으로 1칸
#define GET_RIGHT_IDX(idx) (((idx) << 1) + 1) // 상수연산자가 비트연산자보다 우선순위가 크므로 괄호 묶어주기 

// 비교함수 대신 매크로 (성능 up)
#define COMP_ASC(d1, d2) ((d2)-(d1)) // 오름차순
#define COMP_DESC(d1, d2) ((d1)-(d2)) // 내림차순

// idx의 자식들 중 우선순위가 높은 자식의 index값 리턴 --> delete 에 사용 
int getHighPriority(Heap *ph, int idx)
{
	// 자식노드가 없다면 0리턴 
	if (GET_LEFT_IDX(idx) > ph->numData) return 0;

	// 자식노드가 1개라면 (왼쪽 노드가 유일)
	if (GET_LEFT_IDX(idx) == ph->numData) return GET_LEFT_IDX(idx);

	// 우선순위 
	if (COMP_ASC(ph->heapArr[GET_LEFT_IDX(idx)], ph->heapArr[GET_RIGHT_IDX(idx)]) < 0) {
		idx = GET_RIGHT_IDX(idx);
	}
	else {
		idx = GET_LEFT_IDX(idx);
	}

	return idx;
}

// 힙 초기화
void heap_init(Heap *ph, int len) {
	ph->numData = 0; // 데이터(노드)개수 0
	ph->heapArr = (int*)malloc(sizeof(int)*(len + 1));
	
	g_hp = ph; // 힙정렬에 필요

}

void heap_destroy(Heap *ph) {
	free(ph->heapArr);
	memset(ph, 0, sizeof(Heap));
}

// 힙이 비어있는지? 
int heap_is_empty(Heap *ph) {
	if (ph->numData == 0) return SUCCESS;
	return FAIL;
}

// 힙에 데이터 추가 insert
void heap_insert(Heap *ph, HData data) {

	// 새로 insert되는 데이터는 맨 끝에서 시작 
	int idx = ph->numData + 1;
	// ph->numData 는 현재있는 노드개수이므로 새로 들어가는 값인 idx는 노드개수+1번째에 들어가야한다. 
	// 또한 배열 인덱스는 배열이 0부터 시작하는 것과는 다르게 1부터 시작한다. 그래야 부모자식의 인덱스값이 서로 연관성을 갖게되어 계산이 편리하기 때문

	// 아래 while 문 수행하면서 새로 INSERT된 data가 위치할 idx를 결정 (값을 결정하는게 아님. 값의 위치를 결정하는것)
	while (idx != 1) // root (최상위) 에 도달할때 까지
	{
		// 부모와 우선순위 비교 
		if (COMP_ASC(data, ph->heapArr[GET_PARENT_IDX(idx)]) > 0) // 부모보다 우선순위가 높다면
		{
			// 부모를 끌어내리기
			ph->heapArr[idx] = ph->heapArr[GET_PARENT_IDX(idx)];

			// idx 를 부모의 idx로 이동 
			idx = GET_PARENT_IDX(idx);

		}
		// 새로 넣은 값의 번호가 idx임 
		else // 부모보다 우선순위가 낮거나 같다.. 여기서 while 멈춰야함
		{
			break;
		}
	}

	// idx가 결정된 그곳이 새로 INSERT된 data가 들어갈 위치 

	ph->heapArr[idx] = data;
	ph->numData++;

}

// 힙에 데이터 빼기 delete. 삭제는 root에서 발생 
HData heap_delete(Heap *ph) {

	// root값 없애기 
	HData rootData = ph->heapArr[1]; // 인덱스 1번이 루트 노드, 이를 제거하고 리턴 

	// 마지막 노드가 자리잡을 위치 idx 를 결정해야 한다 .
	// idx가 결정될때까지 마지막 노드의 data는 보관해 놓는다. 

	HData lastElem = ph->heapArr[ph->numData];
	// 마지막노드의 값을 저장해놓기 

	int idx = 1; // 마지막 노드가 일단 root 자리에 오게 된다. 
	int childIdx;

	while (childIdx = getHighPriority(ph, idx))
		// 저 대입연산자 자체가 결과값이 있음. 대입한 값 자체가 결과값임. 
	{
		if (COMP_ASC(lastElem, ph->heapArr[childIdx]) >= 0) break;

		ph->heapArr[idx] = ph->heapArr[childIdx];

		idx = childIdx;
	}

	ph->heapArr[idx] = lastElem;
	//ph->heapArr[ph->numData] = NULL;
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

#define MAX 500
#define SUPERMAX 6000

void findM(int NumberofNum, int minimumOfDifference, int numArr[MAX]) {

	int DivisorIdx = 0;
	int DivisorArr[MAX] = { 0 };
	int answerArr[MAX] = { 0 };
	double rootOfLowestDiff = sqrt(minimumOfDifference);

	// 최소차의 약수 집합이 곧 범위이다. 
	for (int divisor = 1; divisor <= rootOfLowestDiff; divisor++) {
		// 값의 차의 최솟값의 제곱근보다 작은 수로 lowDiff을 나누어서 값을 저장한다. 이때 1부터 하므로 나중에 1은 빼줘야됨
		if (minimumOfDifference % divisor == 0) {
			DivisorArr[DivisorIdx] = divisor;
			DivisorIdx++;
			if (minimumOfDifference / divisor != divisor) {
				DivisorArr[DivisorIdx] = minimumOfDifference / divisor;
				DivisorIdx++;
			}
		}
	}
	
	Heap heap;
	heap_init(&heap, DivisorIdx);
	HeapSort(DivisorArr, DivisorIdx);
	// 약수들을 모두 오름차순 정렬하고

	int ansIndex = 0;

	// 약수들을 저장한 배열에 있는 값들을 1번 인덱스부터 차례로 넣는다.
	for (int sortedDivisorArrIdx = 1; sortedDivisorArrIdx<DivisorIdx; sortedDivisorArrIdx++) {

		int newDivisor = DivisorArr[sortedDivisorArrIdx];
		int numArrIdx = 0;
		int rest = 0;

		for (numArrIdx = 0; numArrIdx < NumberofNum; numArrIdx++) {

			if (numArrIdx == 0) {
				rest = numArr[numArrIdx] % newDivisor;
			}
			else if (rest != numArr[numArrIdx] % newDivisor) {
				break;
			}
		}

		if (numArrIdx == NumberofNum) {
			answerArr[ansIndex] = newDivisor;
			ansIndex++;
		}
	}

	for (int j = 0; j < ansIndex; j++) {
		printf("%d ", answerArr[j]);
	}
}

//int makeItPositiveNumber(int a) {
//
//	if (a < 0) {
//		a = -a;
//	}
//
//	return a;
//}

int main() {

	int NumberofNum;
	scanf("%d", &NumberofNum);

	int numArr[MAX] = { 0 };
	int DifferenceBetweenNumbersArr[SUPERMAX] = { 0 };

	for (int i = 0; i < NumberofNum; i++) {
		scanf("%d", &numArr[i]);
	}

	int DifferenceIdx = 0;

	for (int i = 0; i < NumberofNum; i++) {
		for (int j = i+1; j < NumberofNum; j++) {
			if (numArr[i] - numArr[j] < 0) {
				DifferenceBetweenNumbersArr[DifferenceIdx] = numArr[j] - numArr[i];
			}
			else {
				DifferenceBetweenNumbersArr[DifferenceIdx] = numArr[i] - numArr[j];
			}
			// 해답의 핵심 포인트 
			// 진짜 개 쓸데없이 이상한 함수 호출하지마라!!!!!!!!!!!!!!!!!!!!!!!!!
			// 함수호출에 시간이 다잡아먹힌다 
			DifferenceIdx++;
		}
	}

	Heap hp;
	heap_init(&hp, DifferenceIdx);
	HeapSort(DifferenceBetweenNumbersArr, DifferenceIdx);

	findM(NumberofNum, DifferenceBetweenNumbersArr[0], numArr);

	return 0;
} // 맞았습니다!!

// 해답의 핵심 포인트 
// 진짜 개 쓸데없이 이상한 함수 호출하지마라!!!!!!!!!!!!!!!!!!!!!!!!!
// 함수호출에 시간이 다잡아먹힌다 
// 또한 for문 돌리는건 많아봐야 몇십만번에서 끝나야한다 몇백만 가는순간 그냥 시간초과