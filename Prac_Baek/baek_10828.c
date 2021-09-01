#include <stdio.h>
#include <stdlib.h> // malloc, rand, atoi ..동적메모리, 난수, 문자열 변환
#include <string.h> //strcpy.. 문자열함수. memcpy.. 메모리블럭 함수
#pragma warning(disable:4996) // scnaf() 등 전통 c함수중 버퍼문제. 
#pragma warning(disable:4477) // unsigned <--> signed 관련 warning 무시 

/*
정수를 저장하는 스택을 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.

명령은 총 다섯 가지이다.

push X: 정수 X를 스택에 넣는 연산이다.
pop: 스택에서 가장 위에 있는 정수를 빼고, 그 수를 출력한다. 만약 스택에 들어있는 정수가 없는 경우에는 -1을 출력한다.
size: 스택에 들어있는 정수의 개수를 출력한다.
empty: 스택이 비어있으면 1, 아니면 0을 출력한다.
top: 스택의 가장 위에 있는 정수를 출력한다. 만약 스택에 들어있는 정수가 없는 경우에는 -1을 출력한다.

첫째 줄에 주어지는 명령의 수 N (1 ≤ N ≤ 10,000)이 주어진다. 둘째 줄부터 N개의 줄에는 명령이 하나씩 주어진다. 주어지는 정수는 1보다 크거나 같고, 100,000보다 작거나 같다. 문제에 나와있지 않은 명령이 주어지는 경우는 없다.

출력해야하는 명령이 주어질 때마다, 한 줄에 하나씩 출력한다.
*/

// =========HEADER.H==========

#define SUCCESS 1
#define FAIL 0

typedef int Data;

typedef struct _node {
	Data data;
	struct _node *pNext;
} Node;

typedef struct _stack {
	Node *pTop;
	int numdata;
} Stack;

// =========HEADER.H==========


// ==========STACK.C===========
void stack_init(Stack *pStack) {
	pStack->pTop = NULL;
	pStack->numdata = 0;
}

int stack_push(Stack *pStack, Data data) {

	Node *pNewNode = (Node*)malloc(sizeof(Node));
	memset(pNewNode, 0, sizeof(Node));
	
	pNewNode->data = data;
	pNewNode->pNext = pStack->pTop;
	pStack->pTop = pNewNode;
	pStack->numdata++;

	return SUCCESS;
}

int stack_is_empty(Stack *pStack) {
	if (pStack->pTop == NULL) {
		return SUCCESS;
	}
	else {
		return FAIL;
	}
}
// 있으면 FAIL

int stack_pop(Stack *pStack, Data *pData) {

	if (stack_is_empty(pStack)==SUCCESS) {
		*pData = -1;
		return FAIL;
	}

	else {
		Node *pCurrent = pStack->pTop;

		*pData = pStack->pTop->data;
		pStack->pTop = pStack->pTop->pNext;

		free(pCurrent);

		pStack->numdata--;

		return SUCCESS;
	}
}

int stack_size(Stack *pStack, Data *pData) {
	
	*pData = pStack->numdata;
	return SUCCESS;
}


int stack_top(Stack *pStack, Data *pData) {

	if (stack_is_empty(pStack)==SUCCESS) {
		*pData = -1;
		return FAIL;
	}

	else {
		*pData = pStack->pTop->data;
		return SUCCESS;
	}
}
// ==========STACK.C===========


// ==========STACKMAIN.C===========
int main() {

	int order,N = 0; // 명령의 수 

	Stack stack;
	Data data;
	int arr[10010] = { 0 };
	int NUMDATA = 0; // push 개수 

	stack_init(&stack);

	scanf("%d", &order);

	for (N = 0; N < order; N++) {

		char whatorder[10] = { 0 };
		int num = 0;
		
		scanf("%s", whatorder);

		if (strcmp(whatorder,"push")==0) {
			scanf("%d\n", &num);
			stack_push(&stack, num);
			NUMDATA++;
		}
		else if (strcmp(whatorder, "pop") == 0) {
			stack_pop(&stack, &data);
			arr[N- NUMDATA] = data;
		}
		else if (strcmp(whatorder, "size") == 0) {
			stack_size(&stack, &data);
			arr[N- NUMDATA] = data;
		}
		else if (strcmp(whatorder, "empty") == 0) {
			if (stack_is_empty(&stack) == 0) {
				arr[N- NUMDATA] = 0;
			}
			else {
				arr[N- NUMDATA] = 1;
			}
		}
		else if(strcmp(whatorder, "top") == 0) {
			stack_top(&stack, &data);
			arr[N -NUMDATA] = data;
		}
	}

	for (N = 0; N < order-NUMDATA; N++) {

		printf("%d\n", arr[N]);
	}

	return 0;
} // 맞았습니다!!!
// ==========STACKMAIN.C===========