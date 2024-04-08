#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> dict;

void Q_1()
{
    string str;
    cin >> str;
    transform(str.begin(),str.end(),str.begin(),::tolower);
    //if(str.size()<=15)
    dict.push_back(str);
}
void Q_2()
{
    int c;
    cin >> c;
    if(c==0)
        partial_sort(dict.begin(),dict.begin()+3,dict.end());
    else if(c==1)
        partial_sort(dict.begin(),dict.begin()+3,dict.end(),greater<string>{});
    else
        partial_sort(dict.begin(),dict.begin()+3,dict.end(),
        [](string& l, string& r){
            if(l.size() != r.size())
                return l.size() < r.size();
            return l < r;});
    cout <<dict[0]<<' ' <<dict[1]<<' ' <<dict[2]<<' '<<endl;
}
void Q_3()
{
    string str;
    cin >> str;
    transform(str.begin(),str.end(),str.begin(),::tolower);
    str = dict[0]+str;
    if(str.size()>15)
        str = str.substr(0,15);
    dict[0] = str;
    cout<<str<<endl;
}

int main()
{
    //freopen("input.txt", "r", stdin);
    int Q, cmd;
    cin >>Q;
    for(int i=0;i<Q;i++)
    {
        cin >>cmd;
        if(cmd==1)
            Q_1();
        else if(cmd==2)
            Q_2();
        else
            Q_3();
    }
}