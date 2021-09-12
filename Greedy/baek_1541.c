#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*

*/

int main() {

	char First_sentence[55];
	char Last_sentence[55];
	int FrontTotal = 0;
	int BackTotal = 0;

	gets(First_sentence);
	strcpy(Last_sentence, First_sentence);

	// 1.만약 - 가 없을 경우
	if (strchr(First_sentence, '-') == NULL) {
		
		char *FindAllNumbers = strtok(Last_sentence, "+-");

		while (FindAllNumbers != NULL) {
			BackTotal = BackTotal + atoi(FindAllNumbers);

			FindAllNumbers = strtok(NULL, "+-");
		}

		printf("%d", BackTotal);
		return 0;
	}


	// 2. 만약  - 가 있을 경우 
	char *FindFrontMinus = strtok(First_sentence, "-");

	// 처음으로 나오는 -앞에 숫자 찾기 
	char *FindFrontNumbers = strtok(FindFrontMinus, "+");
	while (FindFrontNumbers != NULL) {
		FrontTotal = FrontTotal + atoi(FindFrontNumbers);

		FindFrontNumbers = strtok(NULL, "+");
	}

	// 전체 숫자 찾기
	char *FindAllNumbers = strtok(Last_sentence, "+-");

	while (FindAllNumbers != NULL) {
		BackTotal = BackTotal + atoi(FindAllNumbers);

		FindAllNumbers = strtok(NULL, "+-");
	}

	printf("%d", FrontTotal * 2 - BackTotal);

	return 0;
} // 맞았습니다!!