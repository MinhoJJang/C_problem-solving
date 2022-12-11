#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)
#pragma warning(disable : 4477)
#define MAX_LENGTH 10005
#define SIZE 2750

char fibo[MAX_LENGTH][SIZE];

// 수를 특정한 배열에 담는다. 이때 이차원 배열로 0번째 피보나치 수는 arr[0]에 담고, 1번째 수는 arr[1]에 담고...이런식으로..!
int sizeArr(int N)
{

	if (N == 0)
	{
		return 0;
	}

	int cnt = 0;
	int i = 0;

	if (N == 200)
	{
	}

	while (fibo[N][i] != '\0')
	{
		i++;
		cnt++;
	}

	return cnt - 1;
}

char fn(int N, int FirstN)
{

	char isTen[SIZE][1] = {0};

	if (N == 0)
	{
		fibo[N][0] = '0';
	}
	else if (N == 1)
	{
		fibo[N][0] = '1';
	}
	else
	{

		int lengthCount = 0;

		// 더하려는 문자열의 길이파악.
		int lengthOfArr1 = sizeArr(N - 1);
		int lengthOfArr2 = sizeArr(N - 2);
		// Arr1 >= Arr2
		int save = lengthOfArr1;

		// 길이가 더 긴 배열의 0번째를 참조하고 난 뒤에는 더할 수 없음
		// 하지만 만약 5+8 = 13이런 경우라면..?
		while (lengthOfArr1 >= 0)
		{

			int check = 0;

			if (lengthOfArr2 >= 0)
			{

				check = fibo[N - 1][lengthOfArr1] + fibo[N - 2][lengthOfArr2] + isTen[lengthCount][0] - '0' - '0';
			}
			else
			{
				check = fibo[N - 1][lengthOfArr1] + isTen[lengthCount][0] - '0';
			}

			if (isTen[lengthCount][0] == '1')
			{
				check -= '0';
			}

			// 더한 값이 10을 넘지 않으면
			if (check < 10)
			{
				fibo[N][lengthOfArr1 + 1] = check + '0';
			}
			// 10을 넘으면
			else
			{
				// 만약 자리수가 같았는데 더했을 떄 총 자리수가 늘어나면...?
				isTen[lengthCount + 1][0] = '1'; // 다음 숫자 10의자리수 올려주고
				fibo[N][lengthOfArr1 + 1] = check - 10 + '0';
			}

			lengthOfArr1--;
			lengthOfArr2--;

			lengthCount++;
		}

		// 더한 숫자의 자리수가 같고, 답안의 자리수가 1 늘어났다면
		if (lengthOfArr1 == -1 && isTen[lengthCount][0] == '1')
		{
			fibo[N][0] = '1';
		}
		// 만약 전부 더한 값이 자리수가 변하지 않았다면
		else
		{
			int k = 0;
			while (k <= save)
			{
				fibo[N][k] = fibo[N][k + 1];
				k++;
			}
			fibo[N][k] = '\0';
		}
	}

	if (N == FirstN)
	{
		return 0;
	}

	return fn(N + 1, FirstN);
}

int main()
{

	int N;

	scanf("%d", &N);
	fn(0, N);

	int i = 0;
	while (fibo[N][i] != 0)
	{
		printf("%c", fibo[N][i]);
		i++;
	}

	return 0;
}
// 200초과에서 랜덤하게 죽는데 왜 죽을까
// 아니 백준 컴파일러에서는 되는데 ??????????ㅋㅋㅋ아