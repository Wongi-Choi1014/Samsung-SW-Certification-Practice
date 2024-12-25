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
	freopen("sample_input_2411_Q1.txt", "r", stdin);

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
#include <queue>

using namespace std;
struct Road{
    int Road_ID;
    int Road_Cost;
    int visit;
    int value;
};

struct Road_index{
    int sCity;
    int eCity;
};

struct dist{
    int min_cost;
    int max_cost;
    int value;
    int eCity;
    //작은순서 정렬
    bool operator<(const dist& d) const {
		return value > d.value;
	}
};

int My_N,My_K;
Road Road_Arr[400][400];
unordered_map<int,Road_index> Current_Road;
//multiset<int,vector<int>,greater<int>()> result;
//multiset<int,greater<int>> result;

//dijkstra 변수 start
#define INF 100000
#define Max_Cost 600

int min_cost_arr[400][600];
dist dist_Arr[400];
int dijkstra(int sCity, int eCity);

priority_queue<dist> pq;
//
int dijkstra_duplicated(int sCity, int eCity, int count);
int visit_duplicated[400];
//dijkstra 변수 end

void init(int N, int K, int mId[], int sCity[], int eCity[], int mCost[]) {
	My_N=N;
    My_K=K;

    for(int i=0;i<N+1;i++)
    {
        for(int j=0;j<N+1;j++)
        {
            Road_Arr[i][j].Road_ID = 0;
            Road_Arr[i][j].Road_Cost = 0;
            Road_Arr[i][j].visit = 0;
            Road_Arr[i][j].value = INF;
        }
    }

    for(int i=0;i<K;i++)
    {
        Road_Arr[sCity[i]][eCity[i]].Road_ID = mId[i];
        Road_Arr[sCity[i]][eCity[i]].Road_Cost = mCost[i];
        Current_Road[mId[i]]={sCity[i],eCity[i]};
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

    int result_value=500;
    pq={};

    for (i = 0; i < My_N; i++)
    {
        dist_Arr[i].value = INF;
        dist_Arr[i].min_cost = 0;
        dist_Arr[i].max_cost = 0;
        dist_Arr[i].eCity = i;

        for(j=0;j<Max_Cost;j++)
        {
            if(i==sCity)
                min_cost_arr[i][j] = 0;
            else
                min_cost_arr[i][j] = INF;
        }
    }
    //init condition
    for (j = 0; j < My_N; j++)
    {
        if (sCity == j) continue;
        if (Road_Arr[sCity][j].Road_Cost == 0) continue;

        min_cost_arr[j][Road_Arr[sCity][j].Road_Cost] = 0;
        dist_Arr[j].value = 0;
        dist_Arr[j].max_cost = Road_Arr[sCity][j].Road_Cost;
        dist_Arr[j].min_cost = Road_Arr[sCity][j].Road_Cost;
        
        pq.push(dist_Arr[j]);
                
    }
    
    result_value=dijkstra(sCity, eCity);
    

    if(result_value<500)
        return result_value; 
	return -1;
}

int dijkstra(int sCity, int eCity)
{
	int j;
    int result_value=500;
    
	//dist_Arr[sCity].value = 0;

	while(!pq.empty())
	{
        dist dist_c = pq.top();
        pq.pop();
        //visit[dist_c.eCity]=1;
		if(dist_c.eCity==eCity)
            return dist_c.value;
		for (j = 0; j < My_N; j++)
		{
			if (j == dist_c.eCity) continue;
			if (Road_Arr[dist_c.eCity][j].Road_Cost == 0) continue;
            //if(Road_Arr[dist_c.eCity][j].visit == 0)
            //    Road_Arr[dist_c.eCity][j].visit = 1;
            //else
             //   continue;
            //if (visit[dist_c.eCity]==1)
            int next_cost;
            //int prev_min_cost = dist_Arr[j].min_cost;

            if(Road_Arr[dist_c.eCity][j].Road_Cost>dist_c.max_cost)
            {
                next_cost = Road_Arr[dist_c.eCity][j].Road_Cost - dist_c.min_cost;
                dist_Arr[j].min_cost = dist_c.min_cost;
                dist_Arr[j].max_cost = Road_Arr[dist_c.eCity][j].Road_Cost;
            }
            
            else if(Road_Arr[dist_c.eCity][j].Road_Cost<dist_c.min_cost)
            {
                next_cost = dist_c.max_cost - Road_Arr[dist_c.eCity][j].Road_Cost;
                dist_Arr[j].min_cost = Road_Arr[dist_c.eCity][j].Road_Cost;
                dist_Arr[j].max_cost = dist_c.max_cost;
            }
            
            else
            {
                next_cost = dist_c.value;
                dist_Arr[j].min_cost = dist_c.min_cost;
                dist_Arr[j].max_cost = dist_c.max_cost;
            }


            if (min_cost_arr[j][dist_Arr[j].min_cost] > next_cost)
            {
                min_cost_arr[j][dist_Arr[j].min_cost] = next_cost;
                dist_Arr[j].value = next_cost;
                pq.push(dist_Arr[j]);
                //pq.push({dist_Arr[j].min_cost, dist_Arr[j].max_cost, dist_Arr[j].value, dist_Arr[j].eCity});
            }
            
		}
	}
    return -1;
}