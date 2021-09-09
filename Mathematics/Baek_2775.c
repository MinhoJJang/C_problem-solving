#include <stdio.h> //표준 입출력헤더 
#pragma warning(disable:4996) //scanf()등 ANSI C함수 에러 메세지 무시

/*
https://www.acmicpc.net/problem/2775

평소 반상회에 참석하는 것을 좋아하는 주희는 이번 기회에 부녀회장이 되고 싶어 각 층의 사람들을 불러 모아 반상회를 주최하려고 한다.

이 아파트에 거주를 하려면 조건이 있는데, “a층의 b호에 살려면 자신의 아래(a-1)층의 1호부터 b호까지 사람들의 수의 합만큼 사람들을 데려와 살아야 한다” 는 계약 조항을 꼭 지키고 들어와야 한다.

아파트에 비어있는 집은 없고 모든 거주민들이 이 계약 조건을 지키고 왔다고 가정했을 때, 주어지는 양의 정수 k와 n에 대해 k층에 n호에는 몇 명이 살고 있는지 출력하라. 단, 아파트에는 0층부터 있고 각층에는 1호부터 있으며, 0층의 i호에는 i명이 산다.

첫 번째 줄에 Test case의 수 T가 주어진다. 그리고 각각의 케이스마다 입력으로 첫 번째 줄에 정수 k, 두 번째 줄에 정수 n이 주어진다

각각의 Test case에 대해서 해당 집에 거주민 수를 출력하라.
*/

int main() {

	int k, n, p, i, j; //k는 층수, n은 호수
					      //1 ≤ k, n ≤ 14
	int Test, t;
	int apt[15][14] = { 0 };
	int ans[210] = { 0 };

	scanf("%d", &Test); //Testcase의 수를 받는다.

	//apt[15][14] 배열에서 각각의 값을 찾아주는 조건문
	for (j = 0; j < 14; j++) {
		for (p = 0; p < 14; p++) {
			for (i = 0; i <= p; i++) {
				apt[0][i] = i+1;
				apt[j + 1][p] += apt[j][i];
			}
		}
	}
	
	//Testcase 수만큼 k,n 세트를 받고 ans[t]에 Testcase 수만큼 답을 저장한다.
	for (t = 0; t < Test; t++) {
		
		scanf("%d", &k);
		scanf("%d", &n);

		ans[t] = apt[k][n-1];
		k = 0;
		n = 0;
	}

	//저장한 답을 제출한다. 
	for (t = 0; t < Test; t++) {
		printf("%d\n", ans[t]);
	}

	return 0;
} //맞았습니다!!