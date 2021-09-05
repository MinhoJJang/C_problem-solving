#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <math.h>
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 
#define DIGIT_NUM 10

// https://www.acmicpc.net/problem/1436

int main() {

	int index;
	scanf("%d", &index);
	
	int count = 0; // 문자열에서 666을 찾으면 +1
	int num = 665; //  num을 1씩 올리고 comp_idx에 넣고 문자열 비교할것임
	
	while (index != count) {

		char comp_idx[DIGIT_NUM] = { 0 }; // 숫자 자리수 
		num++;
		sprintf(comp_idx, "%d", num);

		char *findit = strstr(comp_idx, "666");
		if (findit) {
			count++;
		}
	}

	printf("%d", num);

	return 0;
}