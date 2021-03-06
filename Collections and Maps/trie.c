/*
trie를 만들자. 영단어 모음을 저장하는 trie를 만들자.

영단어는 26개의 알파벳으로 구성되어 있으므로, trie의 root는 26개의 알파벳으로 이루어진다.

즉, 어떤 알파벳인지 표시하는 부분과, 다음 node로 확장할 수 있는 포인터 공간, 그리고 데이터를 저장할 수 있는 공간 세가지가 있어야 한다.

a = 97
b = 98
...
z = 122

이걸 배열에서 표현하기 위해서 a = 0, z = 25 이렇게 하자
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define WORD_MAX_LENGTH 20
#define ALPHABET 26
#define EXIST 1
#define NOTEXIST 0
#define MAX 500000

struct TRIE;

typedef struct NODE
{
    char *data;
    int isExist;
    struct TRIE *next;

} node;

typedef struct TRIE
{
    node *arr[ALPHABET];
    int depth;
} trie;

void trie_init(trie *root, int depth)
{

    root->depth = depth;

    for (int i = 0; i < ALPHABET; i++)
    {
        root->arr[i] = (node *)malloc(sizeof(node));
        root->arr[i]->isExist = NOTEXIST;
    }
}

// trie에 영단어를 넣는 함수. 반드시 trie의 root 부터 시작한다.
void trie_push(trie *root, char *input)
{
    // 먼저 입력된 단어에서 depth번째 글자의 아스키코드 값을 가져온다.
    int idx = input[root->depth] - 97;
    int len = strlen(input);
    char *newData = (char *)malloc(sizeof(len));
    strcpy(newData, input);

    // 1. 알파벳이 들어갈 자리가 있으며, 하위 노드가 존재하지 않을 경우, 그냥 넣는다.
    if (root->arr[idx]->isExist == NOTEXIST && root->arr[idx]->next == NULL)
    {
        root->arr[idx]->data = newData;
        root->arr[idx]->isExist = EXIST;
    }
    else
    {
        // 예외 찾음

        /*
            ex. a, aa, aaa넣으면 aa자리에 aaa가 들어간다. 하....ㅠㅠ
        */

        // 2. 알파벳이 들어갈 자리가 없다 -> 같은 알파벳으로 시작하는 영단어가 2개이다. 그럼 그 다음 글자를 비교한다.

        // 먼저, 해당 노드에서 next trie를 만든다.
        root->arr[idx]->next = (trie *)malloc(sizeof(trie));
        trie_init(root->arr[idx]->next, root->depth + 1);

        // 두 영단어가 다음 알파벳이 존재하는지 확인한다.
        // 예를 들어, abc와 abcd 가 있을 경우 abc는 a-b-c의 data에 저장하고 abcd는 a-b-c-d의 data에 저장하게 하기 위해서이다. 즉, 알파벳이 더이상 존재하지 않는 영단어의 경우 내려가지 않고 해당 trie의 data에 그대로 넣는다.
        // 문제 조건 상 중복되는 단어는 없다.

        // 예외발생지점.
        /*
        3 4
        abbbc
        abbc
        abbcc
        넣었을 때 예외가 발생한다.
        */
        if (root->arr[idx]->data[root->depth + 1] == 0 || input[root->depth + 1] == 0)
        {
            // 둘 중 하나는 NULL이라는 소리.
            if (root->arr[idx]->data[root->depth + 1] == 0)
            {
                trie_push(root->arr[idx]->next, input);
            }
            else
            {
                char *data = root->arr[idx]->data;
                root->arr[idx]->data = input;
                trie_push(root->arr[idx]->next, data);
            }
        }
        else
        {
            // 다음 알파벳이 둘 다 존재할 경우, 현재 데이터가 들어있는 data를 NOTEXIST로 변경한 후, 두 데이터를 다음 노드로 옮겨 다시 배치한다.

            char *data = root->arr[idx]->data;
            root->arr[idx]->data = NULL;
            trie_push(root->arr[idx]->next, data);
            trie_push(root->arr[idx]->next, input);

            root->arr[idx]->isExist = NOTEXIST;
        }
    }
}

int existCount = 0;
char *sameData[MAX] = {0};

void trie_search(trie *root, char *search)
{
    // 해당 영단어가 있는지 확인하려면, 영단어의 각 단어마다 trie가 연결되어 있는지 확인하면 된다.
    int len = strlen(search);
    int idx = search[root->depth] - 97;

    // 일단, arr이 NULL이 아니어야 한다. NULL이라면 바로 컷
    if (root->arr[idx] == NULL)
    {

        return;
    }
    else
    {
        // 해당 공간에 데이터가 존재할 경우 비교해본다. 같다면 그냥 EXIST 해주면 되고, 같지 않을 경우 길이를 비교하여, search가 더 길면 조사를 계속한다.
        if (root->arr[idx]->isExist == EXIST)
        {
            if (strcmp(root->arr[idx]->data, search) == 0)
            {

                sameData[existCount] = (char *)malloc(sizeof(len));
                strcpy(sameData[existCount], search);
                existCount++;
                return;
            }

            if (strlen(root->arr[idx]->data) > strlen(search))
            {
                return;
            }
        }
        else
        {
            // 만약 데이터는 존재하지 않는데, 다음 노드가 존재한다면 찾아볼 수 있다.
            if (root->arr[idx]->next == NULL)
            {
                return;
            }
            else
            {
                trie_search(root->arr[idx]->next, search);
            }
        }
    }
}

void printData()
{
    printf("\n%d\n", existCount);
    for (int i = 0; i < existCount; i++)
    {
        printf("%s\n", sameData[i]);
    }
}

int main()
{
    trie *root = (trie *)malloc(sizeof(trie));
    trie_init(root, 0);

    // 문자열을 저장하는 배열
    int NumberOfData;
    int NumberOfFindingData;
    char *put;
    scanf("%d", &NumberOfData);
    scanf("%d", &NumberOfFindingData);
    for (int i = 0; i < NumberOfData; i++)
    {
        scanf("%s", put);
        trie_push(root, put);
    }

    // 문자열 찾기
    for (int i = 0; i < NumberOfFindingData; i++)
    {
        scanf("%s", put);
        trie_search(root, put);
    }

    printData();

    return 0;
}

// 3 4
// abbbc
// abbc
// abc
// abc
// aborta
// bac
// abbbc