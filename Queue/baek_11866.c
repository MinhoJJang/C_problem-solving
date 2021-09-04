#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
요세푸스 문제는 다음과 같다.

1번부터 N번까지 N명의 사람이 원을 이루면서 앉아있고, 양의 정수 K(≤ N)가 주어진다. 이제 순서대로 K번째 사람을 제거한다. 한 사람이 제거되면 남은 사람들로 이루어진 원을 따라 이 과정을 계속해 나간다. 이 과정은 N명의 사람이 모두 제거될 때까지 계속된다. 원에서 사람들이 제거되는 순서를 (N, K)-요세푸스 순열이라고 한다. 예를 들어 (7, 3)-요세푸스 순열은 <3, 6, 2, 7, 5, 1, 4>이다.

N과 K가 주어지면 (N, K)-요세푸스 순열을 구하는 프로그램을 작성하시오.

첫째 줄에 N과 K가 빈 칸을 사이에 두고 순서대로 주어진다. (1 ≤ K ≤ N ≤ 1,000)
*/


#define SUCCESS	1
#define FAIL	0

#define YES 1
#define NO 0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node *pNext;

} Node;

typedef struct _queue {
	Node *pFront;
	Node *pBack;
	int numdata;
} Queue;

// 1. 큐 초기화 
void queue_init(Queue *pq) {
	pq->pBack = NULL;
	pq->pFront = NULL;
	pq->numdata = 0;
}

// 2. 큐에 자료가 비어있는가?
int queue_is_empty(Queue *pq) {
	if (pq->pFront == NULL) {
		return YES;
	}
	return NO;
}

// 3. 큐에 자료 넣기 
int queue_enq(Queue *pq, Data data) {

	// (1) 일단 데이터를 집어넣을 노드를 만들자. 
	Node *pNewNode = (Node*)malloc(sizeof(Node)); // 포인터를 malloc로 메모리 할당하는것..

	// (2) 새 노드에 데이터를 넣어준다. 
	pNewNode->data = data;
	pNewNode->pNext = NULL; // 놓친점 1) pNewNode를 초기화시켜야하니까 NULL로 초기화시켜준다. 

	// (3) 만약 큐에 자료가 없을 경우, pBack, pFront가 동시에 pNewNode를 가리키게 만든다. 
	if (queue_is_empty(pq) == YES) {
		pq->pBack = pNewNode;
		pq->pFront = pNewNode;
	}

	// (4) 큐에 1개 이상 데이터가 있는 경우, 새로 만든 노드는 pBack에 위치하고, pFront는 그대로 유지한다. 
	else {
		pq->pBack->pNext = pNewNode; // 놓친점 2) front가 그대로 유지되려면 사실상 움직여서는 안됨. 원래 back에 있던 노드의 다음 노드가 새로운 back에 위치하는 것이므로 stack과 비슷하게 back를 움직여주자. 
		pq->pBack = pNewNode;
	}
	pq->numdata++;

	return SUCCESS;
}

// 5. 큐에서 자료 미리보기
int queue_peek(Queue *pq, Data *pData) {

	if (queue_is_empty(pq) == YES) {
		return FAIL;
	}

	if (pData != NULL)
		*pData = pq->pFront->data;

	return SUCCESS;
}

int queue_size(Queue *pq) {
	return pq->numdata;
}

// 큐를 원형으로 만드는 함수
int queue_MakeItCircle(Queue *pq) {

	if (queue_is_empty(pq) == YES) {
		return FAIL;
	}

	pq->pBack->pNext = pq->pFront;

	pq->pBack = NULL;

	return SUCCESS;
}

int queue_jump(Queue *pq, int jumptimes, Data *pData) {
	
	Node *CurrentNode = (Node*)malloc(sizeof(Node));

	Node *PopNode = (Node*)malloc(sizeof(Node));

	CurrentNode = pq->pFront; // 현재 노드를 front에서 출발한다. 

	// jumptimes가 1이 아닐 경우 
	// jumtimes가 1일 경우는 그냥 입력한 수열 그대로 출력하면 되니까 예외로 한다. 
	while (jumptimes-2 != 0) {
		CurrentNode = CurrentNode->pNext;
		jumptimes--;
	}

	// pop할 노드의 바로 이전 노드가 currentnode이다.
	PopNode = CurrentNode->pNext;
	pq->pFront = PopNode->pNext;

	if (pData != NULL)
		*pData = PopNode->data;

	CurrentNode->pNext = pq->pFront;

	free(PopNode);
	pq->numdata--;

	return SUCCESS;
}

void queue_ans(int arr[], int NumberofPeople) {

	printf("<");

	for (int i = 0; i < NumberofPeople; i++) {
		if (i != NumberofPeople - 1) {
			printf("%d, ", arr[i]);
		}
		else {
			printf("%d", arr[i]);
		}
	}

	printf(">");
}


int main() {

	int NumberofPeople = 0;
	int DeleteNumber = 0;
	int Answer[1005] = { 0 };

	Queue q;
	Data data;

	scanf("%d %d", &NumberofPeople, &DeleteNumber);

	// NumberofPeople이 1일 경우, 1 출력
	if (NumberofPeople == 1) {
		Answer[0] = 1;
		queue_ans(Answer, NumberofPeople);
		return 0;
	}

	// DeleteNumber이 1일 경우, 1부터 차례대로 출력
	if (DeleteNumber == 1) {
		
		int num = 1;

		for (int person = 0; person < NumberofPeople; person++) {
			Answer[person] = num;
			num++;
		}

		queue_ans(Answer, NumberofPeople);
		return 0;
	}

	// DeleteNumber이 1이 아닐 경우
	queue_init(&q);

	for (int person = 1; person <= NumberofPeople; person++) {
		queue_enq(&q, person);
	}

	queue_MakeItCircle(&q);

	for (int i = 0; i < NumberofPeople; i++) {
		queue_jump(&q, DeleteNumber, &data);
		Answer[i] = data;
	}

	queue_ans(Answer, NumberofPeople);

	return 0;
} // 맞았습니다! 