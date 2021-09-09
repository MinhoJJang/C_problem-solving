#include <stdio.h> //표준 입출력헤더 
#pragma warning(disable:4996) //scanf()등 ANSI C함수 에러 메세지 무시

/*

*/

int main() {

	//N에서 3을 빼면서 그 값이 5의 배수이면 종료하기.
	int N = 0;
	int count = 0;
	scanf("%d", &N);

	if (N == 4) {
	    printf("%d", -1);
		return 0;
	}
	else if (N == 7) {
		printf("%d", -1);
		return 0;
	}
	else if (N % 5 == 0) {
		printf("%d", N / 5);
		return 0;
	}

	for (int i = 0; ; i++) {

		N = N - 3;

		if (N % 5 == 0) {
			printf("%d", (N / 5)+count+1);
			break;
		}
		else {
			count++;
		}
	}

	return 0;
} //end main()