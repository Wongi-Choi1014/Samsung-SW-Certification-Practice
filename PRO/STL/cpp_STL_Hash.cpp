#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

//hash function 정의
int k =26;

unsigned long long hashfunc(int key[]){
    unsigned long long hash = 0;
    for(int i=0;i<sizeof(key)/sizeof(int);i++)
        hash = hash * k+key[i];
    return hash;
}
//unordered set / map 사용 시 equal_to 정의 필요함
template<class T>
struct equal_to
{
    bool operator()(const T& lhs, const T& rhs) const {
        return lhs == rhs;
    }
};
//custom hash structure
struct Key{
    int x, y, z;
    bool operator==(const Key &r) const{
        return x == r.x && y == r.y && z == r.z;
    }
};

struct Hash_abc{
    size_t operator()(const Key &key) const{
        return key.x*26*26 + key.y*26 + key.z;
    }
};

int main()
{
    unordered_set<int> s;
    for(int i=0;i<=5;i++)
        s.insert(i);
    cout <<s.insert(5).second<<endl;
    s.erase(5);
    cout <<s.insert(5).second<<endl;
}