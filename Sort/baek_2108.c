#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
수를 처리하는 것은 통계학에서 상당히 중요한 일이다. 통계학에서 N개의 수를 대표하는 기본 통계값에는 다음과 같은 것들이 있다. 단, N은 홀수라고 가정하자.

산술평균 : N개의 수들의 합을 N으로 나눈 값
중앙값 : N개의 수들을 증가하는 순서로 나열했을 경우 그 중앙에 위치하는 값
최빈값 : N개의 수들 중 가장 많이 나타나는 값
범위 : N개의 수들 중 최댓값과 최솟값의 차이
N개의 수가 주어졌을 때, 네 가지 기본 통계값을 구하는 프로그램을 작성하시오.

마찬가지로 arr[4002] = {0}; 을 만들고 배열에다 그 수의 개수를 담는다. 

산술-> 입력받음과 동시에 sum += x 그냥하면되고

중앙값-> arr[idx] 개수 더하다가 N/2넘는순간 그 idx출력

최빈값-> arr[idx]를 내림차순 정렬하고 최빈값 찾기

범위 -> 정렬한 데이터 중에서 맨 처음과 맨 끝 idx값의 차 
*/

// -4000 ~ +4000
#define MAX 8005
#define ABSOLUTE 4000

int arr[MAX] = { 0 };

double sum = 0;
double arithmetic_mean = 0;

int median_value = 0;
// N이 홀수이므로, 중앙값은 N/2번째에 있는 수이다. 

int common_value = 0;
int maxRange = 0;

void inputData(int N) {
	int idx;
	for (int i = 0; i < N; i++) {
		scanf("%d", &idx);
		// 최소 -4000, 최대 4000의 수가 입력됨. 
		// 즉 arr의 idx+4000번째에 수를 담은 것임 
		// 만약 0이 입력되면 arr[4000]에 0의 개수가 담기는것
		// -4000이 입력되면 arr[0]에 개수가 담김
		arr[idx+ABSOLUTE]++;
		sum += idx;
	}
}

// 소수점 아래 첫째 자리에서 반올림해 출력
void printArithmeticMean(int N) {

	arithmetic_mean = sum / N;

	printf("%.0f\n", arithmetic_mean);
}

void printMedianValue(int N) {

	int count = 0;
	int aim = N / 2 + 1;
	int currentIdx = 0;

	while (count < aim) {
		count += arr[currentIdx++];	
	}

	// 실제 값은 idx-4000
	median_value = currentIdx - ABSOLUTE - 1;
	printf("%d\n", median_value);
}

#define INITIALIZE 0
#define FINDFIRST 1
#define FINDSECOND 2

void printCommonValue() {

	int flag; // 일단 가장 큰 값을 찾으면 flag에 그 값이 저장된 배열의 idx값을 저장한다.
	int identify = INITIALIZE; // 최빈값을 찾은 순서에 따라 값 배정
	int maxNum = 0;

	for (int idx = 0; idx < MAX; idx++) {

		// 현재 최빈값보다 더 큰 값을 찾으면
		if (maxNum < arr[idx]) {
			maxNum = arr[idx];
			flag = idx;

			// 첫번째로 찾은 최빈값이라는 의미로.. 
			identify = FINDFIRST;
		}
		// 현재 최빈값과 값이 같고, 최빈값이 0이 아닐경우
		else if (maxNum == arr[idx] && maxNum != 0) {
			// 이게 두번째로 찾은 최빈값이면 값을 저장한다. 
			if (identify == FINDFIRST) {
				flag = idx;
				identify = FINDSECOND;
			}
		}
	}

	common_value = flag - ABSOLUTE;
	printf("%d\n", common_value);
}

void printMaxRange() {

	int low = -1;
	int high = -1;
	int lowIdx = 0;
	int highIdx = MAX-1;

	while (low == -1) {
		if (arr[lowIdx] != 0) {
			low = lowIdx;
		}
		lowIdx++;
	}

	while (high == -1) {
		if (arr[highIdx] != 0) {
			high = highIdx;
		}
		highIdx--;
	}

	maxRange = high - low;

	printf("%d\n", maxRange);
}

int main() {

	int N;
	scanf("%d", &N);

	inputData(N);
	printArithmeticMean(N);
	printMedianValue(N);
	printCommonValue();
	printMaxRange();

	return 0;
} // 맞았습니다! 