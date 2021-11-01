#include <stdio.h> 
#define _USE_MATH_DEFINES
#include <math.h>
#pragma warning(disable:4996)

int main() {

	int n;
	scanf("%d", &n);

    // M_PI 는 헤더에서 제공하는 정확한 파이값
	printf("%.6f\n%.6f", pow(n, 2)*M_PI, pow(n, 2) * 2);

	return 0;
}
// ez