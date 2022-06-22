/*
trie를 만들자. 영단어 모음을 저장하는 trie를 만들자.

영단어는 26개의 알파벳으로 구성되어 있으므로, trie의 root는 26개의 알파벳으로 이루어진다.

즉, 어떤 알파벳인지 표시하는 부분과, 다음 node로 확장할 수 있는 포인터 공간, 그리고 데이터를 저장할 수 있는 공간 세가지가 있어야 한다.

구조체는 아래와 같이 생겼을 것이다.


*/

#include <stdio.h>
#define WORD_MAX_LENGTH 20
#define ALPHABET 26

struct TRIE;

typedef struct NODE
{
    int alphabet;
    char data[WORD_MAX_LENGTH];
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
        root->arr[i]->alphabet = i;
    }
}

void trie_push(trie *root, char input[WORD_MAX_LENGTH])
{
    // 먼저 입력된 단어에서 x번째 글자를 가져온다.
    int idx = input[root->depth] - 97;

    // 1. 알파벳이 들어갈 자리가 있는 경우
    if (root->arr[idx]->alphabet)
}

int main()
{
}