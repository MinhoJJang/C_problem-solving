#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996) 
#pragma warning(disable:4477) 
#define YES 1
#define NO 0

/*
�ڿ��� N�� M�� �־����� ��, �Ʒ� ������ �����ϴ� ���̰� M�� ������ ��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

1���� N���� �ڿ��� �߿��� �ߺ� ���� M���� ���� ����
*/
void printarr(int arr[], int len) {

	int idx = 0;

	while (idx != len) {
		printf("%d ", arr[idx]);
		idx++;
	}

	printf("\n");
}

int IsDuplicate(int arr[], int len) {

	for (int idx = len - 1; idx >= 0; idx--) {
		int dup = arr[idx];
		for (int i = idx - 1; i >= 0; i--) {
			if (dup == arr[i]) {
				return YES;
			}
		}
	}
	return NO;
}

void fn(int NumberofNum, int len) {
	
	int select[8]; 
	int num = 0;

	while (num != len) {
		select[num] = num + 1;
		num++;
	}

	// sel �迭�� index 0���� M-1���� ���ڰ� ������� ��
	// M-1�������� 1�� ���ϱ� �����ؼ�, 1 ���� ���ڰ� NumberofNum���� ũ��  �����ڸ��� �ø��� 
	int idx = len - 1;

	while (select[0] != NumberofNum+1) {

		// �ִ���ں��� Ŭ���
		if (select[idx] > NumberofNum) {
			for (int i = idx; i >= 1; i--) {

				select[i] = 1;
				select[i - 1]++;

				if (select[i - 1] > NumberofNum) {
					continue;
				}
				else {
					break;
				}
			}
		}

		// �ִ���ں��ٴ� ������, �ߺ��ΰ� �ƴѰ�? 
		else {
			if (IsDuplicate(select, len) == NO) {
				printarr(select, len);								
			}
			select[idx]++;
		}
	}
}

int main() {

	int N = 0;
	int M = 0;

	scanf("%d%d", &N, &M);

	fn(N, M);

	return 0;
} // �¾ҽ��ϴ�!! 