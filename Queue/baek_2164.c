#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 


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

// 4. 큐에서 자료뺴기 
int queue_deq(Queue *pq, Data *pData) {

	// 일단 먼저 자료가 있는지부터 살펴본다. 
	if (queue_is_empty(pq) == YES) {
		return FAIL;
	}

	// 놓친점 3) pData가 NULL이 되면 안되니까..
	if (pData != NULL)
		// (1) front data를 *pData에 담자.
		*pData = pq->pFront->data;

	// (2) 현재 front노드를 담을 새로운 노드를 지정해주자. 
	Node *pCurNode = (Node*)malloc(sizeof(Node));

	// (3) front Node 를 pCurNode 로 옮기고
	pCurNode = pq->pFront;

	// (4) front위치를 변경해주고
	pq->pFront = pq->pFront->pNext;

	// (5) pCurNode를 free해주고 NumberOfData-- 해준다.
	free(pCurNode);
	pq->numdata--;

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


/*

1 = 1
1 2 = 2
1 2 3 = 2 3 = 3 2 = 2
1 2 3 4 = 2 3 4 = 3 4 2 = 4 2 = 2 4 = 4
1 2 3 4 5 = 2 3 4 5 = 3 4 5 2 = 4 5 2 = 5 2 4 = 2 4 = 4 2 = 2

제일 위에 front에서 pop 1번, 2번하고 2번째에서 2번쨰 데이터를 다시 back로 push해주는 큐 

*/

int main() {

	Queue q;
	Data data;

	queue_init(&q);

	int N = 0;
	scanf("%d", &N);

	for (int i = 1; i <= N; i++) {
		queue_enq(&q, i);
	}

	// q : N, N-1, ... , 3, 2, 1
	//    back					front

	// 예외 1: 입력개수가 1개일때는 카드를 버려서는 안된다. 
	if (N == 1) {
		printf("%d", 1);
		return 0;
	}

	while (queue_size(&q) != 1) {

		// 맨 위 카드를 버린다.
		queue_deq(&q, &data); 

		// 제일 위의 카드 데이터값을 가져온다. 
		queue_peek(&q, &data); 
		int peekData = data;

		queue_deq(&q, &data);
		queue_enq(&q, peekData);
	}

	queue_peek(&q, &data);
	printf("%d", data);

	return 0;
} // 맞았습니다!!