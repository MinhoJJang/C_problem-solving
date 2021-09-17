#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

#define X 0
#define Y 1

int fn_x(int N, int(*arr)[2]) {

	// 기본적으로 값 넣어주고 
	if (N == 0) {

		arr[N][X] = 1;
		return arr[N][X];
	}
	else if (N == 1) {

		arr[N][X] = 0;
		return arr[N][X];
	}

	// 만약 찾으려는 arr에 N번째 배열에 아무런 값도 없다면 
	if (arr[N][X] == 0) {

		arr[N][X] = fn_x(N - 1, arr) + fn_x(N - 2, arr);
		return arr[N][X];
		// 핵심적인 두줄. arr에 fn_x(N, ~)값을 기억함으로써 바로바로 답안 도출되도록 했음. 	
	}
	// 값이 있다면
	else {
		return arr[N][X];
	}
}

int fn_y(int N, int(*arr)[2]) {

	// 기본적으로 값 넣어주고 
	if (N == 0) {

		arr[N][Y] = 0;
		return arr[N][Y];
	}
	else if (N == 1) {

		arr[N][Y] = 1;
		return arr[N][Y];
	}

	// 만약 찾으려는 arr에 N번째 배열에 아무런 값도 없다면 
	if (arr[N][Y] == 0) {

		arr[N][Y] = fn_y(N - 1, arr) + fn_y(N - 2, arr);
		return arr[N][Y];
		// 문제풀이에 핵심적인 두줄. arr에 fn_y(N, ~)값을 기억함으로써 바로바로 답안 도출되도록 했음. 	

		// 처음에 return fn_y(N - 1, arr) + fn_y(N - 2, arr); 해서 시간초과났음. 
	}
	// 값이 있다면
	else {
		return arr[N][Y];
	}
}

void showArr(int Testcase, int(*arr)[2]) {

	for (int i = 0; i < Testcase; i++) {
		printf("%d %d\n", arr[i][0], arr[i][1]);
	}

}

int main() {

	int Testcase;
	int testArr1[100][2] = { 0 };
	int ansArr[100][2] = { 0 };
	int N;

	scanf("%d", &Testcase);

	for (int i = 0; i < Testcase; i++) {

		scanf("%d", &N);
		
		ansArr[i][0] = fn_x(N, testArr1);
		ansArr[i][1] = fn_y(N, testArr1);
	}

	showArr(Testcase, ansArr);

	return 0;
} // 맞았습니다! 