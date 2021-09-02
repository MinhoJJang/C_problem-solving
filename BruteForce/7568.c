#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

// https://www.acmicpc.net/problem/7568

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
