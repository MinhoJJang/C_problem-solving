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
#define SUCCESS 1
#define FAIL 0

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

typedef cor HData;

typedef int fnPriorityComp(HData d1, HData d2);

typedef struct _heap
{
	int numData; // 담고있는 데이터개수 
	HData *heapArr; // 동적메모리로 구현
	fnPriorityComp *comp; // 우선순위 비교함수 
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

// idx의 자식들 중 우선순위가 높은 자식의 index값 리턴 --> delete 에 사용 
int getHighPriority(Heap *ph, int idx) {
	// 자식노드가 없다면 0리턴 
	if (GET_LEFT_IDX(idx) > ph->numData) return 0;

	// 자식노드가 1개라면 (왼쪽 노드가 유일)
	if (GET_LEFT_IDX(idx) == ph->numData) return GET_LEFT_IDX(idx);

	// 우선순위 
	if (COMP_ASC(ph->heapArr[GET_LEFT_IDX(idx)].num, ph->heapArr[GET_RIGHT_IDX(idx)].num) < 0) {
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
	ph->heapArr = (cor*)malloc(sizeof(cor)*(len + 1));
	// complete binary tree의 배열은 1번부터 시작하므로 0번은 값이 없다. 그래서 len+1만큼의 size가 필요함. 이러한 배열을 1-based 배열이라고 부름
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
	
	while (idx != 1) // root (최상위) 에 도달할때 까지
	{
		// 부모와 우선순위 비교 
		if (COMP_ASC(data.num, ph->heapArr[GET_PARENT_IDX(idx)].num) > 0) // 부모보다 우선순위가 높다면
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
		if (COMP_ASC(lastElem.num, ph->heapArr[childIdx].num) >= 0) break;

		ph->heapArr[idx] = ph->heapArr[childIdx];

		idx = childIdx;
	}

	ph->heapArr[idx] = lastElem;
	ph->numData--;

	return rootData;
}

void HeapSort(HData arr[], int n)
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

void printArr(int n) { // 테스트함수
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i].num);
	}
}

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
	//QuickSort(arr, 0, n-1);
	Heap ph;
	heap_init(&ph, n);
	HeapSort(arr, n);
	//printArr(n);
	// 이때, 맨 처음 인덱스 번호에다가 0을 넣고, 그 다음에 숫자비교해서 같으면 0, 크면 1넣고..이런식
	fn(n);
	printAnswer(n);

	return 0;
} 
// 퀵소트하면 최악의 경우가 있기 때문에 시간초과. 
// 따라서 힙소트를 하면 통과함 