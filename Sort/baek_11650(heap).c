/*
https://www.acmicpc.net/problem/11650
2차원 평면 위의 점 N개가 주어진다. 좌표를 x좌표가 증가하는 순으로, x좌표가 같으면 y좌표가 증가하는 순서로 정렬한 다음 출력하는 프로그램을 작성하시오.

첫째 줄에 점의 개수 N (1 ≤ N ≤ 100,000)이 주어진다. 둘째 줄부터 N개의 줄에는 i번점의 위치 xi와 yi가 주어진다. (-100,000 ≤ xi, yi ≤ 100,000) 좌표는 항상 정수이고, 위치가 같은 두 점은 없다.

첫째 줄부터 N개의 줄에 점을 정렬한 결과를 출력한다.
*/

// 미완성

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define X 0
#define Y 1
#define MAX 100005

/*
구조체 타입의 배열선언 후 배열을 정렬하는 키를 바꾸는 문제
*/
typedef int dataType;

typedef struct _coordinate
{
    int x;
    int y;
} cord;

cord inputArr[MAX] = {0};

// ============HEAPSORT============
#define SUCCESS 1
#define FAIL 0
#define ROOTIDX 1

#define GET_PARENT_IDX(idx) ((idx) >> 1)
#define GET_LEFT_IDX(idx) ((idx) << 1)
#define GET_RIGHT_IDX(idx) (((idx) << 1) + 1)

#define COMP_ASC(d1, d2) ((d2) - (d1))
#define COMP_DESC(d1, d2) ((d1) - (d2))

typedef int fnPriorityComp(dataType d1, dataType d2);

typedef struct _heap
{
    int numData;
    dataType *heapArr;
    fnPriorityComp *comp;
} Heap;
Heap *g_hp;

// return the highest priority child's index
int getHighPriority(Heap *ph, int idx)
{
    if (GET_LEFT_IDX(idx) > ph->numData)
    {
        return 0;
    }

    if (GET_LEFT_IDX(idx) == ph->numData)
    {
        return GET_LEFT_IDX(idx);
    }

    if (COMP_ASC(ph->heapArr[GET_LEFT_IDX(idx)], ph->heapArr[GET_RIGHT_IDX(idx)]) < 0)
    {
        idx = GET_RIGHT_IDX(idx);
    }
    else
    {
        idx = GET_LEFT_IDX(idx);
    }

    return idx;
}

void heap_init(Heap *ph, int len)
{
    ph->numData = 0;
    ph->heapArr = (dataType *)malloc(sizeof(dataType) * (len + 1)); // 1-based array
    g_hp = ph;
}

void heap_destroy(Heap *ph)
{
    free(ph->heapArr);
    memset(ph, 0, sizeof(Heap));
}

int heap_is_empty(Heap *ph)
{
    if (ph->numData == 0)
        return SUCCESS;
    return FAIL;
}

void heap_insert(Heap *ph, dataType data)
{
    int idx = ph->numData + 1;

    while (idx != 1)
    {
        if (COMP_ASC(data, ph->heapArr[GET_PARENT_IDX(idx)]) > 0)
        {
            ph->heapArr[idx] = ph->heapArr[GET_PARENT_IDX(idx)];
            idx = GET_PARENT_IDX(idx);
        }
        else
        {
            break;
        }
    }

    ph->heapArr[idx] = data;
    ph->numData++;
}

dataType heap_delete(Heap *ph)
{

    dataType rootData = ph->heapArr[ROOTIDX];
    dataType lastElem = ph->heapArr[ph->numData];

    int idx = ROOTIDX;
    int childIdx;

    while (childIdx = getHighPriority(ph, idx))
    {
        if (COMP_ASC(lastElem, ph->heapArr[childIdx]) >= 0)
        {
            break;
        }
        ph->heapArr[idx] = ph->heapArr[childIdx];
        idx = childIdx;
    }

    ph->heapArr[idx] = lastElem;
    ph->numData--;

    return rootData;
}

void HeapSort(dataType arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        heap_insert(g_hp, arr[i]);
    }
    for (i = 0; i < n; i++)
    {
        arr[i] = heap_delete(g_hp);
    }
}

int main()
{

    Heap hp;
    heap_init(&hp, 10000);

    heap_destroy(&hp);

    return 0;
}