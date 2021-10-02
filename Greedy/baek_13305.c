#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

// 도시 사이의 거리 따로 입력받고
// 도시마다의 기름값 입력받는다.


// 이때 기름값과 도시 위치 인덱스를 받는 구조체를 만들자.

// 그리고 기름값이 제일 싼 도시를 찾고, (제일 싼 도시가 여러개여도 사실 상관없다) 그 도시의 인덱스를 k라 하자. 그러면 0부터 k까지의 도시 중에서 제일 싼 도시를 찾고 계속 반복한다. 종료 시점은 선택한 도시가 제일 앞의 도시가 되었을 때이다. (무조건 맨 처음은 가격에 상관없이, 다음 도시까지 가는데 드는 기름은 넣어야 한다.)

/*
최악의 경우를 상정해서 모든 도시의 기름값이 10억이고, 최대거리가 10억이면...? 10억*10억 = 을 표현 가능한 자료형인 unsigned long long은 변수명이 너무기니까 다른 이름으로 바꿔주자. -> 가격의 자료형을 ValueData 로 바꿔주자.

도시의 수를 N, 가격이 제일 싼 도시의 위치인덱스를 k, 가격을 저장한 배열을 value[], 그 위치의 가격은 value[k], 도시 사이의 거리를 저장한 배열을 arr[], 마지막으로 찾은 도시위치를 end라고 하자. end는 초기에 N-1이다.

 value에 더해야 할 값은
 (arr[k] + ... + arr[end-1]) * value[k] 이다.
 이후 인덱스 0부터 k값을 또 찾고.. 반복한다.
*/

typedef unsigned long long valueData;
#define MAX 100005
int len[MAX]; // 도시 사이 거리
valueData value[MAX]; // 도시의 기름값
valueData minSum = 0; // 최소 비용 합계

void inputData(int N) {

	for (int i = 0; i < N - 1; i++) {
		scanf("%d", &len[i]);
	}

	for (int i = 0; i < N ; i++) {
		scanf("%d", &value[i]);
	}
}

valueData findMinimumValue(int N) {

	int mostCheapIdx = 0; // 가격이 제일 싼 도시의 위치인덱스
	int endIdx = N; // 초기값

	// 1. 일단 가격이 가장 저렴한 위치를 찾자. 
	valueData minValue = value[0];
	int cityIdx = 0; // 현재 도시의 위치

	// 2. cityIdx가 N보다 작을 때까지 수행
	while (cityIdx < N - 1) {

		// 현재 도시의 기름값과, 그전 도시까지 가장 저렴했던 기름값을 비교한다. 만약 기름값이 1이면 이 로직을 수행하지 않는다. 
		if (minValue != 1) {
			if (minValue > value[cityIdx]) {
				minValue = value[cityIdx];
			}
		}

		// 현재까지 가장 저렴한 기름값 * 지금 도시와 다음 도시 사이 거리를 곱한 값을 더한다.
		minSum += minValue * len[cityIdx];

		// 다음 도시로 이동
		cityIdx++;
	}

	return minSum;
}

int main() {

	int N; // 도시의 수
	
	scanf("%d", &N);
	inputData(N);
	printf("%lld", findMinimumValue(N));

	return 0;
} 

// 왜 부분성공이지? 
// 최악의 경우, O(n^2) 상황이 발생함.. 
// 즉 시간초과가 날 수도 있다는 것 

// 로직을바꿔서, 현재 기름값을 가장 싼 기름값으로 치고, 그다음 기름값과 비교해서 만약 그 다음 기름값이 더 싸면 가장 싼 기름값을 바꾸고 그 다음 도시까지의 비용을 곱하고... 이런식으로! 이게 그리디지..

// idx 0 부터 endIdx까지 조사하면서 최소가격 위치를 찾는다. 

/* <기존로직>
while (currentIdx < endIdx) {
	if (minValue > value[currentIdx]) {
		minValue = value[currentIdx];
		mostCheapIdx = currentIdx;
	}
	if (minValue == 1) {
		break; // 1원이면 가장 싸니까 
	}
	currentIdx++;
}

// 최소가격 위치부터 끝까지 도시거리 합을 구한다. 
valueData lenSum = 0;
for (int i = mostCheapIdx; i < endIdx; i++) {
	lenSum += len[i];
}
// endIdx쪽 손보자 

minSum += lenSum * value[mostCheapIdx];
endIdx = mostCheapIdx;

if (mostCheapIdx != 0) {

	return findMinimumValue(endIdx);
} 

--> 시간초과로 58점이었음
*/
