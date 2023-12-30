#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    vector<int> v;
    for(int i =1;i<=5;i++)
        v.push_back(i);
    v.insert(v.begin(),0);
    v.insert(v.end(),6);
    v.erase(v.begin());
    v.pop_back();
    cout << v.empty()<<endl;
    cout << v.size()<<endl;
    //순서 상관없으면 O(1) erase 가능
    v[2] = v.back();
    v.pop_back();
    return 0;
}