#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
 원판을 옮기는 시작위치는 원판이 짝수인지 홀수인지에 따라 달라짐. 

 원판이 홀수개면 1-3 시작
 짝수면 1-2 시작

 원판은 첫 원판을 제외하고, 항상 놓을 수 있는 원판 중에서 가장 작은 것 위에 올라가야 한다. 



*/
#define MAX 1050000


int fnTotal(int N) {

	if (N == 1 || N == 0) {
		return 1;
	}
	else {
		return (fnTotal(N - 1) * 2) + 1;
	}
}


void printarr(int N, int(*arr)[2]) {

	int total = fnTotal(N);

	for (int i = 0; i < total; i++) {

		printf("%d %d \n", arr[i][0], arr[i][1]);
	}

}

int copyArr[MAX][2];
int newArr[MAX][2];

int fn(int N, int arr[][2], int firstN) {

	// newarr1에 arr값을 복사해야함. 

	int total = fnTotal(N - 1);
	for (int i = 0; i < total; i++) {

		copyArr[i][0] = arr[i][0];
		copyArr[i][1] = arr[i][1];
	}

	int idx = 0;


	// 일단 맨 처음이 1-2인지 1-3인지 알아야 함
	if (idx == 0) { 

		newArr[idx][0] = 1;

		if (N % 2 == 1) {
			newArr[idx][1] = 3;
		}
		else {
			newArr[idx][1] = 2;
		}

		idx++;
	}


	if (N == 1) {
		return fn(N + 1, newArr, firstN);
	}
	else	if(N>1){

		// 먼저 배열에 있던 값들을 전부 새 배열로 옮겨준다. 
		// 총 배열의 개수는 fnTotal에서 가져오자. 

		for (int i = total-1; i >= 0; i--) {
			newArr[i * 2 + 1][0] = copyArr[i][0];
			newArr[i * 2 + 1][1] = copyArr[i][1];
		}

		// 아직 들어가지 않은 곳 첫번째에 값을 넣어준다. 
		newArr[2][0] = newArr[0][1];
		newArr[2][1] = newArr[1][1];

		int j = 4;
		int newtotal = fnTotal(N);
		// 이게 두번째 배열이 2-3이냐 3-2이냐에 따라 달라짐
		if (newArr[2][0] == 2) {

			
			while (j < newtotal) {

				newArr[j][0] = newArr[j-2][1];
				newArr[j][1] = newArr[j][0] + 1;
				
				if (newArr[j][1] == 4) {
					newArr[j][1] = 1;
				}

				j = j + 2;
			}
		}
		else {
			while (j < newtotal) {

				newArr[j][0] = newArr[j - 2][1];
				newArr[j][1] = newArr[j][0] -1;

				if (newArr[j][1] == 0) {
					newArr[j][1] = 3;
				}

				j = j + 2;
			}
		}
	}
	if (N == firstN) {
		printarr(N, newArr);
		return 0;
	}
	return fn(N + 1, newArr, firstN);
	
}



int main() {

	int N;
	scanf("%d", &N);

	printf("%d\n", fnTotal(N));

	if (N == 1) {
		printf("1 3");
	}
	else {
		fn(1, copyArr, N);
	}


	return 0;
}