#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct AbsComp{
    bool operator()(const int &l, const int &r)const
    {
        if(abs(l)!=abs(r))
            return abs(l)>abs(r);
        return l>r;
    }
};
priority_queue<int> max_pq;
priority_queue<int,vector<int>,greater<int>> min_pq;
priority_queue<int,vector<int>,AbsComp> abs_pq;

int main()
{
    int q, x;
    cin>>q;
    for(int i =0;i<q;i++)
    {
        cin >> x;
        if(x==0)
        {
            if(max_pq.size()==0)
                cout<<-1<<endl;
            cout<<max_pq.top()<<' '<<min_pq.top()<<' '<<abs_pq.top()<<endl;
            max_pq.pop(), min_pq.pop(), abs_pq.pop();
        }
        else
            max_pq.push(x), min_pq.push(x), abs_pq.push(x);
    }
}