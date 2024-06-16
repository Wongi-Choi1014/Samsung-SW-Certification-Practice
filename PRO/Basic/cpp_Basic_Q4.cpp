/*
������ ����ħ
1. include ���̱�
2. ����� ����ȭ1 : ios::sync_with_stdio(0);cin.tie(0); (�̰� �Ⱦ��Ÿ� Scanf printf)
3. ������� ����ȭ2 : endl�� �����ʱ�
4. �����Ҵ� Ȱ���ϱ�
5. Array > Vector �ð�����
6. Array �⺻���� 0��
7. �ִ��� ���� ���̰� �������̱�(����� Sum��, input���� �迭 ������ �ذ��ϴ� ��� ��)
*/
#include <iostream>
//#include <vector>
//#include <algorithm>
#include <cstdio>
//#include <string>

using namespace std;

int main(){
#ifdef _WIN32
    freopen("input_Q4.txt", "r", stdin);
#endif // _WIN32
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N, M, ipt;
    int sri, sci, eri, eci;
    //long long presum_2D = 0;

    //vector<vector<long long>> A;
    //scanf("%d", &N);
    cin>>N;
    //long long A[1001][1001];
    long long **A = new long long *[N+1];
    for(int i=0;i<N+1;i++)
        A[i] = new long long[N+1];
    
    //vector<long long> A2;
    /*
    for(int i=0; i<N+1; i++)
    {
        A2.push_back(0);
    }
    */
    /*
    //0�Ҵ� �ʿ����
    for(int i=0; i<N+1; i++)
    {
        //A2.push_back(0);
        A[0][i]=0;
    }
    */
    //A.push_back(A2);

    for(int i=1; i<=N; i++)
    {
        //vector<long long> A2;
       // A2.push_back(0);
        //0�Ҵ� �ʿ����
        //A[i]=0;
        for(int j=1; j<=N; j++)
        {
            //cin>>ipt;
            //scanf("%d", &ipt);
            //scanf("%lld", &A[i][j]);
            cin>>A[i][j];
            //A2.push_back(ipt+A[i-1][j]+A2[j-1]-A[i-1][j-1]);
            //A[i][j] = ipt + A[i-1][j] + A[i][j-1] - A[i-1][j-1];
            A[i][j] += A[i-1][j] + A[i][j-1] - A[i-1][j-1];
        }
        //A.push_back(A2);
    }
    cin>>M;
    //scanf("%d",&M);

    for(int i=0; i<M; i++)
    {
        cin >> sri >> sci >> eri >> eci;
        //scanf("%d %d %d %d", &sri, &sci, &eri, &eci);
        
        sri--,sci--;
        //printf("%lld\n", A[eri][eci]-A[sri][eci]-A[eri][sci]+A[sri][sci]);
        cout << A[eri][eci]-A[sri][eci]-A[eri][sci]+A[sri][sci]<<'\n';

        //presum_2D = A[eri][eci]-A[sri][eci]-A[eri][sci]+A[sri][sci];
        //printf("%lld\n", presum_2D);
        //cout << presum_2D<<endl;
    }

    
    return 0;
}