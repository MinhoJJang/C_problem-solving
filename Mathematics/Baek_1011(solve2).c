#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 
#include <math.h>
/*

*/

#define MAX 3000

int main() {

	long start, end, range, temp;
	int Test, t;

	// 어차피 y-x가 중요한거니까, 이 값마다 배열을 만들자 

	scanf("%d", &Test);

	long ans[MAX] = { 0 };

	for (t = 0; t < Test; t++) {

		scanf("%d%d", &start, &end);

		range = end - start;
		temp = sqrt(range);
	
		while (1) {
			if (range - temp * temp <= 0) {
				break;
			}
			temp++;
		}

		if (range > temp*temp - temp) {
			ans[t] = 2 * temp - 1;
		}
		else {
			ans[t] = 2 * temp - 2;
		}
	}

	for (t = 0; t < Test; t++) {
		printf("%d\n", ans[t]);
	}

	return 0;
} 

// int 여서 시간초과했음... long으로 바꾸니 바로 통과함 
// temp제곱값이 int범위를 초과해버리는 순간 while문이..너무많이돌게됨 