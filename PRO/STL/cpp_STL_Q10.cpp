#include <iostream>
#include <string>
#include <list>

using namespace std;

void erase(list<char> &li, list<char>::iterator &it_li)
{
    if(it_li!= li.begin())
        li.erase(prev(it_li,1));
}

void left_shift(list<char> &li, list<char>::iterator &it_li)
{
    if(it_li!=li.begin())
        --it_li;
}

void right_shift(list<char> &li, list<char>::iterator &it_li)
{
    if(it_li!=li.end())
        ++it_li;
}


int main()
{
    int TC;
    cin >> TC;
    
    for(int i=0;i<TC;i++ )
    {
        string str;
        list<char> li;
        cin >> str;
        
        list<char>::iterator it_li = li.end();
        for(auto it_str=str.begin();it_str!=str.end();++it_str)
        //for(char it_str:str)
        {
            //cout << *it_str<<endl;
            if(*it_str=='-')
                erase(li, it_li);

            else if(*it_str=='<')
            {
                //if(it_li!=li.begin())
                //    --it_li;
                left_shift(li, it_li);
            }
                //it_li = left_shift(li, it_li);

            else if(*it_str=='>')
            {
                //if(it_li!=li.end())
                //    ++it_li;
                right_shift(li, it_li);
            }
                //it_li = right_shift(li, it_li);

            else
            {
                li.insert(it_li,*it_str);
                //if(it_li!=li.end())
                    //it_li++;
            }
        }
        for(auto &it:li)
            cout<<it;
        cout<<endl;
    }
}