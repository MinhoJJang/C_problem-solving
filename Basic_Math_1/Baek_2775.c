#include <stdio.h> //ǥ�� �������� 
#pragma warning(disable:4996) //scanf()�� ANSI C�Լ� ���� �޼��� ����

/*
https://www.acmicpc.net/problem/2775

��� �ݻ�ȸ�� �����ϴ� ���� �����ϴ� ����� �̹� ��ȸ�� �γ�ȸ���� �ǰ� �;� �� ���� ������� �ҷ� ��� �ݻ�ȸ�� �����Ϸ��� �Ѵ�.

�� ����Ʈ�� ���ָ� �Ϸ��� ������ �ִµ�, ��a���� bȣ�� ����� �ڽ��� �Ʒ�(a-1)���� 1ȣ���� bȣ���� ������� ���� �ո�ŭ ������� ������ ��ƾ� �Ѵ١� �� ��� ������ �� ��Ű�� ���;� �Ѵ�.

����Ʈ�� ����ִ� ���� ���� ��� ���ֹε��� �� ��� ������ ��Ű�� �Դٰ� �������� ��, �־����� ���� ���� k�� n�� ���� k���� nȣ���� �� ���� ��� �ִ��� ����϶�. ��, ����Ʈ���� 0������ �ְ� �������� 1ȣ���� ������, 0���� iȣ���� i���� ���.

ù ��° �ٿ� Test case�� �� T�� �־�����. �׸��� ������ ���̽����� �Է����� ù ��° �ٿ� ���� k, �� ��° �ٿ� ���� n�� �־�����

������ Test case�� ���ؼ� �ش� ���� ���ֹ� ���� ����϶�.
*/

int main() {

	int k, n, p, i, j; //k�� ����, n�� ȣ��
					      //1 �� k, n �� 14
	int Test, t;
	int apt[15][14] = { 0 };
	int ans[210] = { 0 };

	scanf("%d", &Test); //Testcase�� ���� �޴´�.

	//apt[15][14] �迭���� ������ ���� ã���ִ� ���ǹ�
	for (j = 0; j < 14; j++) {
		for (p = 0; p < 14; p++) {
			for (i = 0; i <= p; i++) {
				apt[0][i] = i+1;
				apt[j + 1][p] += apt[j][i];
			}
		}
	}
	
	//Testcase ����ŭ k,n ��Ʈ�� �ް� ans[t]�� Testcase ����ŭ ���� �����Ѵ�.
	for (t = 0; t < Test; t++) {
		
		scanf("%d", &k);
		scanf("%d", &n);

		ans[t] = apt[k][n-1];
		k = 0;
		n = 0;
	}

	//������ ���� �����Ѵ�. 
	for (t = 0; t < Test; t++) {
		printf("%d\n", ans[t]);
	}

	return 0;
} //�¾ҽ��ϴ�!!