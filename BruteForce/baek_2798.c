#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*https://www.acmicpc.net/problem/2798
김정인 버전의 블랙잭에서 각 카드에는 양의 정수가 쓰여 있다. 그 다음, 딜러는 N장의 카드를 모두 숫자가 보이도록 바닥에 놓는다. 그런 후에 딜러는 숫자 M을 크게 외친다.

이제 플레이어는 제한된 시간 안에 N장의 카드 중에서 3장의 카드를 골라야 한다. 블랙잭 변형 게임이기 때문에, 플레이어가 고른 카드의 합은 M을 넘지 않으면서 M과 최대한 가깝게 만들어야 한다.

N장의 카드에 써져 있는 숫자가 주어졌을 때, M을 넘지 않으면서 M에 최대한 가까운 카드 3장의 합을 구해 출력하시오.
*/

#define MAXNUMBER_CARD	105
#define MAX_ABLE_NUMBEROFSUM 200000
#define FIND_ANSWER 0


int main() {

	int numberofCards;
	int sumYouWant;

	int numberWrittenOnCard[MAXNUMBER_CARD];

	scanf("%d %d", &numberofCards, &sumYouWant);

	for (int i = 0; i < numberofCards; i++) {
		scanf("%d", &numberWrittenOnCard[i]);
	}

	int first;
	int second; 
	int third;

	// 0 1 2 3 4 5

	int sumStorage[MAX_ABLE_NUMBEROFSUM] = { 0 };
	int minimumDifference = sumYouWant;
	int differenceInNumbers;

	int idx = 0;
	int i = 0;

	for (first = numberWrittenOnCard[i]; i < numberofCards - 2; i++) {
		
		int j = i + 1;

		for (second = numberWrittenOnCard[j]; j < numberofCards - 1; j++) {

			int k = j + 1;

			for (third = numberWrittenOnCard[k]; k < numberofCards; k++) {

				sumStorage[idx] = numberWrittenOnCard[i]+ numberWrittenOnCard[j]+ numberWrittenOnCard[k];
				differenceInNumbers = sumYouWant - sumStorage[idx];

				if (differenceInNumbers == 0) {
					printf("%d", sumYouWant - differenceInNumbers);
					return FIND_ANSWER;
				}
				else if (minimumDifference > differenceInNumbers && differenceInNumbers >= 0) {
					minimumDifference = differenceInNumbers;
				}

				idx++;
			}
		}
	}

	printf("%d", sumYouWant - minimumDifference);

	return 0;
}