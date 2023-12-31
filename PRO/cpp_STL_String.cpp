#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    string str{"ABCDE"};
    str.insert(0,"ZZ");
    str.insert(str.cend(),'F');
    str.erase(str.begin());
    str.pop_back();
    cout << str.empty()<<endl;
    cout << str.size()<<endl;
    //순서 상관없으면 O(1) erase 가능
    str[2] = str.back();
    str.pop_back();
    str.push_back('Z');
    //original
    cout<<"original for"<<endl;
    int cnt =1;
    for(auto it= str.begin();it!=str.end();++it)
    {
        //cout<<*it;
        cout << cnt << " : " << *it << endl;
        //printf("%d : %d \n",cnt,*it);
        cnt++;
    }
    //for each?
    cout<<"for each"<<endl;
    cnt = 1;
    for_each(str.begin(),str.end(),[&](int x)
    {
        cout<<cnt<<" : " <<x<<endl;
        cnt++;
    });
    str.pop_back();
    //range based loop
    cout<<"range based loop"<<endl;
    cnt = 1;
    for(auto &it:str)
    {
        cout<<cnt<<" : " <<it<<endl;
        cnt++;
    }
    cout<<str<<endl;
    return 0;
}