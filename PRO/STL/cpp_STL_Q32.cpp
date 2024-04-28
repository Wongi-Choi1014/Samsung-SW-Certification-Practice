#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

unordered_map<string, int> DB;
int current_login = 0;

int validate(string ID)
{
    return DB.count(ID);
}
int activate(string ID)
{
    if(DB.count(ID)==1)
        return DB[ID];
    return 0;
}

int signup(string ID)
{
    //if(DB.count(ID)==0)
    DB.insert({ID,0});
    return DB.size();
}

int close(string ID)
{
    auto it = DB.find(ID);
    if(it!=DB.end())
    {
        if(it->second==1)
            current_login-=1;
        DB.erase(ID);
    }
    /*
    if(DB.count(ID)==1)
    {
        if(DB[ID]==1)
            current_login-=1;
        DB.erase(ID);
    }
    */
    return DB.size();
}
int login(string ID)
{
    auto it = DB.find(ID);
    if(it!=DB.end() && it->second==0)
    {
        it->second=1;
        current_login+=1;
    }
    /*
    if(DB.count(ID)==1 && DB[ID]==0)
    {
        DB[ID]=1;
        current_login+=1;
    }
    */
    return current_login;
}
int logout(string ID)
{
    auto it = DB.find(ID);
    if(it!=DB.end() && it->second==1)
    {
        it->second=0;
        current_login-=1;
    }
    /*
    if(DB.count(ID)==1 && DB[ID]==1)
    {
        DB[ID]=0;
        current_login-=1;
    }
    */
    return current_login;
}

int main()
{
    //freopen("input.txt", "r", stdin);
    int N, cmd;
    string ID;


    cin>>N;
    for(int i =0;i<N;i++)
    {
        cin>>cmd;
        cin>>ID;
        switch(cmd){
            case 1:
                cout<< validate(ID)<<endl;
                break;
            case 2:
                cout<< activate(ID)<<endl;
                break;
            case 3:
                cout<< signup(ID)<<endl;
                break;
            case 4:
                cout<< close(ID)<<endl;
                break;
            case 5:
                cout<< login(ID)<<endl;
                break;
            case 6:
                cout<< logout(ID)<<endl;
                break;
            default:
                break;
        }
    }
}