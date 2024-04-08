#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

map<int,int> tofu;

int main()
{
    int q, x;
    int price, flag;
    cin>>q;
    for(int i =0;i<q;i++)
    {
        cin >> x;
        if(x==1)
        {
            cin>>price;
            cout<<++tofu[price]<<endl;
        }
        else if (x==2)
        {
            cin>>price;
            auto it = tofu.find(price);
            if(it!=tofu.end())
            {
                cout<<--it->second<<endl;
                if(it->second==0)
                    tofu.erase(it);
            }
            else
                cout<<-1<<endl;
        }
        else
        {
            cin>>flag;
            if(flag==0)
            {
                auto it = tofu.begin();
                cout<<it->first<<" "<<--it->second<<endl;
                if(it->second==0)
                    tofu.erase(it);
            }
            else
            {
                auto it = --tofu.end();
                cout<<it->first<<" "<<--it->second<<endl;
                if(it->second==0)
                    tofu.erase(it);
            }

        }
    }
}