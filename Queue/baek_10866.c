#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
정수를 저장하는 덱(Deque)를 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.

명령은 총 여덟 가지이다.

push_front X: 정수 X를 덱의 앞에 넣는다.
push_back X: 정수 X를 덱의 뒤에 넣는다.
pop_front: 덱의 가장 앞에 있는 수를 빼고, 그 수를 출력한다. 만약, 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
pop_back: 덱의 가장 뒤에 있는 수를 빼고, 그 수를 출력한다. 만약, 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
size: 덱에 들어있는 정수의 개수를 출력한다.
empty: 덱이 비어있으면 1을, 아니면 0을 출력한다.
front: 덱의 가장 앞에 있는 정수를 출력한다. 만약 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
back: 덱의 가장 뒤에 있는 정수를 출력한다. 만약 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
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
} Node;

typedef struct _deque {
	Node *pFront;
	Node *pBack;
	int numdata;
} Deque;

void queue_init(Deque *dq) {
	dq->pBack = NULL;
	dq->pFront = NULL;
	dq->numdata = 0;
}

// empty: 큐가 비어있으면 1, 아니면 0을 출력한다.
int queue_is_empty(Deque *dq) {

	if (dq->numdata == 0) {
		
		return YES;
	}
	
	return NO;
}

// push X: 정수 X를 앞에 넣는다 (Front에 추가)
int queue_push_front(Deque *dq, Data data) {

	Node *pNewNode = (Node*)malloc(sizeof(Node));
	pNewNode->data = data;
	pNewNode->pNext_headFront = NULL;
	pNewNode->pNext_headBack = NULL;

	if (queue_is_empty(dq)) {
		dq->pBack = pNewNode;
		dq->pFront = pNewNode;
		dq->pBack->pNext_headFront = dq->pFront;
		dq->pFront->pNext_headBack = dq->pBack;
	}
	else {
		dq->pFront->pNext_headFront = pNewNode;
		pNewNode->pNext_headBack = dq->pFront;
		dq->pFront = pNewNode;
	}

	dq->numdata++;

	return SUCCESS;
}

// 정수 X를 덱의 뒤에 넣는다 (Back에 추가)
int queue_push_back(Deque *dq, Data data) {

	Node *pNewNode = (Node*)malloc(sizeof(Node));
	pNewNode->data = data;
	pNewNode->pNext_headBack = NULL;
	pNewNode->pNext_headFront = NULL;

	if (queue_is_empty(dq)) {
		dq->pBack = pNewNode;
		dq->pFront = pNewNode;
		// 여기부터 
		dq->pBack->pNext_headFront = dq->pFront;
		dq->pFront->pNext_headBack = dq->pBack;
		// 1차수정 
	}
	else {
		
		pNewNode->pNext_headFront = dq->pBack;
		dq->pBack->pNext_headBack = pNewNode;
		dq->pBack = pNewNode;
	}

	dq->numdata++;

	return SUCCESS;
}

// pop_front 덱에서 가장 앞에 있는 정수를 빼고, 그 수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
int queue_pop_front(Deque *dq, Data *pData) {

	if (dq->numdata == 0) {
		printf("%d\n", -1);
		return 0;
	}

	if (pData != NULL)
		*pData = dq->pFront->data;

	Node *pCurNode = (Node*)malloc(sizeof(Node));

	pCurNode = dq->pFront;
	dq->pFront = dq->pFront->pNext_headBack;
	free(pCurNode);
	// pop에서 front의 다음노드위치를 정해버리면 나중에 push할때 오류가 생길수밖에....

	dq->numdata--;

	printf("%d\n", *pData);

	return SUCCESS;
}

// pop_back 덱에서 가장 앞에 있는 정수를 빼고, 그 수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
int queue_pop_back(Deque *dq, Data *pData) {

	if (dq->numdata == 0) {
		printf("%d\n", -1);
		return 0;
	}

	if (pData != NULL)
		*pData = dq->pBack->data;

	Node *pCurNode = (Node*)malloc(sizeof(Node));

	pCurNode = dq->pBack;
	dq->pBack = dq->pBack->pNext_headFront;
	free(pCurNode);

	dq->numdata--;

	printf("%d\n", *pData);

	return SUCCESS;
}

// size: 큐에 들어있는 정수의 개수를 출력한다.
int queue_size(Deque *dq) {
	printf("%d\n", dq->numdata);
	return 0;
}

// front: 큐의 가장 앞에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
int queue_front(Deque *dq, Data *pData) {

	if (queue_is_empty(dq) == YES) {
		printf("%d\n", -1);
		return 0;
	}

	if (pData != NULL)
		*pData = dq->pFront->data;

	printf("%d\n", *pData);

	return SUCCESS;
}

// back: 큐의 가장 뒤에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
int queue_back(Deque *dq, Data *pData) {

	if (queue_is_empty(dq) == YES) {
		printf("%d\n", -1);
		return 0;
	}

	if (pData != NULL)
		*pData = dq->pBack->data;

	printf("%d\n", *pData);

	return SUCCESS;
}


int main() {

	int NumberOfOrders = 0;

	Deque dq;
	Data data;

	queue_init(&dq);

	scanf("%d", &NumberOfOrders);
	
	for (int OrderCount = 0; OrderCount < NumberOfOrders; OrderCount++) {
		char Order[20] = { 0 };
		scanf("%s", Order);

		if (strcmp(Order, "push_back") == 0) {
			int PushNumber = 0;
			scanf("%d", &PushNumber);
			queue_push_back(&dq, PushNumber);
			continue;
		}
		else if (strcmp(Order, "push_front") == 0) {
			int PushNumber = 0;
			scanf("%d", &PushNumber);
			queue_push_front(&dq, PushNumber);
			continue;
		}
		else if (strcmp(Order, "pop_back") == 0) {
			queue_pop_back(&dq, &data);
			continue;
		}
		else if (strcmp(Order, "pop_front") == 0) {
			queue_pop_front(&dq, &data);
			continue;
		}
		else if (strcmp(Order, "size") == 0) {
			queue_size(&dq);
			continue;
		}
		else if (strcmp(Order, "empty") == 0) {
			printf("%d\n", queue_is_empty(&dq));
			continue;
		}
		else if (strcmp(Order, "front") == 0) {
			queue_front(&dq, &data);
			continue;
		}
		else if (strcmp(Order, "back") == 0) {
			queue_back(&dq, &data);		
			continue;
		}
	}
	return 0;
} // 맞았습니다. 비효율적 구현부분은 나중에 살짝 고치면 좋을듯 