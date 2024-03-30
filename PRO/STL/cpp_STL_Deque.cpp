#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

int main()
{
    deque<int> dq;
    for(int i =1;i<=5;i++)
        dq.push_back(i);
    dq.insert(dq.begin(),0);
    dq.insert(dq.end(),6);
    dq.erase(dq.begin());
    dq.pop_back();
    cout << dq.empty()<<endl;
    cout << dq.size()<<endl;
    //순서 상관없으면 O(1) erase 가능
    dq[2] = dq.back();
    dq.pop_back();
    dq.push_front(0);
    //original
    cout<<"original for"<<endl;
    int cnt =1;
    for(auto it= dq.begin();it!=dq.end();++it)
    {

        cout << cnt << " : " << *it << endl;
        cnt++;
    }
    //for each?
    cout<<"for each"<<endl;
    cnt = 1;
    for_each(dq.begin(),dq.end(),[&](int x)
    {
        cout<<cnt<<" : " <<x<<endl;
        cnt++;
    });
    dq.pop_front();
    //range based loop
    cout<<"range based loop"<<endl;
    cnt = 1;
    for(auto &it:dq)
    {
        cout<<cnt<<" : " <<it<<endl;
        cnt++;
    }
    
    return 0;
}