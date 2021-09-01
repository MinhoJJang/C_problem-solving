#include <stdio.h>
#include <stdlib.h> // malloc, rand, atoi ..동적메모리, 난수, 문자열 변환
#include <string.h> //strcpy.. 문자열함수. memcpy.. 메모리블럭 함수
#include <time.h> // clock .. 시간, 날짜 함수
#pragma warning(disable:4996) // scnaf() 등 전통 c함수중 버퍼문제. 
#pragma warning(disable:4477) // unsigned <--> signed 관련 warning 무시 

/*
1부터 n까지의 수를 스택에 넣었다가 뽑아 늘어놓음으로써, 하나의 수열을 만들 수 있다. 이때, 스택에 push하는 순서는 반드시 오름차순을 지키도록 한다고 하자. 임의의 수열이 주어졌을 때 스택을 이용해 그 수열을 만들 수 있는지 없는지, 있다면 어떤 순서로 push와 pop 연산을 수행해야 하는지를 알아낼 수 있다. 이를 계산하는 프로그램을 작성하라.

첫 줄에 n (1 ≤ n ≤ 100,000)이 주어진다. 둘째 줄부터 n개의 줄에는 수열을 이루는 1이상 n이하의 정수가 하나씩 순서대로 주어진다. 물론 같은 정수가 두 번 나오는 일은 없다.

입력된 수열을 만들기 위해 필요한 연산을 한 줄에 한 개씩 출력한다. push연산은 +로, pop 연산은 -로 표현하도록 한다. 불가능한 경우 NO를 출력한다.

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


int stack_pop(Stack *pStack, Data *pData) {

	if (stack_is_empty(pStack)) {
		return FAIL;
	}

	Node *pCurrent = pStack->pTop;
	if (pData != NULL)
		*pData = pStack->pTop->data;

	pStack->pTop = pStack->pTop->pNext;

	free(pCurrent);

	pStack->numdata--;

	return SUCCESS;

}

int stack_size(Stack *pStack, Data *pData) {

	*pData = pStack->numdata;
	return SUCCESS;
}


int stack_top(Stack *pStack, Data *pData) {

	if (stack_is_empty(pStack)) {
		return FAIL;
	}

	if (pData != NULL)
		*pData = pStack->pTop->data;

	return SUCCESS;
}

int main() {

	int N;
	int num;
	
	char plus_min[500000] = { 0 }; 
	// 첫번째 오답 원인. plus_min 은 +와 -를 담는 배열이니까, N의 최대수인 100000보다 적어도 두배는 많아야 한다. 
	int plma = 0; // plus_min배열 = 플마 배열
	int k = 1;

	Stack stack;
	Data data;

	scanf("%d", &N); // 첫줄에 입력받는 정수 N
	stack_init(&stack); 

	for (int i = 0; i < N; i++) {

		scanf("%d", &num);

		if (i > 0 && !stack_is_empty(&stack)) { 
			stack_top(&stack, &data);	
			if (data > num) {
				printf("NO");
				return 0;
			}
			else if (data == num) // 오답원인. 제발 data = num 이랑 == 이랑 헷갈리지 말자...
			{
				stack_pop(&stack, &data);
				plus_min[plma] = '-';
				plma++;
				continue;
			}
		}

		do {
			stack_push(&stack, k);

			plus_min[plma] = '+'; 
			plma++;
			
			k++;

			stack_top(&stack, &data);
		} while (data < num); // stack에 num 값까지만 들어감

		// top 에 있는 data = num 인 상태에서
		stack_pop(&stack, &data);
		plus_min[plma] = '-'; 
		plma++;
	}

	
	for (int t = 0; t < plma; t++) {
		printf("%c\n", plus_min[t]);
	}

	return 0;
} // 맞았습니다!! 