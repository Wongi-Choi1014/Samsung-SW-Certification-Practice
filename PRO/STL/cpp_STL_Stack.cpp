#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

int main()
{
    stack<int> st;
    for(int i =1;i<=5;i++)
        st.push(i);
    st.pop();
    cout << st.empty()<<endl;
    cout << st.size()<<endl;
    //순서 상관없으면 O(1) erase 가능
    st.pop();
    st.push(0);
    //original
    cout<<"original for"<<endl;
    int cnt =1;
    int size = st.size();
    for(int it= 0;it<size;it++)
    {

        cout << cnt << " : " << st.top() << endl;
        st.pop();
        cnt++;
    }
    
    return 0;
}