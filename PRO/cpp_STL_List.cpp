#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

int main()
{
    list<int> li;
    for(int i =1;i<=5;i++)
        li.push_back(i);
    li.insert(li.begin(),0);
    li.insert(li.end(),6);
    li.erase(li.begin());
    li.pop_back();
    cout << li.empty()<<endl;
    cout << li.size()<<endl;

    li.push_front(0);
    //original
    cout<<"original for"<<endl;
    int cnt =1;
    for(auto it= li.begin();it!=li.end();++it)
    {

        cout << cnt << " : " << *it << endl;
        cnt++;
    }
    //for each?
    li.pop_front();
    cout<<"for each"<<endl;
    cnt = 1;
    for_each(li.begin(),li.end(),[&](int x)
    {
        cout<<cnt<<" : " <<x<<endl;
        cnt++;
    });
    li.sort(greater<int>{});
    //range based loop
    cout<<"range based loop"<<endl;
    cnt = 1;
    for(auto &it:li)
    {
        cout<<cnt<<" : " <<it<<endl;
        cnt++;
    }
    list<int> li2;
    li.splice(li.end(), li, li.begin());

    li2.splice(li2.begin(), li);

    li.splice(li.begin(),
    li2,
    li2.begin(), next(li2.begin(), 2));
    
    return 0;
}