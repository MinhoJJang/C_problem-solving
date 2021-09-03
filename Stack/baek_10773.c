#include <stdio.h>
#include <stdlib.h> // malloc, rand, atoi ..동적메모리, 난수, 문자열 변환
#include <string.h> //strcpy.. 문자열함수. memcpy.. 메모리블럭 함수
#pragma warning(disable:4996) // scnaf() 등 전통 c함수중 버퍼문제. 
#pragma warning(disable:4477) // unsigned <--> signed 관련 warning 무시 

#define SUCCESS 1
#define FAIL 0
/*
나코더 기장 재민이는 동아리 회식을 준비하기 위해서 장부를 관리하는 중이다.

재현이는 재민이를 도와서 돈을 관리하는 중인데, 애석하게도 항상 정신없는 재현이는 돈을 실수로 잘못 부르는 사고를 치기 일쑤였다.

재현이는 잘못된 수를 부를 때마다 0을 외쳐서, 가장 최근에 재민이가 쓴 수를 지우게 시킨다.

재민이는 이렇게 모든 수를 받아 적은 후 그 수의 합을 알고 싶어 한다. 재민이를 도와주자!

첫 번째 줄에 정수 K가 주어진다. (1 ≤ K ≤ 100,000)

이후 K개의 줄에 정수가 1개씩 주어진다. 정수는 0에서 1,000,000 사이의 값을 가지며, 정수가 "0" 일 경우에는 가장 최근에 쓴 수를 지우고, 아닐 경우 해당 수를 쓴다.

정수가 "0"일 경우에 지울 수 있는 수가 있음을 보장할 수 있다.

재민이가 최종적으로 적어 낸 수의 합을 출력한다. 최종적으로 적어낸 수의 합은 231-1보다 작거나 같은 정수이다.
*/

// 어떻게할까? 일단 숫자를 입력할때마다 자동으로 push시키고, (scanf써서) 0을 입력받을 경우 push시키지 않고 pop시키면 된다. 

// 일단 스택 초기화 함수, push, pop 3개면 충분할듯 


// =========HEADER.H==========

typedef int Data;

typedef struct _node {
	Data data;
	struct _node *pNext;
} Node;

typedef struct _stack {
	Node *pTop;
	//int numdata;
} Stack;

// =========HEADER.H==========

// ==========STACK.C==========
void stack_init(Stack *pStack) {
	pStack->pTop = NULL;
	//pStack->numdata = 0;
}

int stack_is_empty(Stack *pStack) {
	if (pStack->pTop == NULL) {
		return SUCCESS;
	}
	else {
		return FAIL;
	}
}

int stack_push(Stack *pStack, Data data) {

	Node *pNewNode = (Node*)malloc(sizeof(Node));
	memset(pNewNode, 0, sizeof(Node));

	pNewNode->data = data;
	pNewNode->pNext = pStack->pTop;
	pStack->pTop = pNewNode;
	//pStack->numdata++;

	return SUCCESS;
}

int stack_pop(Stack *pStack, Data *pData) {

	if (stack_is_empty(pStack) == SUCCESS) {
		return FAIL;
	}

	{
		Node *pCurrent = pStack->pTop;

		*pData = pStack->pTop->data;
		pStack->pTop = pStack->pTop->pNext;

		free(pCurrent);

		//pStack->numdata--;

		return SUCCESS;
	}
}
// ==========STACK.C==========


// ========STACKMAIN.C=========
int main() {

	int K; // 정수 K
	int ans[100001] = { 0 };
	int num= 0;
	int answer = 0;
	int j = 0;
	
	Stack stack;
	Data data;

	stack_init(&stack);

	scanf("%d", &K);

	for (int i = 0; i < K; i++) {

		scanf("%d", &num); // 정수 받기
		if (num == 0) {
			stack_pop(&stack, &data);
		}
		else {
			stack_push(&stack, num);
		}
	}
	
	while (!stack_is_empty(&stack)) {
		stack_pop(&stack, &data);
		ans[j] = data;
		j++;
	}

	for (int k = 0; k < j; k++) {
		answer += ans[k];
	}
	
	printf("%d", answer);

	return 0;
} // 맞았습니다 ! 
// =========STACKMAIN.C=========