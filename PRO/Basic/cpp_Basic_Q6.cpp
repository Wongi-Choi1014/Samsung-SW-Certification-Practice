#include <iostream>
#include <algorithm>

using namespace std;

int binary_search_loop(int left, int right, int mid, int target, int *arr)
{
    while(left<=right)
    {
        if(target ==arr[mid])
            return mid;
        if(target>arr[mid])
            left = mid+1;
        else
            right = mid-1;
        mid = (left + right)/2;
    }
    return -1;
}

int binary_search_recursive(int left, int right, int mid, int target, int *arr)
{
    if(left>right)
        return -1;
    if(target ==arr[mid])
        return mid;
    if(target>arr[mid])
        return binary_search_recursive(mid+1, right, (mid+1 + right)/2, target, arr);
    else
        return binary_search_recursive(left, mid-1, (left + mid-1)/2, target, arr);
}

int binary_search_lower_bound(int *arr,int N,int target)
{
    auto it = lower_bound(arr,arr+N,target);
    if(*it==target)
        return it-arr;
    else
        return -1;
}

int main()
{
#ifdef _WIN32
    freopen("input_Q6.txt", "r",stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    cin>>N;
    int *A = new int[N];

    for(int i=0;i<N;i++)
        cin>>A[i];

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
        cout << binary_search_lower_bound(A, N, target)<< ' ';
    }
}