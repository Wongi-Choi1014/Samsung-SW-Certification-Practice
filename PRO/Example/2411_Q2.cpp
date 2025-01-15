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
Ǯ����
1. hash arr[����3] ���ں��� �����Ѵ�. (�������� ����)
2. �� �� ���ڿ� �´� �������� �����ϱ�(A��, B��)
3. �տ��� ���� �߰��� ��� +A, B+ �� ��� +�ڸ��� ����Ѵ��� 3�ڸ� ���� ���ϱ�
4. A+, +B�� ��� +�ڸ��� ����Ѵ��� 3�ڸ� ���� ���ϱ�
5. A+, +B Boundary case ó��

Review
1. �迭 �ڷᱸ�� ������ �ʱ�ȭ ������ ��
2. ������ ������ idx �������� ���� ����� �׸��� ��� ó���� ��
3. ���� ������ �Ͱ�
*/

#include <iostream>
#include <queue>
using namespace std;

int countArr[1100];
deque<int> A_Line;
deque<int> B_Line;

int Boundary_Case[2];
void init_arr()
{
    for(int i = 0; i<1100; i++)
        countArr[i] = 0;
    for(int i = 0; i<2; i++)
        Boundary_Case[i] = 0;
    A_Line.clear();
    B_Line.clear();
}
void init(int mCnt1, int mDigitList1[30000], int mCnt2, int mDigitList2[30000]){
    init_arr();
    int A_1 = 0, A_2 = 0, A_3 = 0;
    int B_1 = 0, B_2 = 0, B_3 = 0;
    for(int i = 0; i < mCnt1; i++){
        A_Line.push_back(mDigitList1[i]);
        A_1 = mDigitList1[i];
        if(i>1)
            countArr[A_3*100 + A_2*10 + A_1]++;
        A_3 = A_2;
        A_2 = A_1;

    }
    for(int i = 0; i < mCnt2; i++){
        B_Line.push_back(mDigitList2[i]);
        B_1 = mDigitList2[i];
        if(i>1)
            countArr[B_3*100 + B_2*10 + B_1]++;
        B_3 = B_2;
        B_2 = B_1;
    }
    //Boundary case
    int A_last_idx = A_Line.size()-1;
    Boundary_Case[0] = A_Line[A_last_idx-1]*100 + A_Line[A_last_idx]*10 + B_Line[0];
    countArr[Boundary_Case[0]]++;
    Boundary_Case[1] = A_Line[A_last_idx]*100 + B_Line[0]*10 + B_Line[1];
    countArr[Boundary_Case[1]]++;
    //int Test=0;
}

void append(int mDir, int mNum1, int mNum2){
    //Boundary case
    if(Boundary_Case[0]>0)
        countArr[Boundary_Case[0]]--;
    if(Boundary_Case[1]>0)
        countArr[Boundary_Case[1]]--;
    if(mDir == 0)
    {
        //+A
        int A_1 = A_Line[1], A_2 = A_Line[0], A_3 = 0;
        int Data = mNum1;

        while(Data > 0)
        {
            A_Line.push_front(Data%10);
            A_3 = Data%10;
            countArr[A_3*100 + A_2*10 + A_1]++;
            Data /= 10;

            A_1 = A_2;
            A_2 = A_3;
        }
        //+B
        int B_1 = B_Line[1], B_2 = B_Line[0], B_3 = 0;
        Data = mNum2;

        while(Data > 0)
        {
            B_Line.push_front(Data%10);
            B_3 = Data%10;
            countArr[B_3*100 + B_2*10 + B_1]++;
            Data /= 10;


            B_1 = B_2;
            B_2 = B_3;
        }
        //Boundary case
        int A_last_idx = A_Line.size()-1;
        Boundary_Case[0] = A_Line[A_last_idx-1]*100 + A_Line[A_last_idx]*10 + B_Line[0];
        countArr[Boundary_Case[0]]++;
        Boundary_Case[1] = A_Line[A_last_idx]*100 + B_Line[0]*10 + B_Line[1];
        countArr[Boundary_Case[1]]++;
    }

    else
    {
        //A+
        int A_last_idx = A_Line.size()-1;
        int A_1 = 0, A_2 = A_Line[A_last_idx], A_3 = A_Line[A_last_idx-1];
        int Data = mNum1;
        deque<int> A_append_right;
        while(Data > 0)
        {
            A_append_right.push_front(Data%10);
            Data /= 10;
            
        }
        
        for(int i = 0; i<A_append_right.size(); i++)
        {
            A_1 = A_append_right[i];
            A_Line.push_back(A_append_right[i]);
            countArr[A_3*100 + A_2*10 + A_1]++;

            A_3 = A_2;
            A_2 = A_1;
        }
        //Boundary case
        A_last_idx = A_Line.size()-1;
        Boundary_Case[0] = A_Line[A_last_idx-1]*100 + A_Line[A_last_idx]*10 + B_Line[0];
        countArr[Boundary_Case[0]]++;
        Boundary_Case[1] = A_Line[A_last_idx]*100 + B_Line[0]*10 + B_Line[1];
        countArr[Boundary_Case[1]]++;
            
        //B+
        int B_last_idx = B_Line.size()-1;
        int B_1 = 0, B_2 = B_Line[B_last_idx], B_3 = B_Line[B_last_idx-1];
        Data = mNum2;
        deque<int> B_append_right;
        while(Data > 0)
        {
            B_append_right.push_front(Data%10);
            Data /= 10;
            
        }
        
        for(int i = 0; i<B_append_right.size(); i++)
        {
            B_1 = B_append_right[i];
            B_Line.push_back(B_append_right[i]);
            countArr[B_3*100 + B_2*10 + B_1]++;

            B_3 = B_2;
            B_2 = B_1;
        }

    }
}

int countNum(int mNum){
    return countArr[mNum];
}