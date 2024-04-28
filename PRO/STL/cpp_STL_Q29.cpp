#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
    //freopen("input.txt", "r", stdin);
    int Q;
    string ipt;
    set<string> DB;

    cin>>Q;
    for(int i =0;i<Q;i++)
    {
        cin>>ipt;
        if(DB.insert(ipt).second==false)
            DB.erase(ipt);
    }
    cout <<DB.size();
}