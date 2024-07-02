#include <iostream>
#include <vector>
using namespace std;
/*** user.cpp ***/
extern bool checkCards(int indexA, int indexB, int diff);

int zero_diff_idx[50000][4];
int cnt[50000];


void playGame(int N)
{
    int left, mid, right;
    for(int i =0;i<N;i++)
        cnt[i]=0;
    // 두 카드의 숫자를 비교하기 위해 아래와 같이 checkCards 함수를 사용합니다.
    zero_diff_idx[0][cnt[0]++]=0;
    for(int i =1;i<2*N;i++)
    {
        left=0;right=N-1;mid=(left+right)/2;
        while(left<=right)
        {
            if(checkCards(0, i, mid))
                right=mid-1;
            else
                left=mid+1;
            mid=(left+right)/2;
        }
        for(int j=0; j<cnt[left];j++)
        {
            checkCards(i,zero_diff_idx[left][j], 0);
        }
        zero_diff_idx[left][cnt[left]++]=i;
    }
}
 
 
/*** main.cpp ***/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
 
#include<stdio.h>
 
#define MAX_N 50000
#define ABS(a) (((a) < 0) ? -(a) : (a))
 
extern void playGame(int N);
 
static int N;
static int cards[MAX_N * 2];
static bool found[MAX_N + 1];
static int foundCnt;
static bool ok;
 
bool checkCards(int indexA, int indexB, int diff)
{
    if (!ok || indexA < 0 || indexA >= N * 2 || indexB < 0 || indexB >= N * 2)
    {
        ok = false;
        return false;
    }
 
    if (ABS(cards[indexA] - cards[indexB]) > diff)
    {
        return false;
    }
 
    int val = cards[indexA];
    if (diff == 0 && indexA != indexB && !found[val])
    {
        foundCnt += 1;
        found[val] = true;
    }
 
    return true;
}
 
void init()
{
    foundCnt = 0;
    ok = true;
 
    for (int i = 1; i <= N; i++)
    {
        found[i] = false;
    }
}
 
static bool run()
{
    scanf("%d", &N);
    for (int i = 0; i < 2 * N; i++)
    {
        scanf("%d", &cards[i]);
    }
 
    init();
    playGame(N);
 
    return ok && foundCnt == N;
}
 
int main()
{
    setbuf(stdout, NULL);
    freopen("input_Q9.txt", "r", stdin);
 
    int T, MARK;
    scanf("%d%d", &T, &MARK);
 
    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
 
    return 0;
}