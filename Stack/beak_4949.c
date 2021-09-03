#include <stdio.h>
#include <stdlib.h> // malloc, rand, atoi ..동적메모리, 난수, 문자열 변환
#include <string.h> //strcpy.. 문자열함수. memcpy.. 메모리블럭 함수
#pragma warning(disable:4996) // scnaf() 등 전통 c함수중 버퍼문제. 
#pragma warning(disable:4477) // unsigned <--> signed 관련 warning 무시 

// =========HEADER.H==========

#define SUCCESS 1
#define FAIL 0

#define YES 10
#define NO 5

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

void stack_destroy(Stack *pStack)
{
	while (!stack_is_empty(pStack)) // 스택이 다 비어질때까지
	{
		stack_pop(pStack, NULL); // 스택이 다 비어질때까지 pop
	}
}

int stack_ans(int a) {
	if (a == NO) {
		printf("no\n");
	}
	else {
		printf("yes\n");
	}
	return SUCCESS;
}
// ==========STACK.C===========


// ==========STACKMAIN.C===========
int main() {

	int ans[1000] = { 0 };
	int idx = 0; // 반복횟수
	Stack stack;
	Stack stack_new;
	Stack stack_new2;
	Stack check_stack; // 괄호가 pop될때의 numdata를 입력받을 스택 생성 
	Data data;
	char sentence[110] = { 0 };

	for (int i = 0; i < 1000; i++) { // '.'입력받을때까지 계속 for문 돌림
	first:
		fgets(sentence, 110, stdin); // gets쓰면 안되나????
		int len = strlen(sentence); // 문장길이 변수로 저장

		if (sentence[0] == '.' && len == 2) {
			break; // '.' 하나를 입력받으면 입력 종료이므로 for문 탈출
		}

		if (i > 0) {
			stack_destroy(&stack);
			stack_destroy(&stack_new);
			stack_destroy(&stack_new2);
			stack_destroy(&check_stack);
		}

		stack_init(&stack); // for문 시작할때마다 스택 새로 생성
		stack_init(&stack_new);
		stack_init(&stack_new2);
		stack_init(&check_stack);

		int PS1_1count = 0; // ')' 개수 
		int PS1_2count = 0; // '(' 개수 

		int PS2_1count = 0; // ']' 개수 
		int PS2_2count = 0; // '[' 개수 

		idx++; // 전체for문 반복횟수

		// 괄호만 stack에 넣기. 
		for (int k = 0; k < len; k++) {
			if (sentence[k] == '(' || sentence[k] == ')' || sentence[k] == '[' || sentence[k] == ']') {
				stack_push(&stack, sentence[k]);
				stack_push(&stack_new, sentence[k]);
				stack_push(&stack_new2, sentence[k]);
			}
		}

		// 스택 상에는 '(' 와 같은 문자가 아니라 40과 같은 아스키코드 숫자로 들어온다. 

		stack_size(&stack, &data);

		if (data == 0) { // 만약 공백만 있는 문자열이면 yes 리턴 
			ans[i] = YES;
			stack_ans(ans[i]);
			continue; // for문으로 이동 
		}
		if (data % 2 != 0) { // size값이 홀수면 no리턴
			ans[i] = NO;
			stack_ans(ans[i]);
			continue; // for문으로 이동 
		}

		stack_top(&stack, &data);
		if (data == 40 || data == 91) {
			// asciicode ( = 40, ) = 41, [ = 91, ] = 93
			// stack_top이 '[' 이거나 '(' 이면 바로 no 리턴
			ans[i] = NO;
			stack_ans(ans[i]);
			continue;  // for문으로 이동 
		}

		while (!stack_is_empty(&stack)) { // 스택이 다 비어질때까지
			stack_pop(&stack, &data);

			if (data == 41) {
				PS1_1count++; // ) 개수 
			}
			else if (data == 40) {
				PS1_2count++; // ( 개수 
			}
			else if (data == 93) {
				PS2_1count++; // ] 개수 
			}
			else if (data == 91) {
				PS2_2count++; // [ 개수 
			}

			if (PS1_1count - PS1_2count < 0 || PS2_1count - PS2_2count < 0) { // count 값이 한번이라도 음수가 되는 순간 짝이 절대 맞을 수 없음
				ans[i] = NO;
				stack_ans(ans[i]);
				goto first;
			}
		}

		if (PS1_1count - PS1_2count > 0 || PS2_1count - PS2_2count > 0) {
			ans[i] = NO;
			stack_ans(ans[i]);
			continue;
		}

		if (PS1_1count - PS1_2count == 0 && PS2_1count - PS2_2count == 0) {

			int total = PS1_1count + PS1_2count + PS2_1count + PS2_2count;

			Data size_data;
			Data check_data; // check_stack에서 pop된 data
			int check = 0; // 차이값 담을 변수
			int t = 0;

			if (PS1_1count > 0) {

				for (t = 0; t < total; t++) {

					stack_pop(&stack_new, &data);
					if (data == 41) { // 만약 ) 이면
						stack_size(&stack_new, &size_data); // pop된 상태에서 stack 내 개수 data
						stack_push(&check_stack, size_data); // 그 data값을 새로운 check_stack에 push
					}
					else if (data == 40) { // 만약 ( 만나는 순간
						stack_size(&stack_new, &size_data); // pop된 상태에서 stack 내 개수 data
						stack_pop(&check_stack, &check_data); // check_stack에서 pop 시켜 check_data 뽑아냄
						check = check_data - size_data; // 이때 반드시 check_data보다 size_data값이 더 작을 것임. 

						if (check % 2 == 0) { // 그 차이가 2의 배수이면 반드시 괄호 안에 홀수개의 괄호가 있으므로 균형잡힌 문자열이 아님 
							ans[i] = NO;		
							break; // for문 탈출 
						}
						else {
							ans[i] = YES;
							continue;
						}
					}
				}
			}

			int test = i;
			int anstest[1000] = { 0 };

			stack_destroy(&check_stack);
			stack_init(&check_stack);
			check = 0;


			if (PS2_1count > 0) {
				for (t = 0; t < total; t++) {

					// 소괄호 작동방식이랑 똑같음 
					stack_pop(&stack_new2, &data);

					if (data == 93) { // 만약 ] 이면
						stack_size(&stack_new2, &size_data); // pop된 상태에서 stack 내 개수 size_data
						stack_push(&check_stack, size_data); // 그 size_data값을 새로운 check_stack에 push
					}

					else if (data == 91) { // 만약 [ 만나는 순간
						stack_size(&stack_new2, &size_data); // pop된 상태에서 stack 내 개수 size_data
						stack_pop(&check_stack, &check_data); // check_stack에서 pop 시켜 check_data 뽑아냄
						check = check_data - size_data; // 이때 반드시 check_data보다 size_data값이 더 작을 것임. 

						if (check % 2 == 0) { // 그 차이가 2의 배수이면 반드시 괄호 안에 홀수개의 괄호가 있으므로 균형잡힌 문자열이 아님 
							anstest[test] = NO;
							break; // for문 탈출 
						}
						else {
							anstest[test] = YES;
							continue;
						}
					}
				}
			}

			if ((ans[i] == YES || ans[i] == 0)&& (anstest[test] == YES || anstest[test] == 0)) { // 둘다 yes이면 yes.
				ans[i] = YES;
				stack_ans(ans[i]);
			}
			else {
				ans[i] = NO;
				stack_ans(ans[i]);
			}
		}

		//	stack_ans(ans[i]);
	}

	// 이후 stack_ans 에 ans[i]값 입력 
	//for (int j = 0; j < idx; j++) {
	//    stack_ans(ans[i]);
	//}

	return 0;
}