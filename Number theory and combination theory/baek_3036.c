#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
상근이는 창고에서 링 N개를 발견했다. 상근이는 각각의 링이 앞에 있는 링과 뒤에 있는 링과 접하도록 바닥에 내려놓았다.

상근이는 첫 번째 링을 돌리기 시작했고, 나머지 링도 같이 돌아간다는 사실을 발견했다. 나머지 링은 첫 번째 링 보다 빠르게 돌아가기도 했고, 느리게 돌아가기도 했다. 이렇게 링을 돌리다 보니 첫 번째 링을 한 바퀴 돌리면, 나머지 링은 몇 바퀴 도는지 궁금해졌다.

링의 반지름이 주어진다. 이때, 첫 번째 링을 한 바퀴 돌리면, 나머지 링은 몇 바퀴 돌아가는지 구하는 프로그램을 작성하시오.
*/

/*
첫번쨰 수를 분자로 두고, 뒤에수를 분모로 두고 그 분수를 최대한 약분한 값이 곧 답입 
*/
#define MAX 105
#define TRUE 1
#define FALSE 0

int arr[MAX] = { 0 };
int n;

// 데이터값 넣기 
void putData() {

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

// 숫자의 절댓값 
int abs(int x) {
	if (x < 0) {
		return -x;
	}
	return x;
}

int printCurrentAnswer(int a, int b) {
	printf("%d/%d\n", a, b);
	return 0;
}

// 약수 찾는 함수 
// 이때 a는 항상 arr[0] 이다. 
int findAliquot(int a, int b) {

	int aliquot[MAX] = { 0 }; // 약수저장하는 배열 
	int idx = 0; // 위 배열의 인덱스 
	int flag = FALSE; // 나누어 떨어지지 않으면 FALSE, 나누어 떨어지면 TRUE
	int mom = a; // 분모
	int son = b; // 분자 

	// 1. 두 수의 차의 절댓값을 구한다. 
	int diff = abs(a - b);

	// 만약 수의 차이가 0일 경우, 답은 항상 1/1이므로 
	if (diff == 0) {
		return printCurrentAnswer(1, 1);
	}

	// 2. 그 절댓값의 약수를 배열에 저장한다. 약수니까 i는 2부터 시작
	// 숫자가 크면 특수하게 찾을려고 했지만 1000정도면 그냥 for문 돌려도 무방하다고 생각했음 
	for (int i = 2; i <= diff; i++) {
		if (diff % i == 0) {
			aliquot[idx++] = i;
		}
	}

	// 3. a,b가 나누어 떨어질 때까지 약수로 나눈다...
	// - 만약 나누어 떨어지지 않으면, 그냥 a,b를 리턴한다. 
	// - 나누어 떨어지면, flag를 세우고, 일단 for문 끝까지 다 나누고 나서 다시 함수를 호출한다. 이때, 분자 혹은 분모가 1이면 함수호출은 생략한다. 
	for (int i = 0; i < idx; i++) {
		if (mom % aliquot[i] == 0 && son % aliquot[i] == 0) {
			mom /= aliquot[i];
			son /= aliquot[i];
			if (mom == 1 || son == 1 || abs(mom - son) == 1) {
				break;
			}
			flag = TRUE;
		}
	}

	if (flag == FALSE) {
		return printCurrentAnswer(mom, son);
	}
	else {
		return findAliquot(mom, son);
	}
}

void printAns(int n) {

	int mother = arr[0];
	int sonidx = 1;

	while (sonidx != n) {
		// ans의 0번째 인덱스는 없다고 치고.. 
		// arr[0] / arr[1], arr[0] / arr[2] ... 이렇게.. 

		// 1. 일단 분자 분모 사이에 공통인수가 있는지 알아야 한다. 
		// 함수를 만들자
		// 그리고 일단 분자나 분모가 1이거나 분자와 분모의 차가 1이면 나누어 떨어질 리가 없으므로 이 경우는 제외 
		if (arr[0] == 1 || arr[sonidx] == 1 || abs(arr[0] - arr[sonidx]) == 1) {
			printCurrentAnswer(arr[0], arr[sonidx]);
		}
		else {
			findAliquot(arr[0], arr[sonidx]);
		}
		sonidx++;
	}
}

int main() {

	putData();
	printAns(n);

	return 0;
} // 맞았습니다!