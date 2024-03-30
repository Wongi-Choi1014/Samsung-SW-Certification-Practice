#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int main()
{
    queue<int> q;
    for(int i =1;i<=5;i++)
        q.push(i);
    q.pop();
    cout << q.empty()<<endl;
    cout << q.size()<<endl;
    //순서 상관없으면 O(1) erase 가능
    q.pop();
    q.push(0);
    //original
    cout<<"original for"<<endl;
    int cnt =1;
    int size = q.size();
    for(int it= 0;it<size;it++)
    {

        cout << cnt << " : " << q.front() << endl;
        q.pop();
        cnt++;
    }
    
    return 0;
}