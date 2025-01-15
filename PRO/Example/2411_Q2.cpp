//main.cpp

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int mCnt1, int mDigitList1[30000], int mCnt2, int mDigitList2[30000]);
extern void append(int mDir, int mNum1, int mNum2);
extern int countNum(int mNum);

#define CMD_INIT 1
#define CMD_APPEND 2
#define CMD_COUNT 3

static int mDigitList1[30000];
static int mDigitList2[30000];
static char temp[30001];

static bool run()
{
    int query_num;
    scanf("%d", &query_num);

    int ans;
    bool ok = false;

    for (int q = 0; q < query_num; q++)
    {
        int query;
        scanf("%d", &query);
        if (query == CMD_INIT)
        {
            int mCnt1, mCnt2;
            scanf("%d", &mCnt1);
            scanf("%s", temp);
            for (int i = 0; i < mCnt1; i++){
                mDigitList1[i] = temp[i] - '0';
            }
            for (int i = mCnt1; i < 30000; i++){
                mDigitList1[i] = 0;
            }
            scanf("%d", &mCnt2);
            scanf("%s", temp);
            for (int i = 0; i < mCnt2; i++){
                mDigitList2[i] = temp[i] - '0';
            }
            for (int i = mCnt2; i < 30000; i++){
                mDigitList2[i] = 0;
            }
            init(mCnt1, mDigitList1, mCnt2, mDigitList2);
            ok = true;
        }
        else if (query == CMD_APPEND)
        {
            int mDir, mNum1, mNum2;
            scanf("%d %d %d", &mDir, &mNum1, &mNum2);
            append(mDir, mNum1, mNum2);
        }
        else if (query == CMD_COUNT)
        {
            int mNum;
            scanf("%d", &mNum);
            int ret = countNum(mNum);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
    }
    return ok;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("sample_input_2411_Q2.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);
    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}

//user.cpp
/*
풀이
1. hash arr[숫자3] 숫자별로 저장한다. (전역변수 설정)
2. 각 줄 숫자에 맞는 전역변수 설정하기(A줄, B줄)
3. 앞열에 숫자 추가할 경우 +A, B+ 일 경우 +자릿수 계산한다음 3자리 숫자 더하기
4. A+, +B일 경우 +자릿수 계산한다음 3자리 숫자 더하기
5. A+, +B Boundary case 처리

Review
1. 배열 자료구조 변수수 초기화 주의할 것
2. 복잡한 구조로 idx 설정하지 말고 공통된 항목은 묶어서 처리할 것
3. 방향 주의할 것것
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int countArr[1100];
int A_front[2];
int B_front[2];
int A_back[2];
int B_back[2];

vector<int> A_append_right;
vector<int> B_append_right;

//deque<int> A_Line;
//deque<int> B_Line;

int Boundary_Case[2];
void init_arr()
{
    A_append_right.reserve(5);
    B_append_right.reserve(5);
    for(int i = 0; i<1100; i++)
        countArr[i] = 0;
    for(int i = 0; i<2; i++)
    {
        Boundary_Case[i] = 0;
        A_front[i] = 0;
        B_front[i] = 0;
        A_back[i] = 0;
        B_back[i] = 0;
    }
    //A_Line.clear();
    //B_Line.clear();
}
void init(int mCnt1, int mDigitList1[30000], int mCnt2, int mDigitList2[30000]){
    init_arr();
    int A_1 = 0, A_2 = 0, A_3 = 0;
    int B_1 = 0, B_2 = 0, B_3 = 0;
    for(int i = 0; i < mCnt1; i++){
        //A_Line.push_back(mDigitList1[i]);
        A_1 = mDigitList1[i];
        if(i>1)
            countArr[A_3*100 + A_2*10 + A_1]++;
        else
            A_front[i] = A_1;
        A_3 = A_2;
        A_2 = A_1;

    }
    for(int i = 0; i < mCnt2; i++){
       //B_Line.push_back(mDigitList2[i]);
        B_1 = mDigitList2[i];
        if(i>1)
            countArr[B_3*100 + B_2*10 + B_1]++;\
        else
            B_front[i] = B_1;
        B_3 = B_2;
        B_2 = B_1;
    }
    //Boundary case
    //int A_last_idx = A_Line.size()-1;
    A_back[0] = A_3;
    A_back[1] = A_2;

    B_back[0] = B_3;
    B_back[1] = B_2;
    Boundary_Case[0] = A_back[0]*100 + A_back[1]*10 + B_front[0];
    countArr[Boundary_Case[0]]++;
    Boundary_Case[1] = A_back[1]*100 + B_front[0]*10 + B_front[1];
    countArr[Boundary_Case[1]]++;
    //int Test=0;
}

void append(int mDir, int mNum1, int mNum2){
    //Boundary case
    //if(Boundary_Case[0]>0)
    countArr[Boundary_Case[0]]--;
    //if(Boundary_Case[1]>0)
    countArr[Boundary_Case[1]]--;
    if(mDir == 0)
    {
        //+A
        int A_1 = A_front[1], A_2 = A_front[0], A_3 = 0;
        int Data = mNum1;

        while(Data > 0)
        {
            //A_Line.push_front(Data%10);
            A_3 = Data%10;
            countArr[A_3*100 + A_2*10 + A_1]++;
            Data /= 10;

            A_1 = A_2;
            A_2 = A_3;
        }
        A_front[0] = A_2;
        A_front[1] = A_1;

        //+B
        int B_1 = B_front[1], B_2 = B_front[0], B_3 = 0;
        Data = mNum2;

        while(Data > 0)
        {
            //B_Line.push_front(Data%10);
            B_3 = Data%10;
            countArr[B_3*100 + B_2*10 + B_1]++;
            Data /= 10;


            B_1 = B_2;
            B_2 = B_3;
        }
        B_front[0] = B_2;
        B_front[1] = B_1;

        //Boundary case
        //int A_last_idx = A_Line.size()-1;
        Boundary_Case[0] = A_back[0]*100 + A_back[1]*10 + B_front[0];
        countArr[Boundary_Case[0]]++;
        Boundary_Case[1] = A_back[1]*100 + B_front[0]*10 + B_front[1];
        countArr[Boundary_Case[1]]++;
    }

    else
    {
        //A+
        //int A_last_idx = A_Line.size()-1;
        int A_1 = 0, A_2 = A_back[1], A_3 = A_back[0];
        int Data = mNum1;
        A_append_right.clear();
        B_append_right.clear();
        while(Data > 0)
        {
            A_append_right.push_back(Data%10);
            Data /= 10;
            
        }
        
        for(int i = A_append_right.size()-1; i>=0; i--)
        {
            A_1 = A_append_right[i];
            //A_Line.push_back(A_append_right[i]);
            countArr[A_3*100 + A_2*10 + A_1]++;

            A_3 = A_2;
            A_2 = A_1;
        }
        A_back[0] = A_3;
        A_back[1] = A_2;
        //Boundary case
        //A_last_idx = A_Line.size()-1;
        Boundary_Case[0] = A_back[0]*100 + A_back[1]*10 + B_front[0];
        countArr[Boundary_Case[0]]++;
        Boundary_Case[1] = A_back[1]*100 + B_front[0]*10 + B_front[1];
        countArr[Boundary_Case[1]]++;
            
        //B+
        //int B_last_idx = B_Line.size()-1;
        int B_1 = 0, B_2 = B_back[1], B_3 = B_back[0];
        Data = mNum2;
        
        while(Data > 0)
        {
            B_append_right.push_back(Data%10);
            Data /= 10;
            
        }
        
        for(int i = B_append_right.size()-1; i>=0; i--)
        {
            B_1 = B_append_right[i];
            //B_Line.push_back(B_append_right[i]);
            countArr[B_3*100 + B_2*10 + B_1]++;

            B_3 = B_2;
            B_2 = B_1;
        }
        B_back[0] = B_3;
        B_back[1] = B_2;

    }
}

int countNum(int mNum){
    return countArr[mNum];
}