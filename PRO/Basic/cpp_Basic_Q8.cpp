#include <iostream>
#include <algorithm>

using namespace std;

int Page[100000];
long long Page_Sum[100000];
int result[100000]; 
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
    int left,right,mid,target;
    left=0;
    for(int i=0;i<K-1;i++)
    {
        right=N-1;
        mid = (left+right)/2;
        target = Page_Sum[N-1]/K*(i+1);
        while(left<=right)
        {
            if(target==Page_Sum[mid])
                right=mid;
            if(target<Page_Sum[mid])
                right=mid-1;
            else
                left=mid+1;
            mid = (left+right)/2;
        }
        result[i]=right;
        left=right+1;
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