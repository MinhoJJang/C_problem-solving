#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <math.h>

/* 1보다 큰 자연수 중에서  1과 자기 자신을 제외한 약수가 없는 자연수를 소수라고 한다. 예를 들어, 5는 1과 5를 제외한 약수가 없기 때문에 소수이다. 하지만, 6은 6 = 2 × 3 이기 때문에 소수가 아니다.

골드바흐의 추측은 유명한 정수론의 미해결 문제로, 2보다 큰 모든 짝수는 두 소수의 합으로 나타낼 수 있다는 것이다. 이러한 수를 골드바흐 수라고 한다. 또, 짝수를 두 소수의 합으로 나타내는 표현을 그 수의 골드바흐 파티션이라고 한다. 예를 들면, 4 = 2 + 2, 6 = 3 + 3, 8 = 3 + 5, 10 = 5 + 5, 12 = 5 + 7, 14 = 3 + 11, 14 = 7 + 7이다. 10000보다 작거나 같은 모든 짝수 n에 대한 골드바흐 파티션은 존재한다.

2보다 큰 짝수 n이 주어졌을 때, n의 골드바흐 파티션을 출력하는 프로그램을 작성하시오. 만약 가능한 n의 골드바흐 파티션이 여러 가지인 경우에는 두 소수의 차이가 가장 작은 것을 출력한다.

입력
첫째 줄에 테스트 케이스의 개수 T가 주어진다. 각 테스트 케이스는 한 줄로 이루어져 있고 짝수 n이 주어진다.

출력
각 테스트 케이스에 대해서 주어진 n의 골드바흐 파티션을 출력한다. 출력하는 소수는 작은 것부터 먼저 출력하며, 공백으로 구분한다. */


// 에라토스테네스의 체 이용

/*
로직:

1. 2n의 최댓값만큼의 배열을 만들고, 모두 소수로 가정(TRUE)한다. 물론 1은 제외.
2. 2를 제외하고, 2의 배수들에게 모두 FALSE를 부여한다.
3. 2다음 TRUE인 숫자를 찾고, 그 숫자를 k라고 했을 때 k의 배수들에게 FALSE를 부여한다.
4. 그렇게 계속 하다가, k^2 > 2n 이 되는 순간 로직 종료.
*/

#define PRIME 0
#define NOTPRIME -1

#define SMALLONE 0
#define BIGONE 1

#define MAX 10005

int n;
int arr[MAX] = { PRIME }; // 전부 PRIME 이라고 가정 
int num[MAX] = { 0 };
int numIdx = 0;

int answer[MAX][2] = { 0 };
int ansIdx = 0;

void putData() {
    
    scanf("%d", &n);

	for (numIdx=0; numIdx<n; numIdx++) {
		scanf("%d", &num[numIdx]);
	}
}

int searchNextPrime(int a) {
	int primeIdx = a + 1;
	while (arr[primeIdx] != PRIME) {
		primeIdx++;
	}
	return primeIdx;
}

void mainLogic() {

	// 0, 1은 소수가 아님
	// 1-based 배열
	arr[0] = NOTPRIME;
	arr[1] = NOTPRIME;

	// 가장 마지막으로 조사한 수 
	// 일단 위에서 1까지 조사했으니까
	int currentPrime = searchNextPrime(1);
	
	// 체 거르기
	int Maxprime = (int)sqrt(MAX);
	while (currentPrime <= Maxprime) {
		for (int i = currentPrime; i*currentPrime <= MAX; i++) {
			arr[i*currentPrime] = NOTPRIME;
		}
		currentPrime = searchNextPrime(currentPrime);
	}
}

// 골드바흐 추측..
// 2부터 해서 입력받은 숫자에다가 소수를 빼고, 그 빼고 남은 숫자가 PRIME 인지 확인. 

void findPartition(int inputNum){
   
    int currentPrime = 2; // 언제나 2부터 시작 

    while(currentPrime <= inputNum/2){
        // 만약 입력값에서 현재 소수값을 뺀 값이 소수라면..
        if(arr[inputNum - currentPrime] == PRIME ){
            answer[ansIdx][SMALLONE] = currentPrime;
            answer[ansIdx][BIGONE] = inputNum-currentPrime;
        }
        // 차이값이 소수가 아니라면 현재 소수값을 다음 소수값으로 바꿔준다
        currentPrime = searchNextPrime(currentPrime);
    }
    ansIdx++;
}

void printAns(){

    for(int idx = 0; idx<numIdx; idx++){
        int inputNum = num[idx];
        findPartition(inputNum);
        printf("%d %d\n", answer[idx][SMALLONE], answer[idx][BIGONE]);
    }
}

int main() {

	putData();
	mainLogic();
	printAns();

	return 0;
} // 맞았습니다!