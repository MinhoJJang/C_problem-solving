#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 
#pragma warning(disable:4828) 

#include <math.h>
/*
https://www.acmicpc.net/problem/2447
문제
재귀적인 패턴으로 별을 찍어 보자. N이 3의 거듭제곱(3, 9, 27, ...)이라고 할 때, 크기 N의 패턴은 N×N 정사각형 모양이다.

크기 3의 패턴은 가운데에 공백이 있고, 가운데를 제외한 모든 칸에 별이 하나씩 있는 패턴이다.

***
* *
***
N이 3보다 클 경우, 크기 N의 패턴은 공백으로 채워진 가운데의 (N/3)×(N/3) 정사각형을 크기 N/3의 패턴으로 둘러싼 형태이다. 예를 들어 크기 27의 패턴은 예제 출력 1과 같다.

입력
첫째 줄에 N이 주어진다. N은 3의 거듭제곱이다. 즉 어떤 정수 k에 대해 N=3k이며, 이때 1 ≤ k < 8이다.

출력
*/

#define MAX 10000
#define SUPER_MAX 531500

char save[SUPER_MAX];
// In C, if the array becomes too large, it must be declared as a global variable.

int printarr(int N, char(*board)[MAX]) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%c", board[i][j]);
		}
		printf("\n");
	}

	return 0;
}

int fnStar(int N, char(*board)[MAX], int FirstN) {

	// Start with N = 3;
	// FirstN is Input number

	int Center = N / 3; 
	// Center = 1/3 of N 
	// Because I have to put it in 3x3

	if (N == 3) {

		// create star
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				board[i][j] = '*';
			}
		}

		// delete star
		for (int i = Center; i < Center * 2; i++) {
			for (int j = Center; j < Center * 2; j++) {
				board[i][j] = ' ';
			}
		}
	}

	else {

		// Put everything on the existing board 
		// in a one-dimensional arrangement one by one. 
		int idx = 0;

		for (int i = 0; i < Center; i++) {
			for (int j = 0; j < Center; j++) {
				save[idx++] = board[i][j];
			}
		}

		// create star
		int x = 0;
		int y = 0;

		while (x != N) {
			idx = 0;
			for (int i = x; i < x + Center; i++) {
				for (int j = y; j < y + Center; j++) {
					board[i][j] = save[idx++];
				}
			}
			if (y == Center * 2) {
				y = 0;
				x = x + Center;
			}
			else {
				y = y + Center;
			}
		}

		// delete star 
		for (int i = Center; i < 2 * Center; i++) {
			for (int j = Center; j < 2 * Center; j++) {
				board[i][j] = ' ';
			}
		}
	}

	if (N == FirstN) {
		return printarr(N, board);
	}

	return fnStar(N * 3, board, FirstN);
}

char board[MAX][MAX];

int main() {

	int N;
	scanf("%d", &N);
	fnStar(3, board, N);

	return 0;
} // 맞았습니다!