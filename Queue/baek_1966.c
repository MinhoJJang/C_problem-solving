#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
1966

현재 Deque의 가장 앞에 있는 문서의 ‘중요도’를 확인한다.
나머지 문서들 중 현재 문서보다 중요도가 높은 문서가 하나라도 있다면, 이 문서를 인쇄하지 않고 Deque의 가장 뒤에 재배치 한다. 그렇지 않다면 바로 인쇄를 한다.
예를 들어 Deque에 4개의 문서(A B C D)가 있고, 중요도가 2 1 4 3 라면 C를 인쇄하고, 다음으로 D를 인쇄하고 A, B를 인쇄하게 된다.

여러분이 할 일은, 현재 Deque에 있는 문서의 수와 중요도가 주어졌을 때, 어떤 한 문서가 몇 번째로 인쇄되는지 알아내는 것이다. 예를 들어 위의 예에서 C문서는 1번째로, A문서는 3번째로 인쇄되게 된다.

첫 줄에 테스트케이스의 수가 주어진다. 각 테스트케이스는 두 줄로 이루어져 있다.

테스트케이스의 첫 번째 줄에는 문서의 개수 N(1 ≤ N ≤ 100)과, 몇 번째로 인쇄되었는지 궁금한 문서가 현재 Deque에서 몇 번째에 놓여 있는지를 나타내는 정수 M(0 ≤ M < N)이 주어진다. 이때 맨 왼쪽은 0번째라고 하자. 두 번째 줄에는 N개 문서의 중요도가 차례대로 주어진다. 중요도는 1 이상 9 이하의 정수이고, 중요도가 같은 문서가 여러 개 있을 수도 있다.

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
	Data IndexOfData;
} Node;

typedef struct _queue {
	Node *pFront;
	Node *pBack;
	Data NumberOfData;
	Data BigData;
} Queue;


void queue_init(Queue *pq) {
	pq->pBack = NULL;
	pq->pFront = NULL;
	pq->NumberOfData = 0;
	pq->BigData = 1;
}

int queue_is_empty(Queue *pq) {

	if (pq->pFront != NULL) { return NO; }

	return YES;
}

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

	pq->NumberOfData++;
	pNewNode->IndexOfData = (pq->NumberOfData -1);

	return SUCCESS;
}

int queue_MakeQueueCircle(Queue *pq) {

	if (queue_is_empty(pq) == YES) {
		return FAIL;
	}

	pq->pBack->pNext = pq->pFront;

	return SUCCESS;
}

int queue_SearchDataIndex(Queue *pq, Data IndexWantToKnow, Data NumberOfDocuments) {

	Node *CurrentNode = (Node*)malloc(sizeof(Node));
	Node *PointingBigNode = (Node*)malloc(sizeof(Node));
	Node *SearchNode = (Node*)malloc(sizeof(Node));
	Node *SearchingStartNode = (Node*)malloc(sizeof(Node));
	
	CurrentNode = pq->pFront;
	PointingBigNode = pq->pBack;

	pq->BigData = pq->pFront->data;
	
	while (CurrentNode->pNext->IndexOfData != pq->pFront->IndexOfData && pq->BigData != 9) {

		if (pq->BigData < CurrentNode->pNext->data) {
			pq->BigData = CurrentNode->pNext->data;
			PointingBigNode = CurrentNode;		
		}
		CurrentNode = CurrentNode->pNext;
	}

	int MostBigDataInQueue = PointingBigNode->pNext->data;
	int CheckBigDataCount = 0;

	SearchNode = PointingBigNode->pNext;

	for(int iteration=0; MostBigDataInQueue>0; iteration++) // 의미없는 for문 대신 그냥 while()문 쓰는게 나을듯하다 
	{
		if (SearchNode->data == MostBigDataInQueue) {

			CheckBigDataCount++;
			SearchingStartNode = SearchNode;

			if (SearchNode->IndexOfData == IndexWantToKnow) {
				
				return CheckBigDataCount;
			}
		}
	
		if (SearchNode->IndexOfData == PointingBigNode->IndexOfData) {
			MostBigDataInQueue--;
			SearchNode = SearchingStartNode;
			PointingBigNode = SearchingStartNode;
		}

		SearchNode = SearchNode->pNext;
	}

	free(CurrentNode);
	free(PointingBigNode);
	free(SearchNode);
	free(SearchingStartNode);
}

int main() {

	Queue q;

	int Testcase = 0;
	int NumberOfDocuments = 0;
	int IndexWeWant = 0;
	int ImportanceNumbers = 0;
	int Answer[1000] = { 0 };

	scanf("%d", &Testcase);

	for (int t = 0; t < Testcase; t++) {

		scanf("%d %d", &NumberOfDocuments, &IndexWeWant);

		queue_init(&q);
		
		for (int i = 0; i < NumberOfDocuments; i++) {
			scanf("%d", &ImportanceNumbers);
			queue_push(&q, ImportanceNumbers);
		}

		if (NumberOfDocuments == 1) {
			Answer[t] = 1;
		}

		else {
			queue_MakeQueueCircle(&q);
			Answer[t] = queue_SearchDataIndex(&q, IndexWeWant, NumberOfDocuments);
		}
	}

	for (int t = 0; t < Testcase; t++) {
		printf("%d\n", Answer[t]);
	}

	return 0;
} // 맞았습니다!! 와 진짜... ㅠㅠ 진짜 힘들었다 ㅠㅠㅠㅠ
