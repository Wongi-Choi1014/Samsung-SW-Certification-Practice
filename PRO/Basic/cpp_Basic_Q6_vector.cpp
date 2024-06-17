/*
������ ����ħ
1. Vector ��� �� �̸� ����� ũ�⸸ŭ reserve�� �Ͽ� �ð��� ������
2. Vector �Լ��� ���� �� ������ ���� �������
3. 
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int binary_search_lower_bound(vector<int>&A,int target)
{
    auto it = lower_bound(A.begin(),A.end(),target);
    if(it==A.end() || *it!=target)
    //if(*it==target)
        return -1;
    else
        return it - A.begin();
}

int main()
{
#ifdef _WIN32
    freopen("input_Q6.txt", "r",stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N, ipt;
    cin>>N;
    vector<int> A;
    A.reserve(N);
    for(int i=0;i<N;i++)
    {
        cin>>ipt;
        A.push_back(ipt);
    }

    int Q;
    cin>>Q;
    int *B = new int[Q];

    for(int i=0;i<Q;i++)
        cin>>B[i];
    
    int left, right, mid, target;
    for(int i=0;i<Q;i++)
    {
        left = 0;
        right = N-1;
        mid = (left + right)/2;
        target = B[i];
        //cout << binary_search_loop(left, right, mid, target, A)<< ' ';
        //cout << binary_search_recursive(left, right, mid, target, A)<< ' ';
        cout << binary_search_lower_bound(A, target)<< ' ';
    }
}