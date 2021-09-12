#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

/*

*/

int main() {

	int CoinTypes;
	int MaxNumber;
	int CoinValue[10] = { 0 };
	int Type;
	int TotalCoinNumber = 0;

	scanf("%d %d", &CoinTypes, &MaxNumber);
	for (Type = 0; Type < CoinTypes; Type++) {
		scanf("%d", &CoinValue[Type]);
	}
	Type--;

	while (Type >= 0) {
		int Coins = MaxNumber / CoinValue[Type];

		TotalCoinNumber = TotalCoinNumber + Coins;
		MaxNumber = MaxNumber - (Coins*CoinValue[Type]);

		if (MaxNumber == 0) {
			printf("%d", TotalCoinNumber);
			return 0;
		}
		Type--;
	}

} // 맞았습니다 