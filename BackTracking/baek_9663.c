/*
    ============================================================
    Algorithm 14465001 Term project
    202033762 장민호

    algorithm: Backtracking
    solved: https://www.acmicpc.net/problem/9663 (N_Queen)
    why do I take it? : N-Queen is a very symbolical problem of backtracking, so I want to solve it.

    what is backtracking?
        해를 찾는 도중 해가 아니어서 막히면, 되돌아가서 다시 해를 찾아가는 기법이다. 즉, 특정한 조건을 만족시킬 경우만 살펴보는 기법으로, 해가 될 것 같지 않은 노드는 조사하지 않기 때문에 불필요한 조사 작업이 필요 없어 효율적인 검색을 할 수 있다.

    Original? Extension?
        처음에는 0부터 n까지 모든 노드에 대해 조사했는데, 조사하다 보니 N-Queen문제는 나오는 답이 대칭적이라는 사실을 알게 되었다.

    ============================================================
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int queenLocation[15];  // 배치된 퀸의 위치를 저장하는 배열
int placementCompleted; // 배치완료된 퀸 세트 개수
int arr[15];            // 첫번째 줄에 위치한 퀸에 따라 배치가능한 세트 개수
int QueenToBePlaced;    // 배치해야 하는 퀸 개수

void N_Queen_original(int placedQueenNumber) // 배치된 퀸 숫자를 인자로 받는다
{
    if (placedQueenNumber == QueenToBePlaced) // 전부 퀸을 배치한 상태
    {
        // original
        placementCompleted++; // 결과값 + 1
        arr[queenLocation[0]]++;
        return;
    }

    for (int newQueen_x = 0; newQueen_x < QueenToBePlaced; newQueen_x++) // 새로 위치시킬 퀸의 x좌표를 0부터 최대 퀸 개수만큼 검사한다.
    {
        bool canBePlaced = true;            // 일단 배치 가능하다고 생각하고, 배치 후  기존에 배치된 퀸들과 서로 만나지 않는지 체크한다.
        int newQueen_y = placedQueenNumber; // 새로 배치하는 퀸의 y좌표는, 현재까지 놓인 퀸의 개수와 같다. ex) 퀸이 2개 놓였다면, 그다음 퀸의 좌표는 (newQueen_x, 2) 일 것이다.

        for (int idx = 0; idx < newQueen_y; idx++) // 기존에 배치된 퀸 개수는 placedQueenNumber이므로, 배치된 퀸들과 배치한 퀸이 서로 만나지 않는지 체크한다.
        {

            if (newQueen_y - idx == abs(newQueen_x - queenLocation[idx]) || newQueen_x == queenLocation[idx])
            /*
                이미 배치된 퀸과 만나는 경우는 3가지가 있다.
                1. 대각선 왼쪽 길
                2. 직선 아래 길
                3. 대각선 오른쪽 길

                ex)
                마치 보드판이 x,y 좌표평면의 4사분면 위에 있는 것처럼 생각한다. 다만 y를 먼저 배치한다. (y,x) > 이유는 첫째 줄부터 채우기 때문이다.
                    ->
                ㅣ  _ O _ _
                    _ _ _ O
                    _ _ _ _
                    _ _ _ _
                새로 들어올 수 있는 퀸(N) 위치 : (2, 0)

                이미 배치된 퀸의 위치는 (idx, queenLocation[idx]) 이다.
                배치할 퀸의 위치는 (newQueen_y, newQueen_x) 이다.

                대각선에 닿는지 조사하려면 몇 칸 띄워져 있는지도 알아야 한다. y축 상 떨어져 있는 거리는 반드시 newQueen_y - idx 일 것이고, x축 상 떨어져 있는 거리는 queenLocation[idx] - newQueen_x(대각선 왼쪽) 혹은 newQueen_x - queenLocation[idx](대각선 오른쪽) 일 것이다.

                그 y축이 떨어져 있는 거리가 x축에서 떨어져 있는 거리와 같아서는 안된다. 즉, 저 두 값이 같다면 false 이다.

                또한 직선 아래 위치할 경우 그냥 x축 값이 같은지, newQueen_x - queenLocation[idx] == 0 인지 알아보면 된다.
            */
            {
                canBePlaced = false;
                break; // 퀸 중 하나라도 범위가 겹치면 그 뒤는 더이상 조사할 필요가 없다. 바로 break로 필요없는 코드 동작을 줄인다.
            }
        }

        if (canBePlaced) // 만약 이미 배치된 퀸들과 범위가 겹치지 않는다면, 유망한 곳이라고 볼 수 있다.
        {
            queenLocation[placedQueenNumber] = newQueen_x; // 새로 배치한 퀸의 위치를 등록한다.
            N_Queen_original(placedQueenNumber + 1);       // 그다음 퀸을 배치하러 가보자
            queenLocation[placedQueenNumber] = 0;          // 새로 배치한 퀸에 대해 N_Queen에서 모든 가능성을 조사했으므로, 다음 배치를 위해 0으로 초기화해준다.
        }
    }

    return;
}

