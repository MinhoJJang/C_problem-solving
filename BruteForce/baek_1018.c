#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*
https://www.acmicpc.net/problem/1018
2021.09.03 solved
지민이는 자신의 저택에서 MN개의 단위 정사각형으로 나누어져 있는 M*N 크기의 보드를 찾았다. 어떤 정사각형은 검은색으로 칠해져 있고, 나머지는 흰색으로 칠해져 있다. 지민이는 이 보드를 잘라서 8*8 크기의 체스판으로 만들려고 한다.

체스판은 검은색과 흰색이 번갈아서 칠해져 있어야 한다. 구체적으로, 각 칸이 검은색과 흰색 중 하나로 색칠되어 있고, 변을 공유하는 두 개의 사각형은 다른 색으로 칠해져 있어야 한다. 따라서 이 정의를 따르면 체스판을 색칠하는 경우는 두 가지뿐이다. 하나는 맨 왼쪽 위 칸이 흰색인 경우, 하나는 검은색인 경우이다.

보드가 체스판처럼 칠해져 있다는 보장이 없어서, 지민이는 8*8 크기의 체스판으로 잘라낸 후에 몇 개의 정사각형을 다시 칠해야겠다고 생각했다. 당연히 8*8 크기는 아무데서나 골라도 된다. 지민이가 다시 칠해야 하는 정사각형의 최소 개수를 구하는 프로그램을 작성하시오.

나올수 있는 보드의 경우의 수 

(N - 7) * (M - 7)
*/

#define MAX 55

int main() {

	char Input_WhiteBlack_Board[MAX][MAX];
	int BasicBoard[MAX][MAX] = { 0 }; 
	// W,B를 편의상 0과 1로 바꾼 보드 
	// White = 0, Black = 1

	int width;
	int length;
	
	scanf("%d %d", &length, &width);

	for (int len = 0; len < length; len++) {
		scanf("%s", Input_WhiteBlack_Board[len]);
	}
		
	for (int len = 0; len < length; len++) {
		for (int wid = 0; wid < width; wid++) {
			if (Input_WhiteBlack_Board[len][wid] == 'B') {
				BasicBoard[len][wid] = 1;
			}
		}
	}

	int StoreNumberofColored[MAX][MAX];

	for (int len = 0; len + 7 < length; len++) {
		for (int wid = 0; wid + 7 < width; wid++) {

			int NumberOfColored = 0;
			int StartNum = BasicBoard[len][wid];
			int Cur_len = len; // Cur == current
			int Cur_wid = wid;
			int StartLocation = (len + wid) % 2;

			// White 시작인 경우
			if (StartNum == 0) {

				for (Cur_len = len; Cur_len < len + 8; Cur_len++) {
					for (Cur_wid = wid; Cur_wid < wid + 8; Cur_wid++) {
						int Cur_num = BasicBoard[Cur_len][Cur_wid];
						int Cur_location = (Cur_len + Cur_wid) % 2;

						if (Cur_location == StartLocation) {
							if (Cur_num != StartNum) {
								NumberOfColored++;
							}
						}
						else if (Cur_location != StartLocation) {
							if (Cur_num == StartNum) {
								NumberOfColored++;
							}
						}		
					}
				}							
			}
			
			// Black 시작인 경우
			else if (StartNum == 1) {

				for (Cur_len = len; Cur_len < len + 8; Cur_len++) {
					for (Cur_wid = wid; Cur_wid < wid + 8; Cur_wid++) {
						int cur_num = BasicBoard[Cur_len][Cur_wid];
						int curlocation = (Cur_len + Cur_wid) % 2;

						if (curlocation == StartLocation) {
							if (cur_num != StartNum) {
								NumberOfColored++;
							}
						}
						else if (curlocation != StartLocation) {
							if (cur_num == StartNum) {
								NumberOfColored++;
							}
						}
					}
				}
			}

			// 상식적으로, 64개중에서 절반을 넘게 바꿔야된다면 그건 그냥 시작점을 바꿔주면 되지 않을까? 
			if (NumberOfColored > 32) {
				NumberOfColored = 64 - NumberOfColored;
			}
			StoreNumberofColored[len][wid] = NumberOfColored;
			if (NumberOfColored == 0) {
				printf("%d", NumberOfColored);
				return 0;
			}
		}
	}

	int MinimumNumber = StoreNumberofColored[0][0];

	for (int len = 0; len + 7 < length; len++) {
		for (int wid = 0; wid + 7 < width; wid++) {

			if (MinimumNumber > StoreNumberofColored[len][wid]) {
				MinimumNumber = StoreNumberofColored[len][wid];
			}
		}
	}

	printf("%d", MinimumNumber);

	return 0;
} // 맞았습니다!!!!
