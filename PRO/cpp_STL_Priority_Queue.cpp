#include <iostream>
#include <queue>

using namespace std;

struct AbsComp{
    bool operator()(const int &l, const int &r) const{
        return abs(l) < abs(r);
    }
};
int main()
{
    //내림차순
    //priority_queue<int> pq;
    //오름차순
    //priority_queue<int, vector<int>, greater<int>> pq;
    //절대값
    priority_queue<int, vector<int>, AbsComp> pq;
    
    for(int i =1;i<=10;i++)
        if (i%2 ==1)
            pq.push(-i);
        else
            pq.push(i);

    pq.pop();
    cout << pq.empty()<<endl;
    cout << pq.size()<<endl;
    pq.push(121);
    //original
    cout<<"original for"<<endl;
    int cnt =1;
    int size = pq.size();
    for(auto it= 0;it<size;++it)
    {

        cout << cnt << " : " << pq.top() << endl;
        pq.pop();
        cnt++;
    }
    
    return 0;
}