#include <stdio.h> //표준 입출력헤더 
#pragma warning(disable:4996) //scanf()등 ANSI C함수 에러 메세지 무시


/*
땅 위에 달팽이가 있다. 이 달팽이는 높이가 V미터인 나무 막대를 올라갈 것이다.

달팽이는 낮에 A미터 올라갈 수 있다. 하지만, 밤에 잠을 자는 동안 B미터 미끄러진다. 또, 정상에 올라간 후에는 미끄러지지 않는다.

달팽이가 나무 막대를 모두 올라가려면, 며칠이 걸리는지 구하는 프로그램을 작성하시오.
*/

int main() {
	
	int a, b, v;
	scanf("%d%d%d", &a, &b, &v);
	getchar();

	int h = v - a; //목표 높이-낮에 올라가는 높이
	int d = a - b; //하루에 올라가는 총 높이 

	if (h % d == 0) {
		printf("%d", (h/d)+1); 
	}
	else {  
		printf("%d", (h / d) + 2); //소숫점아래 자동 버려짐
	}

	getchar();
	return 0;
} //end main() //맞았습니다!!