#include <stdio.h> 
#pragma warning(disable:4996) 

int abs(int a, int b) {
	// a<b;

	int diff = b-a;
	if (diff < a) {
		return diff;
	}
	return a;
}

int main() {

	int x, y, w, h;

	scanf("%d%d%d%d", &x, &y, &w, &h);

	int a = abs(y, h);
	int b = abs(x, w);
	
	if (a < b) {
		printf("%d", a);
	}
	else {
		printf("%d", b);
	}

	return 0;
} // ez