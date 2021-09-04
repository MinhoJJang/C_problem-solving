#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
정수를 저장하는 큐를 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.

명령은 총 여섯 가지이다.

push X: 정수 X를 큐에 넣는 연산이다.
pop: 큐에서 가장 앞에 있는 정수를 빼고, 그 수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
size: 큐에 들어있는 정수의 개수를 출력한다.
empty: 큐가 비어있으면 1, 아니면 0을 출력한다.
front: 큐의 가장 앞에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
back: 큐의 가장 뒤에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.

첫째 줄에 주어지는 명령의 수 N (1 ≤ N ≤ 2,000,000)이 주어진다. 둘째 줄부터 N개의 줄에는 명령이 하나씩 주어진다. 주어지는 정수는 1보다 크거나 같고, 100,000보다 작거나 같다. 문제에 나와있지 않은 명령이 주어지는 경우는 없다.
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


void queue_init(Queue *pq) {
	pq->pBack = NULL;
	pq->pFront = NULL;
	pq->numdata = 0;
}

// empty: 큐가 비어있으면 1, 아니면 0을 출력한다.
int queue_is_empty(Queue *pq) {
	
	if (pq->pFront == NULL) return YES;
	
	return NO;
}

// push X: 정수 X를 큐에 넣는 연산이다.
int queue_push(Queue *pq, Data data) {

	Node *pNewNode = (Node*)malloc(sizeof(Node));	
	pNewNode->data = data;
	pNewNode->pNext = NULL; 

	if (queue_is_empty(pq)) {
		pq->pBack = pNewNode;
		pq->pFront = pNewNode;
	}
	else {
		pq->pBack->pNext = pNewNode; 
		pq->pBack = pNewNode;
	}

	pq->numdata++;

	return SUCCESS;
}

// pop: 큐에서 가장 앞에 있는 정수를 빼고, 그 수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
int queue_pop(Queue *pq, Data *pData) {

	if (queue_is_empty(pq) == YES) {
		printf("%d\n", -1);
		return 0;
	}

	if (pData != NULL)
		*pData = pq->pFront->data;

	Node *pCurNode = (Node*)malloc(sizeof(Node));
	pCurNode = pq->pFront;
	pq->pFront = pq->pFront->pNext;
	free(pCurNode);
	pq->numdata--;

	printf("%d\n", *pData);

	return SUCCESS;
} 

// size: 큐에 들어있는 정수의 개수를 출력한다.
int queue_size(Queue *pq) {
	printf("%d\n", pq->numdata);
	return 0;
}

// front: 큐의 가장 앞에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
int queue_front(Queue *pq, Data *pData) {

	if (queue_is_empty(pq)) {
		printf("%d\n", -1);
		return 0;
	}

	if(pData != NULL)
		*pData = pq->pFront->data;

	printf("%d\n", *pData);

	return SUCCESS;
}

// back: 큐의 가장 뒤에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
int queue_back(Queue *pq, Data *pData) {

	if (queue_is_empty(pq)) {
		printf("%d\n", -1);
		return 0;
	}

	if (pData != NULL)
		*pData = pq->pBack->data;

	printf("%d\n", *pData);

	return SUCCESS;
}


int main() {

	Queue queue;
	Data data;

	queue_init(&queue);

	int N = 0;

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {

		char order[6] = { 0 };
		scanf("%s", order);

		if (strcmp(order, "push") == 0) {
			int num = 0;
			scanf("%d", &num);
			queue_push(&queue, num);
		}
		else if (strcmp(order, "pop") == 0) {
			queue_pop(&queue, &data);
		}
		else if (strcmp(order, "size") == 0) {
			queue_size(&queue);
		}
		else if (strcmp(order, "empty") == 0) {
			
			if (queue_is_empty(&queue)) {
				printf("%d\n", 1);
			}
			else {
				printf("%d\n", 0);
			}
		}
		else if (strcmp(order, "front") == 0) {
			queue_front(&queue, &data);
		}
		else if (strcmp(order, "back") == 0) {
			queue_back(&queue, &data);
		}

	}

	return 0;
} // 맞았습니다 !! 