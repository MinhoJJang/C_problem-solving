#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 


#define NeverBeLowestNumber 1001

int FindLowestTime(int people, int time[], int lowest_time, int WaitingPeople, int totaltime) {

	while (WaitingPeople != 0) {
		int idx = 0;
		lowest_time = time[idx];

		for (int i = 0; i < people - 1; i++) {
			if (lowest_time > time[i + 1]) {
				lowest_time = time[i + 1];
				idx = i + 1;
			}
		}

		time[idx] = NeverBeLowestNumber;

		totaltime = totaltime + (WaitingPeople * lowest_time);
		WaitingPeople--;
	}

	return totaltime;
}

int main() {

	int people;
	int time[1005] = { 0 };
	int lowest_time = 0;
	int totaltime = 0;

	scanf("%d", &people);
	int Waitingpeople = people;

	for (int i = 0; i < people; i++) {
		scanf("%d", &time[i]);
	}

	printf("%d", FindLowestTime(people, time, lowest_time, Waitingpeople, totaltime));
	
	return 0;
} // 맞았습니다!