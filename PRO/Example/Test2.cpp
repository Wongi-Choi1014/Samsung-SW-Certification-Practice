
#include <iostream>
#include <map>
#include <set>

using namespace std;

void main()
{
    map<int,set<int>,greater<int>> test;
    map<int,int> test2;
    test[1].insert(1);
    test[1].erase(1);
    test2[1]=1;
    test2[2]=2;
    test2[3]=3;
    test2[5]=5;
    test2[6]=6;
    auto it = --test2.upper_bound(7);
    cout << (--test2.lower_bound(7))->second << ' ' << test2.upper_bound(3)->second <<endl;

    return;

}

