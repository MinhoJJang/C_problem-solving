#include <stdio.h> //표준 입출력헤더 
#pragma warning(disable:4996) //scanf()등 ANSI C함수 에러 메세지 무시

//문제 https://www.acmicpc.net/problem/1193

/*					위
		1   2   6   7   15
		3   5   8   14
	    4   9   13
아래	10 12
		11
대각선 모양으로 읽자 

X번째 수.. 1+2+...+n<=X< 1+2+...+(n+1)
X에서 수를 빼면서 n값 찾기 
*/

int main() {

	int X;
	int count = 0;
	//printf("숫자를 입력하세요");
	scanf("%d", &X);

	int sum = 0;
	int n;

	for (n = 1; ; n++) //무한루프
	{
		sum += n; //n을 1부터 계속 더한 것을 sum
		if (X - sum > 0) //입력받은 값 X에서 sum을 빼어 양수일경우
		{
			count++; //count를 0에서 1만큼 올려준다 
		}
		else if (X - sum <= 0) //입력받은 값 X에서 sum을 빼어 음수이거나 0일경우
		{
			break; 
			//함수종료
			//뺀 값이 처음으로 0이하 정수가 되었으므로 break된 순간의 n값은
			//1+2+...+(n-1)<= X < 1+2+...+n 을 만족함 
		}
	}
	//printf("%d\n", count); //1부터 n까지 정수 개수. 몇번째 줄인지 알려줌.
	//printf("%d\n", X - (sum - n)); //그 줄에서 위에서부터 몇번째 수인가?
	int diff = X - (sum - n); 

	//n이 홀수면 아래에서 위로 , 짝수면 위에서 아래로 
	if (n % 2 == 0) {
		printf("%d/%d", diff, count + 2 - diff);
	}
	else {
		printf("%d/%d", count+2-diff, diff);
	}

	return 0;
} //맞았습니다!