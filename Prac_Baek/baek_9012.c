#include <stdio.h>
#include <stdlib.h> // malloc, rand, atoi ..동적메모리, 난수, 문자열 변환
#include <string.h> //strcpy.. 문자열함수. memcpy.. 메모리블럭 함수
#pragma warning(disable:4996) // scnaf() 등 전통 c함수중 버퍼문제. 
#pragma warning(disable:4477) // unsigned <--> signed 관련 warning 무시 

/*
괄호 문자열(Parenthesis String, PS)은 두 개의 괄호 기호인 ‘(’ 와 ‘)’ 만으로 구성되어 있는 문자열이다. 그 중에서 괄호의 모양이 바르게 구성된 문자열을 올바른 괄호 문자열(Valid PS, VPS)이라고 부른다. 한 쌍의 괄호 기호로 된 “( )” 문자열은 기본 VPS 이라고 부른다. 만일 x 가 VPS 라면 이것을 하나의 괄호에 넣은 새로운 문자열 “(x)”도 VPS 가 된다. 그리고 두 VPS x 와 y를 접합(concatenation)시킨 새로운 문자열 xy도 VPS 가 된다. 예를 들어 “(())()”와 “((()))” 는 VPS 이지만 “(()(”, “(())()))” , 그리고 “(()” 는 모두 VPS 가 아닌 문자열이다.

여러분은 입력으로 주어진 괄호 문자열이 VPS 인지 아닌지를 판단해서 그 결과를 YES 와 NO 로 나타내어야 한다.

입력 데이터는 표준 입력을 사용한다. 입력은 T개의 테스트 데이터로 주어진다. 입력의 첫 번째 줄에는 입력 데이터의 수를 나타내는 정수 T가 주어진다. 각 테스트 데이터의 첫째 줄에는 괄호 문자열이 한 줄에 주어진다. 하나의 괄호 문자열의 길이는 2 이상 50 이하이다.

출력은 표준 출력을 사용한다. 만일 입력 괄호 문자열이 올바른 괄호 문자열(VPS)이면 “YES”, 아니면 “NO”를 한 줄에 하나씩 차례대로 출력해야 한다.
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

// ==========STACK.C==========
void stack_init(Stack *pStack) {
	pStack->pTop = NULL;
	pStack->numdata = 0;
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
	pStack->numdata++;

	return SUCCESS;
}

int stack_pop(Stack *pStack, Data *pData) {

	if (stack_is_empty(pStack) == SUCCESS) {
		return FAIL;
	}

	Node *pCurrent = pStack->pTop;

	if (pData != NULL) // 매우중요!!! pData가 NULL이면 실행되어서는 안됨! 
		
		*pData = pStack->pTop->data;
		pStack->pTop = pStack->pTop->pNext;

		free(pCurrent);

		pStack->numdata--;

	return SUCCESS;
	
}

void stack_destroy(Stack *pStack)
{
	while (!stack_is_empty(pStack)) // 스택이 다 비어질때까지
	{
		stack_pop(pStack, NULL); // 스택이 다 비어질때까지 pop
	}
}

int stack_top(Stack *pStack, Data *pData) {

	if (stack_is_empty(pStack) == SUCCESS) {
		*pData = -1;
		return FAIL;
	}

	else {
		*pData = pStack->pTop->data;
		return SUCCESS;
	}
}

int stack_ans(int a) {
	if (a == 0) {
		printf("NO\n");
	}
	else {
		printf("YES\n");
	}
	return SUCCESS;
}

// ==========STACK.C==========

//이걸 스택으로 어떻게 해결할까? 

// 일단 문자열을 받고, 문자열속의 문자를 하나씩 stack에 담는다. 담은 문자열을 pop 하는데, (1. 만약 top이 (이면 바로 NO return), (2. 문자열 속 문자 개수가 홀수이면 바로 NO return). 그리고 pop 할때 ')' 를 먼저 찾았을 테니,  ')' 를 찾을 때 pop 하고 count 를 1씩 올린다. (를 찾는 순간 count 를 1씩 내린다. 스택이 빌 때까지 진행하고 count이 0이면 YES return

// ========STACKMAIN.C=========
int main() {

	int t, Testcase = 0; // 테스트 데이터
	char PS[100] = { 0 }; // 받을 Parenthesis String 문자열
	int ans[10000] = { 0 }; // YES, NO값을 받을 배열. 숫자로 값을 받고 나중에 숫자값에 따라 YES, NO결정

	Stack stack;
	Data data;

	scanf("%d", &Testcase);

	for (t = 0; t < Testcase; t++) {

		stack_init(&stack); // 스택 생성
		int count = 0;
		
		scanf("%s", PS);
		int len = strlen(PS);

		if (len % 2 != 0) {
			ans[t] = 0; // PS개수가 홀수이면 바로 NO리턴. 
			stack_destroy(&stack);
			continue; // 바로 위의 for문으로 이동
		}

		for (int i = 0; i < len; i++) {
			stack_push(&stack, PS[i]);
		}

		stack_top(&stack, &data);
		if (data == 40) {
			ans[t] = 0; // stack_top이 "(" 면 바로 NO리턴. 
			stack_destroy(&stack);
			continue; // 바로 위의 for문으로 이동
		}

		while (!stack_is_empty(&stack)) {
			stack_pop(&stack, &data);

			if (data == 41) {
				count++; // ')' 이면 카운트 업
			}
			else {
				count--;
			}

			if (count < 0) {
				ans[t] = 0; // pop 하다가 (가 더 많이 pop 되는 순간 NO 리턴
				stack_destroy(&stack);
				break; // while문 탈출
			}
		}

		if (count != 0) {
			ans[t] = 0; // 다 했는데 count가 0보다 크면 짝이 안맞으니까 NO 리턴
			stack_destroy(&stack);
			continue; // for 문으로 바로 이동 
		}
		else {
			ans[t] = 1; // YES 리턴
			stack_destroy(&stack);
		}
	}

	for (int k = 0; k < Testcase; k++) {
		stack_ans(ans[k]);
	}

	return 0;
} // 맞았습니다!
// ========STACKMAIN.C=========