#include <iostream>
using namespace std;

//Template
template<class T>
struct Data { T a, b;};

int main()
{
	Data<int> A;
	A.a = 1;
	//cout << A.a << endl;
	//range based for loop
	int arr[5] = {1,2,3,4,5};
	for(auto& i: arr){
		//cout << i <<">>";
		i++;
		//cout << i << endl;
	}
	//initializer list
	int arr2[5]{1,2,3,4,5};
	//cout<<arr2[2]<<endl;

	//memset
	int arr3[5]{1,2,3,4,5};
	int cnt = 0;
	int arr4[] = {0,0,0,0,0};
	memcpy(arr4,arr3,sizeof(arr3));
	memset(arr3,0,sizeof(arr3));
	
	for(auto& i: arr3){
		//cout <<cnt <<"(arr3) : " << i << endl;
		cnt++;
	}
	
	cnt = 0;
	for(auto& i: arr4){
		//cout <<cnt <<"(arr4) : " << i << endl;
		cnt++;
	}
	//lambda
	auto sum_n =[](int n){
		int sum=0;
		for(int i =1;i<=n;i++) sum +=i;
		return sum;
	};
	cout<<sum_n(10)<<endl;
	return 0;
}