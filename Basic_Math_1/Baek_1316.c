/*
https://www.acmicpc.net/problem/1316
그룹 단어란 단어에 존재하는 모든 문자에 대해서, 각 문자가 연속해서 나타나는 경우만을 말한다. 예를 들면, ccazzzzbb는 c, a, z, b가 모두 연속해서 나타나고, kin도 k, i, n이 연속해서 나타나기 때문에 그룹 단어이지만, aabbbccb는 b가 떨어져서 나타나기 때문에 그룹 단어가 아니다.

단어 N개를 입력으로 받아 그룹 단어의 개수를 출력하는 프로그램을 작성하시오.

첫째 줄에 단어의 개수 N이 들어온다. N은 100보다 작거나 같은 자연수이다. 둘째 줄부터 N개의 줄에 단어가 들어온다. 단어는 알파벳 소문자로만 되어있고 중복되지 않으며, 길이는 최대 100이다.
*/
#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
#define MAX 100

#define OPEN 0
#define CLOSED 1

int groupWordNumber = 0;

void checkIsGroupWord(char word[]) {

	int wordCheck[26] = { OPEN };
	int wordLen = strlen(word);

	for (int i = 0; i < wordLen; i++) {

		int idx = word[i] - 97;
		if (wordCheck[idx] == CLOSED) {
			// 바로 끝. 이건 더이상 그룹 단어가 아니다. 
			return 0;
		}

		if (idx == word[i + 1] - 97) {
			// 문자열에 같은 문자가 나오면 패스
			continue;
		}
		else {
			// 다른 문자가 나오면, wordCheck에 이전 문자를 투입
			wordCheck[idx] = CLOSED;
		}
	}
	groupWordNumber++;
}

int main() {

	int N;
	scanf("%d", &N);
	char wordArr[MAX][MAX];

	for (int i = 0; i < N; i++) {
		scanf("%s", wordArr[i]);
	}

	for (int i = 0; i < N; i++) {
		checkIsGroupWord(wordArr[i]);
	}

	printf("%d", groupWordNumber);

	return 0;
} // 맞았습니다! 