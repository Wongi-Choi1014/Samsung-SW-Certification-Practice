#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void print_vector(vector<int> &v,string msg){
    int cnt =1;
    for(auto it= v.begin();it!=v.end();++it)
    {
        cout << cnt << "("<<msg<<") : " << *it << endl;
        cnt++;
    }
}

int main()
{
	vector<int> v = {5,3,-2,1,-4};
    auto abscmp = [](int l, int r){return abs(l) < abs(r);};
    print_vector(v,string{"original"});
    //=======Sort O(nlogn)========
    //정방향 Sort
    vector<int> v_normal = v;
    sort(v_normal.begin(), v_normal.end());
    //print_vector(v_normal,string{"normal"});

    //역방향 Sort
    vector<int> v_reverse = v;
    sort(v_reverse.begin(), v_reverse.end(),greater<int>{});
    //print_vector(v_reverse,string{"reverse"});

    //abs sort
    vector<int> v_abs = v;
    sort(v_abs.begin(), v_abs.end(),abscmp);
    //print_vector(v_abs,string{"abs"});

    //partial Sort
    vector<int> v_partial = v;
    partial_sort(v_partial.begin(), v_partial.begin()+2, v_partial.end());
    //print_vector(v_partial,string{"partial"});

    //=======nth element O(n)========
    //nth_element
    vector<int> v_nth = v;
    nth_element(v_nth.begin(), v_nth.begin()+2, v_nth.end());
    //print_vector(v_nth,string{"nth"});
    
    //find
    auto it = find(v.begin(),v.end(),-2);
    //cout<<"find value : "<<*it<<endl;
    it = find_if(v.begin(),v.end(),[](auto x){return x<-3;});
    //cout<<"find value : "<<*it<<endl;

    //swap, min, max
    vector<int> v_swap = v;
    //print_vector(v_swap,string{"swap"});
    swap(v_swap, v_reverse);
    //print_vector(v_swap,string{"swap"});
    swap(v_swap, v_reverse);
    swap(*v_swap.begin(), *(v_swap.begin()+2));
    //print_vector(v_swap,string{"swap"});

    pair<int,int> Min_Max = minmax(*v.begin(), *(v.begin()+2));
    //cout <<"Min : "<<Min_Max.first<<", Max : "<< Min_Max.second<<endl;
    
    //element indexing(bound 이전 Sort 작업 필수)
    print_vector(v_normal,string{"normal"});
    it = lower_bound(v_normal.begin(),v_normal.end(),1);
    cout << "lower_bound(1) : "<<(*it)<<endl;
    it = upper_bound(v_normal.begin(),v_normal.end(),1);
    cout << "upper_bound(1) : "<<*it<<endl;
    it = max_element(v_normal.begin(),v_normal.end());
    cout<<"max : "<< *it<<endl;
    it = min_element(v_normal.begin(),v_normal.end());
    cout<<"min : "<< *it<<endl;

    //for each?
    cout<<"for each"<<endl;
    int cnt = 1;
    for_each(v.begin(),v.end(),[&](int x)
    {
        //cout<<cnt<<" : " <<x<<endl;
        cnt++;
    });
    //range based loop
    cout<<"range based loop"<<endl;
    cnt = 1;
    for(auto &it:v)
    {
        //cout<<cnt<<" : " <<it<<endl;
        cnt++;
    }
    //count
    cnt = count(v.begin(),v.end(),-2);
    cout<<"num of -2 : "<<cnt<<endl;
    cnt = count_if(v.begin(),v.end(),[](auto x){return x<0;});
    cout<<"0미만 수 : " <<cnt<<endl;
    //remove
    vector<int> v_remove = v;
    cout<<"remove num of -2"<<endl;
    it = remove(v_remove.begin(),v_remove.end(),-2);
    v_remove.erase(it,v_remove.end());
    print_vector(v_remove, "remove");

    v_remove = v;
    cout<<"remove 0미만 수"<<endl;
    it = remove_if(v_remove.begin(),v_remove.end(),[](auto x){return x<0;});
    v_remove.erase(it,v_remove.end());
    print_vector(v_remove, "remove");
    return 0;
}