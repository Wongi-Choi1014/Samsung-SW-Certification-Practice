#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Data{
    int id, score;
    bool operator<(const Data &r) const{
        if(score==r.score) return id < r.id;
        return score < r.score;
    }
    bool operator>(const Data &r) const{
        if(score==r.score) return id > r.id;
        return score > r.score;
    }
};

priority_queue<Data> max_pq;
priority_queue<Data,vector<Data>,greater<Data>> min_pq;
int hash_data[100001];

template<typename T>
void print(T&pq)
{
    while(pq.size())
    {
        Data top = pq.top();
        if(top.score==hash_data[top.id])
        {
            cout << top.id<<endl;
            return;
        }
        pq.pop();
    }
    cout<<-1<<endl;
}


int main()
{
    int q, x;
    int id, score;
    cin>>q;
    for(int i =0;i<q;i++)
    {
        cin >> x;
        if(x==1)
        {
            cin>>id>>score;
            hash_data[id]=score;
            max_pq.push({id,score});
            min_pq.push({id,score}); 
        }
        else if(x==2)
        {
            cin>>id;
            hash_data[id]=0;
        }
        else if(x==3)
        {
            print(min_pq);
        }
        else
        {
            print(max_pq);
        }
    }
}