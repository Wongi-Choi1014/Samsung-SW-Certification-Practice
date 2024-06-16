#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main(){
    freopen("input.txt", "r", stdin);
    
    long long TC, calculate,tmp;
    long long result[3]; 
    result[2] = 2000000000;
    long long Liquid;
    vector<long long> table;
    cin >> TC;

    int sign, flag;
    sign = TC;
    flag = 0;

    for(int i=0; i<TC; i++)
    {
        cin >>Liquid;
        table.push_back(Liquid);
        if((Liquid > 0) && (flag==0))
        {
            flag = 1;
            sign = i;
        }
    }
    if((sign<TC) &&(sign>0))
    {
        //auto it_prev = table.begin()+sign;
        auto it_prev = table.end();
        for(auto it=table.begin(); it!=table.begin()+sign; it++)
        //for(auto it=table.begin(); it!=table.end()-1; it++)
        {
            tmp = 2000000000;
            //for(auto it_b=it_prev; it_b!=table.end();it_b++)
            for(auto it_b=it_prev; it_b!=table.begin()+sign;)
            //for(auto it_b=table.end(); it_b!=it+1;)
            {
                it_b--;
                calculate = abs(*it+*it_b);
                if(tmp<calculate)
                    break;
                tmp = calculate;
                if(calculate<result[2])
                {
                    result[0] = *it;
                    result[1] = *it_b;
                    result[2] = calculate;
                }
                it_prev = it_b+1;
            }
        }
        if(abs(*(table.begin()+sign-2)+*(table.begin()+sign-1))<result[2])
        {
            result[0] = *(table.begin()+sign-2);
            result[1] = *(table.begin()+sign-1);
            result[2] = abs(*(table.begin()+sign-2)+*(table.begin()+sign-1));
        }
        if(abs(*(table.begin()+sign)+*(table.begin()+sign+1))<result[2])
        {
            result[0] = *(table.begin()+sign);
            result[1] = *(table.begin()+sign+1);
            result[2] = abs(*(table.begin()+sign)+*(table.begin()+sign+1));
        }
    }
    else if(sign==0)
    {
        result[0] = *table.begin();
        result[1] = *(table.begin()+1);
        result[2] = *table.begin()+*(table.begin()+1);
        /*
        for(auto it=table.begin(); it!=table.end(); it++)
        {
            for(auto it_b=table.end(); it_b!=table.begin();)
            {

                it_b--;
                calculate = abs(*it+*it_b);
                if(tmp<calculate)
                    break;
                tmp = calculate;
                if(calculate<result[2])
                {
                    result[0] = *it;
                    result[1] = *it_b;
                    result[2] = calculate;
                }
            }
        }
        */
    }
    else
    {
        result[0] = *(table.end()-2);
        result[1] = *(table.end()-1);
        result[2] = *(table.end()-2)+*(table.end()-1);
    }
    cout<<result[0]<<' '<<result[1]<<endl;
    //Test
    //cout<<result[2]<<endl;
    return 0;
}