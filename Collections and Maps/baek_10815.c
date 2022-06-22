/*
https://www.acmicpc.net/problem/10815

문제
숫자 카드는 정수 하나가 적혀져 있는 카드이다. 상근이는 숫자 카드 N개를 가지고 있다. 정수 M개가 주어졌을 때, 이 수가 적혀있는 숫자 카드를 상근이가 가지고 있는지 아닌지를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 상근이가 가지고 있는 숫자 카드의 개수 N(1 ≤ N ≤ 500,000)이 주어진다. 둘째 줄에는 숫자 카드에 적혀있는 정수가 주어진다. 숫자 카드에 적혀있는 수는 -10,000,000보다 크거나 같고, 10,000,000보다 작거나 같다. 두 숫자 카드에 같은 수가 적혀있는 경우는 없다.

셋째 줄에는 M(1 ≤ M ≤ 500,000)이 주어진다. 넷째 줄에는 상근이가 가지고 있는 숫자 카드인지 아닌지를 구해야 할 M개의 정수가 주어지며, 이 수는 공백으로 구분되어져 있다. 이 수도 -10,000,000보다 크거나 같고, 10,000,000보다 작거나 같다

출력
첫째 줄에 입력으로 주어진 M개의 수에 대해서, 각 수가 적힌 숫자 카드를 상근이가 가지고 있으면 1을, 아니면 0을 공백으로 구분해 출력한다.

예제 입력 1
5
6 3 2 10 -10
8
10 9 -5 2 3 4 5 -10
예제 출력 1
1 0 0 1 1 0 0 1

*/

/*
풀이법
sol_1.
Tree를 구현한 후, BinarySearchTree를 통해 검색한다.

sol_2.
20억개의 배열을 구현한 후 countingSort처럼 각 배열의 index가 해당 숫자의 존재 여부를 밝힐 수 있도록 만든다.
*/
#include <stdio.h>

#define MAX 20000001
#define KEY 10000000
#define EXIST 1
#define NOTEXIST 0
int arr[MAX] = {NOTEXIST};

int main()
{
    int NumberOfCard;   // 존재하는카드개수
    int cardNumber;     // 카드 숫자
    int NumberOfSearch; // 찾는카드개수

    scanf("%d", &NumberOfCard);
    for (int i = 0; i < NumberOfCard; i++)
    {
        scanf("%d", &cardNumber);
        arr[cardNumber + KEY] = EXIST;
    }

    scanf("%d", &NumberOfSearch);
    for (int i = 0; i < NumberOfSearch; i++)
    {
        scanf("%d", &cardNumber);
        if (arr[cardNumber + KEY] == EXIST)
        {
            printf("1 ");
        }
        else
        {
            printf("0 ");
        }
    }

    return 0;
} // 맞았습니다!!