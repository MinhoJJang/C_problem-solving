#include <stdio.h>
#pragma warning (disable:4996)
/*
arr[30] 이렇게 만들어서 arr[i] = i 가 되도록 만든 다음, 입력받은 숫자를 보고 구해보자.
*/

#define MAX 31
#define TESTCASE 10000

int num[MAX] = { 0 };

// 이항계수 : binomial coefficient
// 이항계수 값을 저장한다. 
int bionomialCoefficient[MAX][MAX] = { 0 };

int testCase;
int low[TESTCASE];
int high[TESTCASE];

void putData() {

	scanf("%d", &testCase);
	for (int i = 0; i < testCase; i++) {
		scanf("%d%d", &low[i], &high[i]);
	}

	/*    for(int n=1; n<=high; n++){
		   num[n] = n;
	   } */
}

// 10C2 or 10C6 같은 경우, 2와 8을 비교하고 2를 가져온다. 10C6의 경우 4.
int returnSmall(int a, int b) {
	// a<b
	int diff = b - a;
	if (a < diff) {
		return a;
	}
	return diff;
}

// numerator 분모
// denominator 분자 

int mainLogic(int a, int b) {

	if (bionomialCoefficient[a][b] == 0) {
		int NumberofNum = returnSmall(a, b);
		int denominator[MAX] = { 0 }; // 분자 
		int numerator[MAX] = { 0 }; // 분모 

		int CurrentNumerotor = NumberofNum; // 현재 분모 숫자 
		int CurrentDenominator = b; // 현재 분자 숫자
		// 배열에 분모 분자의 숫자들을 넣어준다. 10C3이라고 한다면
		// 분자에 10, 9, 8 넣고
		// 분모에 3, 2, 1 넣고.. 
		while (CurrentNumerotor > 0) {
			// 분자 
			denominator[CurrentDenominator] = CurrentDenominator;
			// 분모
			numerator[CurrentNumerotor] = CurrentNumerotor;

			CurrentDenominator--;
			CurrentNumerotor--;
		}

		
		for (int numeIdx = NumberofNum; numeIdx > 1; numeIdx--) {
			for (int denoIdx = b; denoIdx > b - NumberofNum; denoIdx--) {
				if (denominator[denoIdx] % numerator[numeIdx] == 0) {
					denominator[denoIdx] /= numerator[numeIdx];
					numerator[numeIdx] = 1;
					break;
				}
			}
		}

		int denoMultifly = 1;
		int numeMultifly = 1;

		for (int denoIdx = b; denoIdx > b - NumberofNum; denoIdx--) {
			denoMultifly *= denominator[denoIdx];
		}
		for (int numeIdx = NumberofNum; numeIdx > 0; numeIdx--) {
			numeMultifly *= numerator[numeIdx];
		}

		bionomialCoefficient[a][b] = denoMultifly / numeMultifly;
		bionomialCoefficient[b - a][b] = denoMultifly / numeMultifly;
	}

	return bionomialCoefficient[a][b];
}

void mainFunction() {
	for (int i = 0; i < testCase; i++) {
		printf("%d\n", mainLogic(low[i], high[i]));
	}
}

int main() {

	putData();
	mainFunction();

	return 0;
}
// 맞았습니다! 