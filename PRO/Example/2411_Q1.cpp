//main.cpp

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int N, int K, int mId[], int sCity[], int eCity[], int mCost[]);
extern void add(int mId, int sCity, int eCity, int mCost);
extern void remove(int mId);
extern int cost(int sCity, int eCity);

/////////////////////////////////////////////////////////////////////////

#define MAX_K 1000
#define CMD_INIT 100
#define CMD_ADD 200
#define CMD_REMOVE 300
#define CMD_COST 400

static bool run() {
	int q;
	scanf("%d", &q);

	int n, k;
	int mIdArr[MAX_K], sCityArr[MAX_K], eCityArr[MAX_K], mCostArr[MAX_K];
	int mId, sCity, eCity, mCost;
	int cmd, ans, ret = 0;
	bool okay = false;

	for (int i = 0; i < q; ++i) {
		scanf("%d", &cmd);
		switch (cmd) {
			case CMD_INIT:
				okay = true;
				scanf("%d %d", &n, &k);
				for (int j = 0; j < k; ++j) {
					scanf("%d %d %d %d", &mIdArr[j], &sCityArr[j], &eCityArr[j], &mCostArr[j]);
				}
				init(n, k, mIdArr, sCityArr, eCityArr, mCostArr);
				break;
			case CMD_ADD:
				scanf("%d %d %d %d", &mId, &sCity, &eCity, &mCost);
				add(mId, sCity, eCity, mCost);
				break;
			case CMD_REMOVE:
				scanf("%d", &mId);
				remove(mId);
				break;
			case CMD_COST:
				scanf("%d %d %d", &sCity, &eCity, &ans);
				ret = cost(sCity, eCity);
				if (ans != ret)
					okay = false;
				break;
			default:
				okay = false;
				break;
		}
	}
	return okay;
}

int main() {
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}

//user.cpp
#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>

using namespace std;
struct Road{
    int Road_ID;
    int Road_Cost;
};

struct Road_index{
    int sCity;
    int eCity;
};

struct dist{
    int min_cost;
    int max_cost;
    int value;
};

int My_N,My_K;
Road Road_Arr[400][400];
unordered_map<int,Road_index> Current_Road;
//multiset<int,vector<int>,greater<int>()> result;
multiset<int,greater<int>> result;

//dijkstra 변수 start
#define INF 100000

int pre[400];
int visit[400];
dist dist_Arr[400];
void dijkstra(int sCity, int eCity);
//dijkstra 변수 end

void init(int N, int K, int mId[], int sCity[], int eCity[], int mCost[]) {
	My_N=N;
    My_K=K;
    for(int i=0;i<K;i++)
    {
        Road_Arr[sCity[i]][eCity[i]].Road_ID = mId[i];
        Road_Arr[sCity[i]][eCity[i]].Road_Cost = mCost[i];
        Current_Road[mId[i]]={sCity[i],eCity[i]};
    }

    for(int i=0;i<N+1;i++)
    {
        for(int j=0;j<N+1;j++)
        {
            Road_Arr[i][j].Road_ID = 0;
            Road_Arr[i][j].Road_Cost = 0;
        }
    }

    return;
}

void add(int mId, int sCity, int eCity, int mCost) {
	Road_Arr[sCity][eCity].Road_ID = mId;
    Road_Arr[sCity][eCity].Road_Cost = mCost;
    My_K++;
    Current_Road[mId]={sCity,eCity};
    return;
}

void remove(int mId) {
    int sCity = Current_Road[mId].sCity;
    int eCity = Current_Road[mId].eCity;
    Road_Arr[sCity][eCity].Road_ID = 0;
    Road_Arr[sCity][eCity].Road_Cost = 0;
    Current_Road.erase(mId);
    My_K--;
	return;
}

int cost(int sCity, int eCity) {
	int i;
	int j;
	int from;
	int to;
	int value;

    int Max_Cost=-1, Min_Cost=-1;
    for (i = 1; i <= My_N; i++)
    {
        dist_Arr[i].value = INF;
        dist_Arr[i].min_cost = 0;
        dist_Arr[i].max_cost = 0;
        visit[i] = 0;
        pre[i] = -1;
    }

    dijkstra(sCity, eCity);
    /*
    auto first = result.begin(); 
    if (first != result.end()) 
    { 
        Max_Cost =  *first; 
    } // Access the last element 
    
    auto last = result.end(); 
    if (last != result.begin()) 
    { 
        --last; // Move iterator to the last element 
        Min_Cost = *last; 
    }
    */
    int result_value = dist_Arr[eCity].value;
    if(result_value<500)
        return result_value; 
	return -1;
}

void dijkstra(int sCity, int eCity)
{
    int i;
	int j;
	int min;
	int v;

	dist_Arr[sCity].value = 0;

	for (i = 1; i <= My_N; i++)
	{
		min = INF;

		for (j = 1; j <= My_N; j++)
		{
			if (visit[j] == 0 && min > dist_Arr[j].value)
			{
				min = dist_Arr[j].value;
				v = j;
			}
		}

		visit[v] = 1;
		
		
		for (j = 1; j <= My_N; j++)
		{
			if (j == v) continue;
			if (Road_Arr[v][j].Road_Cost == 0) continue;
            
            int next_cost;
			if(Road_Arr[v][j].Road_Cost>dist_Arr[v].max_cost)
            {
                next_cost = Road_Arr[v][j].Road_Cost - dist_Arr[v].min_cost;
                if (dist_Arr[j].value > next_cost)
                {
                    dist_Arr[j].value = next_cost;
                    dist_Arr[j].max_cost = Road_Arr[v][j].Road_Cost;
                    if( pre[j] != -1)
                        pre[j] = v;
                }
            }
            else if(Road_Arr[v][j].Road_Cost<dist_Arr[v].min_cost)
            {
                next_cost = dist_Arr[v].max_cost - Road_Arr[v][j].Road_Cost;
                if (dist_Arr[j].value > next_cost)
                {
                    dist_Arr[j].value = next_cost;
                    dist_Arr[j].min_cost = Road_Arr[v][j].Road_Cost;
                    if( pre[j] != -1)
                        pre[j] = v;
                }
            }
            else
            {
                next_cost = dist_Arr[v].value;
                if (dist_Arr[j].value > next_cost)
                {
                    dist_Arr[j].value = next_cost;
                    if( pre[j] != -1)
                        pre[j] = v;
                }
            }
                
		}
	}
}
