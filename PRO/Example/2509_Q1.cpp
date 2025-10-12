// main.cpp

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int N, int K, int sBuilding[], int eBuilding[], int mDistance[]);
extern void add(int sBuilding, int eBuilding, int mDistance);
extern int calculate(int M, int mCoffee[], int P, int mBakery[], int R);

/////////////////////////////////////////////////////////////////////////

#define MAX_E 30000
#define MAX_SHOP 1000
#define CMD_INIT 100
#define CMD_ADD 200
#define CMD_CALC 300

static bool run()
{
	int q;
	scanf("%d", &q);

	int n, k, m, p, r;
	static int sBuildingArr[MAX_E], eBuildingArr[MAX_E], mDistArr[MAX_E], mCoffee[MAX_SHOP], mBakery[MAX_SHOP];
	int sBuilding, eBuilding, mDist;
	int cmd, ans, ret = 0;
	bool okay = false;

	for (int i = 0; i < q; ++i)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT:
			okay = true;
			scanf("%d %d", &n, &k);
			for (int j = 0; j < k; ++j)
			{
				scanf("%d %d %d", &sBuildingArr[j], &eBuildingArr[j], &mDistArr[j]);
			}
			init(n, k, sBuildingArr, eBuildingArr, mDistArr);
			break;
		case CMD_ADD:
			scanf("%d %d %d", &sBuilding, &eBuilding, &mDist);
			add(sBuilding, eBuilding, mDist);
			break;
		case CMD_CALC:
			scanf("%d %d %d", &m, &p, &r);
			for (int j = 0; j < m; ++j)
			{
				scanf("%d", &mCoffee[j]);
			}
			for (int j = 0; j < p; ++j)
			{
				scanf("%d", &mBakery[j]);
			}
			ret = calculate(m, mCoffee, p, mBakery, r);
			scanf("%d", &ans);
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

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input_2509_Q1.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}

// user.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

int My_N;
int My_K;
int Distance_C, Distance_B;
int My_R;

struct Building
{
	vector<pair<int, int>> Edge; //{to(ID), distance}
	int type = -1;				 // 0: coffee, 1: bakery, -1: none
};

Building Current_Building[10005];
vector<int> visited_C, visited_B;
int all_visited_C[10005];
int all_visited_B[10005];
void bfs(int start, int condition); // condition 0: coffee, 1: bakery

void init(int N, int K, int sBuilding[], int eBuilding[], int mDistance[])
{
	My_K = K;
	My_N = N;
	// ensure proper size and clear previous data
	// Current_Building.clear();
	// Current_Building.resize(N + 1);
	for(int i=0;i<=N;i++){
		Current_Building[i].Edge.clear();
		Current_Building[i].type = -1;
	}

	for (int i = 0; i < K; i++)
	{
		int s = sBuilding[i];
		int e = eBuilding[i];
		int d = mDistance[i];

		Current_Building[s].Edge.push_back({d, e});
		Current_Building[e].Edge.push_back({d, s});
	}

	return;
}

void add(int sBuilding, int eBuilding, int mDistance)
{

	Current_Building[sBuilding].Edge.push_back({mDistance, eBuilding});
	Current_Building[eBuilding].Edge.push_back({mDistance, sBuilding});
	return;
}

int calculate(int M, int mCoffee[], int P, int mBakery[], int R)
{
	int score = -1;
	My_R =R;

	// all_visited_C.clear();
	// all_visited_B.clear();

	// all_visited_C.resize(My_N, R+1);
	// all_visited_B.resize(My_N, R+1);
	queue<int> q;
	for (int i = 0; i < My_N; i++)
	{
		Current_Building[i].type = -1;
		all_visited_C[i]= R+1;
		all_visited_B[i]= R+1;
	}
	for (int i = 0; i < M; i++)
	{
		int c = mCoffee[i];
		Current_Building[c].type = 0;
		q.push(c);
		//bfs(mCoffee[i],0);
	}
	for (int i = 0; i < P; i++)
	{
		int b = mBakery[i];
		Current_Building[b].type = 1;
		q.push(b);
		//bfs(mBakery[i],1);
	}
	
	
	
	
	while(!q.empty())
	{
		int i=q.front();
		q.pop();
		
		if (Current_Building[i].type != -1)
		{
			
			//visited_C.clear();
			//visited_B.clear();

			//visited_C.resize(My_N, R+1);
			//visited_B.resize(My_N, R+1);
			//Distance_B = R+1;
			//Distance_C = R+1;
			bfs(i,Current_Building[i].type);
			//if (Distance_B > My_R || Distance_C > My_R)
			//	score = -1;
			//if (Distance_B <= My_R && Distance_C <= My_R)
			//	if (Distance_B + Distance_C <score || score == -1)
			//		score = Distance_B + Distance_C;
		}

	}

	for (int i = 0; i < My_N; i++)
	{
		if (Current_Building[i].type == -1)
		{
			if (all_visited_B[i] <= My_R && all_visited_C[i] <= My_R)
				if (all_visited_B[i] + all_visited_C[i] <score || score == -1)
					score = all_visited_B[i] + all_visited_C[i];
		}

	}
	
	return score;
}

void bfs(int start, int condition) // condition 0: coffee, 1: bakery
{
	queue<pair<int,int>> q;//{distance, building}
	// 한 개의 참조로 적절한 visited 벡터를 가리키게 함
	// 방법1: 삼항 연산자로 참조 초기화
	int* visited = (condition == 0) ? all_visited_C : all_visited_B;
	// (또는 포인터 사용:
	//  vector<int>* pVisited = (condition==0) ? &visited_C : &visited_B;
	//  vector<int>& visited = *pVisited;
	// )
	q.push({0,start});
	visited[start] = 0;

	while (!q.empty()) {
		int cur = q.front().second;
		int dist = q.front().first;
		q.pop();
		if(dist>=My_R)
			break;

		if(dist> visited[cur])
			continue;
		

		for (const auto& edge : Current_Building[cur].Edge) {
			int next = edge.second;
			int nextDist = edge.first + dist;
			
			if(condition ==0){
				if(Current_Building[next].type ==0)
				{
					if(dist < Distance_C)
						Distance_C = dist;
					continue;
				}
			}

			if(condition ==1){
				if(Current_Building[next].type ==1)
				{
					if(dist < Distance_B)
						Distance_B = dist;
					continue;
				}
			}
			
			if (nextDist < visited[next]) {
				visited[next] = nextDist;
				q.push({nextDist,next});
				// Process the next building as needed
			}
		}
	}
	/*
	if(condition ==0){
		for(int i=0;i<My_N;i++){
			if(visited[i]<all_visited_C[i])
				all_visited_C[i]= visited[i];
		}
	}
	if(condition ==1){
		for(int i=0;i<My_N;i++){
			if(visited[i]<all_visited_B[i])
				all_visited_B[i]= visited[i];
		}
	}*/
}