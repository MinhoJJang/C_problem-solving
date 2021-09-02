#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*

몸무게
C - D - B - A - E
1 - 2 - 3 - 4 - 5
키
C - A - B - D - E
1 - 2 - 3 - 4 - 5

가장 몸무게가 큰 값을 가진 배열 인덱스에 임의의 등수 1을 넣어주고 ,
A는 A끼리 더해서 합을 배열에 다시 넣고, 최솟값을 찾아서 그거부터 다시 등수를 넣는다. 
*/

int FindBigWeight(int NumberOfPeople, int weight[]) {

	// 몸무게를 배열에 큰 순서대로 저장하고, 그 사람의 번호도 마찬가지로 2차원 배열에 넣는다.

	// 아니지, 브루트포스니까 무식하게 비교하는건가????

	// 












}

int FindBigHeight();

int main() {

	int NumberofPeople;
	int weight[55] = { 0 };
	int height[55] = { 0 };
	int MostHeavyWeight = 0;
	int MostTallHeight = 0;
	int index = 0;
	
	int Answer[55] = { 0 };

	scanf("%d", &NumberofPeople);

	for (index = 0; index < NumberofPeople; index++) {
		scanf("%d %d", &weight[index], &height[index]);
	}

	for (index = 0; index < NumberofPeople; index++) {

		MostHeavyWeight = weight[index];
		MostTallHeight = height[index];

		int CountBiggerPersonThanMe = 0;

		for (int CompareIndex = 0; CompareIndex < NumberofPeople; CompareIndex++) {
			if (MostHeavyWeight < weight[CompareIndex] && MostTallHeight < height[CompareIndex]) {
				CountBiggerPersonThanMe++;
			}
		}

		Answer[index] = CountBiggerPersonThanMe + 1;
		
	}

	for (int i = 0; i < NumberofPeople; i++) {
		printf("%d ", Answer[i]);
	}

	return 0;
}