#include <stdio.h>
#pragma warning(disable : 4996)
#pragma warning(disable : 4477)

#define MAX_INDEX 15
#define True 1
#define False 0

typedef char boolean;

int arr[15],
    result, n;

void back(int placed)
{
    if (placed == n)
    {
        result++;
        return;
    }

    for (int i = 0; i < n; i++)
    { // check all vertax
        boolean canPlace = True;
        for (int a = 0; a < placed; a++)
            if (placed - a == i - arr[a] || a - placed == i - arr[a] || i == arr[a])
            { // check whether we can place Queen at position (placed, i)
                canPlace = False;
                break;
            }
        if (canPlace)
        { // backtracking
            arr[placed] = i;
            back(placed + 1);
            arr[placed] = 0;
        }
    }

    return;
}

int main()
{
    scanf("%d", &n);
    back(0);
    printf("%d", result);
    return 0;
}

/*{
    0, 1, 0, 0, 2,
    10, 4, 40, 92, 352, 724,
    2680, 14200, 73712, 365596, 2279184
 }*/