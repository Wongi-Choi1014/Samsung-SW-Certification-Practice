#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

long long Page[100105];
long long Page_Sum[100105];
vector<long long> result;

int main()
{
#ifdef _WIN32
    freopen("input_Q8.txt", "r",stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long N,K;
    cin>>N>>K;
    long long left_min;
    Page_Sum[0]=0;
    for(long long i=0;i<N;i++)
    {
        cin>>Page[i];
        if(i==0)
        {
            left_min =Page[i];
            Page_Sum[i+1]=Page[i];
        }
        else
            Page_Sum[i+1]=Page_Sum[i]+Page[i];
        if(left_min>Page[i])
            left_min=Page[i];
    }
    long long left,right,mid;
    left = left_min;
    right= Page_Sum[N];
    mid = (left+right)/2;
    //mid = Page_Sum[N] / K;
    long long split_count = 0;
    
    while (left <= right)
    {
        vector<long long> validation;
        split_count = 1;
        long long compare_idx = N;
        for(long long i=N-2;i>=0;i--)
        {
            if((Page_Sum[compare_idx]-Page_Sum[i])>mid)
            {
                compare_idx=i+1;
                validation.push_back(i);
                split_count++;
            }
        }
        
        if (split_count > K)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
        mid = (left + right) / 2;
        if(left > right && split_count>K)
        {
            right=left;
            mid = (left + right) / 2;
            continue;
        }
        if(left > right)
        {
            result = validation;
        }
    }
    long long start_idx, end_idx;
    long long skew=K-(result.size()+1);
    long long split_point = result.back();
    result.pop_back();

    for(long long i=0;i<N;i++)
    {
        cout<<Page[i]<<" ";
        if(i==split_point)
        {
            cout<<"/ ";
            split_point = result.back();
            result.pop_back();
        }
        else if(skew>=1)
        {
            skew--;
            cout<<"/ ";
        }
    }
    cout<<'\n';
}