#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int Page[100000];
long long Page_Sum[100000];
vector<int> result;

int main()
{
#ifdef _WIN32
    freopen("input_Q8.txt", "r",stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int N,K;
    cin>>N>>K;

    for(int i=0;i<N;i++)
    {
        cin>>Page[i];
        if(i==0)
            Page_Sum[i]=Page[i];
        else
            Page_Sum[i]=Page_Sum[i-1]+Page[i];
    }
    int left,right,mid;
    left = 0;
    right= Page_Sum[N - 1];
    //mid = (left+right)/2;
    mid = Page_Sum[N-1]/K;
    int cnt=0;
    
    while (left <= right)
    {
        
        mid = (left + right) / 2;

        //result[i] = right;
        left = right + 1;
        vector<int> validation;
        validation.push_back(N-1);
        for(int i=N-1;i>0;i++)
        {
            
        }
        if(cnt==K)
            result=validation;
        else
            cnt=0;
        if (K < cnt)
            left = mid + 1;
        else
            right = mid - 1;
        mid = (left + right) / 2;
    }
    result[K-1]=N-1;
    
    int s=0;
    for(int i=0;i<K;i++)
    {
        for(int j=s;j<=result[i];j++)
        //    cout<<Page[j]<<" ";
        if(i!=K-1)
        //    cout<<"/ ";
        s = result[i]+1;
        if(i==0)
            cout<<Page_Sum[result[i]]<<'\n';
        else
            cout<<Page_Sum[result[i]]-Page_Sum[result[i-1]]<<'\n';
    }
    int debug=0;
}