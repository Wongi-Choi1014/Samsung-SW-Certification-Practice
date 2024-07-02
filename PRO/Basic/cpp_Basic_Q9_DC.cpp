#include <iostream>
#include <vector>
using namespace std;
/*** user.cpp ***/
extern bool checkCards(int indexA, int indexB, int diff);

void playGame(int N)
{
    vector<vector<int>> stack;
    int M = 2*N;
    int diff = (M+1)/7;
    
    // 두 카드의 숫자를 비교하기 위해 아래와 같이 checkCards 함수를 사용합니다.
    vector<int> front, back;
    front.push_back(0);
    for(int i =1;i<M;i++)
    {
        if(checkCards(0,i, diff))
            front.push_back(i);
        else
            back.push_back(i);
    }
    stack.push_back(front);
    stack.push_back(back);
    

    while(!stack.empty())
    {
        vector<int> substack, front, back;
        substack = stack.back();
        stack.pop_back();
        int substack_size = substack.size();
        if(substack_size==2)
        {
            checkCards(substack[0],substack[1], 0);
            continue;
        }
        diff = substack_size /7 ;
        front.push_back(*substack.begin());
        for(auto it =  substack.begin()+1;it!=substack.end();it++)
        {
            if(checkCards(*substack.begin(),*it, diff))
                front.push_back(*it);
            else
                back.push_back(*it);
        }
        stack.push_back(front);
        stack.push_back(back);
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