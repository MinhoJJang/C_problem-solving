#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*

*/


#define SUCCESS	1
#define FAIL	0

#define YES 1
#define NO 0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node *pNext_headFront;
	struct _node *pNext_headBack;
	Data IndexOfData;
} Node;

typedef struct _Queue {
	Node *pFront;
	Node *pBack;
	int NumberOfData;
} Queue;

// =============

void queue_init(Queue *q) {
	q->pBack = NULL;
	q->pFront = NULL;
	q->NumberOfData = 0;
}

// empty: 큐가 비어있으면 1, 아니면 0을 출력한다.
int queue_is_empty(Queue *q) {

	if (q->NumberOfData == 0) {

		return YES;
	}

	return NO;
}

int queue_push(Queue *q, Data data) {

	Node *pNewNode = (Node*)malloc(sizeof(Node));
	pNewNode->data = data;
	pNewNode->pNext_headBack = NULL;
	pNewNode->pNext_headFront = NULL;

	if (queue_is_empty(q)) {
		q->pBack = pNewNode;
		q->pFront = pNewNode;
		 
		q->pBack->pNext_headFront = q->pFront;
		q->pFront->pNext_headBack = q->pBack;
		
	}
	else {
		pNewNode->pNext_headFront = q->pBack;
		q->pBack->pNext_headBack = pNewNode;
		q->pBack = pNewNode;
	}

	q->NumberOfData++;
	pNewNode->IndexOfData = q->NumberOfData;

	return SUCCESS;
}

// front위치한 수 빼기
int queue_pop(Queue *q, Data *pData) {

	if (q->NumberOfData == 0) {
		
		return 0;
	}

	if (pData != NULL)
		*pData = q->pFront->data;

	Node *pCurNode = (Node*)malloc(sizeof(Node));

	pCurNode = q->pFront;
	q->pFront = q->pFront->pNext_headBack;
	
	// 1차 수정사항 
	// 당연히 pop을 하면 headfront, headback이 바뀌니까 고쳐주어야함
	q->pBack->pNext_headBack = q->pFront;
	q->pFront->pNext_headFront = q->pBack;

	free(pCurNode);
	
	q->NumberOfData--;

	return SUCCESS;
}

int queue_MakeitCircle(Queue *q) {
	q->pFront->pNext_headFront = q->pBack;
	q->pBack->pNext_headBack = q->pFront;
}

int queue_MoveLeftTimes(Queue *q, Data Index) {

	int MoveLeftCount = 0;

	while (q->pFront->IndexOfData != Index) {
		
		q->pFront = q->pFront->pNext_headBack;
		q->pBack = q->pBack->pNext_headBack;
		MoveLeftCount++;
	}

	return MoveLeftCount;
}

int queue_MoveRightTimes(Queue *q, Data Index) {

	int MoveRightCount = 0;

	while (q->pFront->IndexOfData != Index) {

		q->pFront = q->pFront->pNext_headFront;
		q->pBack = q->pBack->pNext_headFront;
		MoveRightCount++;
	}

	return MoveRightCount;
}

int main() {

	int Queue_size;
	int Max_PopTimes;
	int NumberLocation;
	int TotalMoveCount = 0;

	scanf("%d %d", &Queue_size, &Max_PopTimes);

	Queue GoLeftQueue;
	Queue GoRightQueue;
	Data data;

	queue_init(&GoLeftQueue);
	queue_init(&GoRightQueue);

	// 편의상 1부터 큐 사이즈까지 큐에 데이터를 순서대로 넣음
	for (int data = 1; data <= Queue_size; data++) {
		queue_push(&GoLeftQueue, data);
		queue_push(&GoRightQueue, data);
	}

	queue_MakeitCircle(&GoLeftQueue);
	queue_MakeitCircle(&GoRightQueue);

	for (int Poptime = 0; Poptime < Max_PopTimes; Poptime++) {
		scanf("%d", &NumberLocation);

		int NumberofGoLeft = queue_MoveLeftTimes(&GoLeftQueue, NumberLocation);
		int NumberofGoRight = queue_MoveRightTimes(&GoRightQueue, NumberLocation);

		if (NumberofGoLeft > NumberofGoRight) {
			TotalMoveCount = TotalMoveCount + NumberofGoRight;
			queue_pop(&GoRightQueue, &data);
			GoLeftQueue = GoRightQueue;
		}
		else {
			TotalMoveCount = TotalMoveCount + NumberofGoLeft;
			queue_pop(&GoLeftQueue, &data);
			GoRightQueue = GoLeftQueue;
		}
	}

	printf("%d", TotalMoveCount);



	return 0;
}