#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <math.h>
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 
/*
예를 들어, 10보다 크고, 20보다 작거나 같은 소수는 4개가 있다. (11, 13, 17, 19) 또, 14보다 크고, 28보다 작거나 같은 소수는 3개가 있다. (17,19, 23)

자연수 n이 주어졌을 때, n보다 크고, 2n보다 작거나 같은 소수의 개수를 구하는 프로그램을 작성하시오. 

입력은 여러 개의 테스트 케이스로 이루어져 있다. 각 케이스는 n을 포함하는 한 줄로 이루어져 있다.

입력의 마지막에는 0이 주어진다.

각 테스트 케이스에 대해서, n보다 크고, 2n보다 작거나 같은 소수의 개수를 출력한다.

1 ≤ n ≤ 123,456
*/

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
#define MAX 246920


int arr[MAX] = {PRIME}; // 전부 PRIME 이라고 가정 
int num[MAX] = {0};
int numIdx = 0;

int answer[MAX] = {0};
int ansIdx = 0;

void putData(){
    do{
        scanf("%d", &num[numIdx]); 
        numIdx++;
    } while (num[numIdx-1] != 0);
}

int findNextPrime(int a){
    int primeIdx = a+1;
    while(num[primeIdx] != PRIME){
        primeIdx++;
    }
    return primeIdx;
}

void mainLogic(){

    // 0, 1은 소수가 아님
    // 1-based 배열
    arr[0] = NOTPRIME;
    arr[1] = NOTPRIME;

    // 가장 마지막으로 조사한 수 
    // 일단 위에서 1까지 조사했으니까
    int currentPrime = findNextPrime(1);
    //int flag = pow(currentPrime, 2);
    // 체 거르기
    while(currentPrime <= (int)sqrt(MAX)){
        for(int i = 2; i*currentPrime<=MAX; i++){
            arr[i*currentPrime] = NOTPRIME;
        }
        currentPrime = findNextPrime(currentPrime);
    }
}

void searchAllPrime(){

    int count = 0;
    int idx = 0;

    while(idx<numIdx){

        int n = num[idx];

        for(int i=n+1; i<=n*2; i++){
            if(arr[i]==PRIME){
                count++;
            }
        }

        answer[ansIdx] = count;
        ansIdx++;
        idx++;
    }
}

void printAnswer(){
    for(int i=0; i<numIdx; i++){
        printf("%d\n", answer[i]);
    }
}

int main(){

    putData();
    mainLogic();
    searchAllPrime();
    printAnswer();

    return 0;
}