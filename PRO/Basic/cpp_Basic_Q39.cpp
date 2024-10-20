#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

#define Max_N 100;
int Subway_Graph[100][100];

int main()
{
    setbuf(stdout, NULL);
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    freopen("input_Q39.txt", "r", stdin);
    
    int N, M;
    scanf("%d%d", &N, &M);
 
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin>>Subway_Graph[i][j];
        }
    }
    return 0;
}