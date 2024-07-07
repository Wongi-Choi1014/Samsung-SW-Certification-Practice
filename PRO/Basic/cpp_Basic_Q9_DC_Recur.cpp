#include <iostream>
#include <vector>
using namespace std;
/*** user.cpp ***/
extern bool checkCards(int indexA, int indexB, int diff);

int A[1000001];
void recur(int s, int e)
{
    if(s+1==e)
    {
        checkCards(A[s], A[e], 0);
        return;
    }
    int mid = s;
    int diff = (e-s)/6;
    for(int i=s+1;i<=e;i++)
    {
        if(checkCards(A[s], A[i], diff))
            swap(A[++mid],A[i]);
    }
    recur(s,mid);
    recur(mid+1,e);
}

void playGame(int N)
{
    int M = 2*N;
    for(int i=0;i<M;i++)
        A[i]=i;
    recur(0,M-1);
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