void N_Queen_extension(int placedQueenNumber) // 배치된 퀸 숫자를 인자로 받는다
{
    if (placedQueenNumber == QueenToBePlaced) // 전부 퀸을 배치한 상태
    {
        // extension
        // arr[queenLocation[0]]++;
        return;
    }

    for (int newQueen_x = 0; newQueen_x < QueenToBePlaced; newQueen_x++) // 새로 위치시킬 퀸의 x좌표를 0부터 최대 퀸 개수만큼 검사한다.
    {
        // extension
        // 배치할 수 있는 퀸의 개수는 대칭적이다. 따라서 중간까지만 구하고 나머지는 안구해도 된다.
        if (queenLocation[0] >= QueenToBePlaced / 2.0)
        {
            return;
        }

        bool canBePlaced = true;            // 일단 배치 가능하다고 생각하고, 배치 후  기존에 배치된 퀸들과 서로 만나지 않는지 체크한다.
        int newQueen_y = placedQueenNumber; // 새로 배치하는 퀸의 y좌표는, 현재까지 놓인 퀸의 개수와 같다. ex) 퀸이 2개 놓였다면, 그다음 퀸의 좌표는 (newQueen_x, 2) 일 것이다.

        for (int idx = 0; idx < newQueen_y; idx++) // 기존에 배치된 퀸 개수는 placedQueenNumber이므로, 배치된 퀸들과 배치한 퀸이 서로 만나지 않는지 체크한다.
        {

            if (newQueen_y - idx == abs(newQueen_x - queenLocation[idx]) || newQueen_x == queenLocation[idx])
            /*
                이미 배치된 퀸과 만나는 경우는 3가지가 있다.
                1. 대각선 왼쪽 길
                2. 직선 아래 길
                3. 대각선 오른쪽 길

                ex)
                마치 보드판이 x,y 좌표평면의 4사분면 위에 있는 것처럼 생각한다. 다만 y를 먼저 배치한다. (y,x) > 이유는 첫째 줄부터 채우기 때문이다.
                    _ O _ _
                    _ _ _ O
                    N _ _ _
                    _ _ _ _
                새로 들어올 수 있는 퀸(N) 위치 : (2, 0)


                이미 배치된 퀸의 위치는 (idx, queenLocation[idx]) 이다.
                배치할 퀸의 위치는 (newQueen_y, newQueen_x) 이다.

                대각선에 닿는지 조사하려면 몇 칸 띄워져 있는지도 알아야 한다. y축 상 떨어져 있는 거리는 반드시 newQueen_y - idx 일 것이고, x축 상 떨어져 있는 거리는 queenLocation[idx] - newQueen_x(대각선 왼쪽) 혹은 newQueen_x - queenLocation[idx](대각선 오른쪽) 일 것이다.

                그 y축이 떨어져 있는 거리가 x축에서 떨어져 있는 거리와 같아서는 안된다. 즉, 저 두 값이 같다면 false 이다.

                또한 직선 아래 위치할 경우 그냥 x축 값이 같은지, newQueen_x - queenLocation[idx] == 0 인지 알아보면 된다.
            */
            {
                canBePlaced = false;
                break; // 퀸 중 하나라도 범위가 겹치면 그 뒤는 더이상 조사할 필요가 없다. 바로 break로 필요없는 코드 동작을 줄인다.
            }
        }

        if (canBePlaced) // 만약 이미 배치된 퀸들과 범위가 겹치지 않는다면, 유망한 곳이라고 볼 수 있다.
        {
            queenLocation[placedQueenNumber] = newQueen_x; // 새로 배치한 퀸의 위치를 등록한다.
            N_Queen_extension(placedQueenNumber + 1);      // 그다음 퀸을 배치하러 가보자
            queenLocation[placedQueenNumber] = 0;          // 새로 배치한 퀸에 대해 N_Queen에서 모든 가능성을 조사했으므로, 다음 배치를 위해 0으로 초기화해준다.
        }
    }

    return;
}

void printArr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
}

int getAnswer(int arr[], int n)
{
    int i = 0;
    int answer = 0;
    if (n % 2 == 0)
    {
        while (arr[i] != 0)
        {
            answer += 2 * arr[i++];
        }
    }
    else
    {
        while (arr[i] != 0)
        {
            answer += 2 * arr[i++];
        }
        answer -= arr[i - 1];
    }

    return answer;
}

int main()
{
    scanf("%d", &QueenToBePlaced);

    printf("===============Original Start=================\n");

    // 시간 최적화 비교 시작
    clock_t start, end;
    start = clock(); // 시작, 현재시간 측정

    N_Queen_original(0);

    end = clock();

    long result = end - start;
    printf("%ld ms\n", result / 1000);

    // original
    printf("%d\n", placementCompleted);

    printf("===============Original End=================\n");
    // 시간 최적화 비교 종료

    printf("\n");

    printf("===============Extension Start=================\n");

    // 시간 최적화 비교 시작
    start = clock(); // 시작, 현재시간 측정

    N_Queen_extension(0);

    end = clock();

    result = end - start;
    printf("%ld ms\n", result / 1000);

    // original
    printf("%d\n", placementCompleted);

    printf("===============Extension End=================\n");
    // 시간 최적화 비교 종료

    printf("\n");

    printf("===============PrintArr Start=================\n");

    printArr(arr, QueenToBePlaced);

    printf("===============PrintArr End=================\n");

    return 0;
}

/*{
    0, 1, 0, 0, 2,
    10, 4, 40, 92, 352, 724,
    2680, 14200, 73712, 365596, 2279184
 }*/