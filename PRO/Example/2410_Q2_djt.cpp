//main.cpp

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

extern void init(int N);
extern void addRoad(int K, int mSpotA[], int mSpotB[], int mDis[]);
extern void addBikeRent(int mSpot);
extern int getMinMoney(int mStartSpot, int mEndSpot, int mMaxTime);

#define CMD_INIT	0
#define CMD_ROAD	1
#define CMD_BIKE	2
#define CMD_MONEY	3

int spotA[30], spotB[30], dis[30];
static bool run()
{
	int Q, N, K;
	int maxTime;
	int ret, ans;

	bool ok = false;

	scanf("%d", &Q);
	for (int q = 0; q < Q; q++)
	{
		int cmd;
		scanf("%d", &cmd);
		if (cmd == CMD_INIT)
		{
			scanf("%d", &N);
			init(N);
			ok = true;
		}
		else if (cmd == CMD_ROAD)
		{
			scanf("%d", &K);
			for (int i = 0; i < K; i++) scanf("%d %d %d", &spotA[i], &spotB[i], &dis[i]);
			addRoad(K, spotA, spotB, dis);
		}
		else if (cmd == CMD_BIKE)
		{
			scanf("%d", &spotA[0]);
			addBikeRent(spotA[0]);
		}
		else if (cmd == CMD_MONEY)
		{
			scanf("%d %d %d", &spotA[0], &spotB[0], &maxTime);
			ret = getMinMoney(spotA[0], spotB[0], maxTime);
			scanf("%d", &ans);
			if (ans != ret) {
				ok = false;
			}
		}
		else ok = false;
	}
	return ok;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input_2410_Q2.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}

/*
Dijkstra
 : vertex를 (spot, time, type)로 확장
 : type에 따라 다르게 전파하기
*/

#include<vector>
#include<queue>
using namespace std;
using pii = pair<int, int>;
const int INF = 1e9;

int N;						// 지점 개수
enum { WALK, BIKE, TAXI };	// type = 0(walk), 1(bike), 2(taxi)

vector<pii> adj[105];		// 양방향 인접 배열
bool bike[105];				// bike[spot] = 1(자전거 대여소인 경우)/0
int C[105][505][3];			// C[spot][time][type] = minCost

struct Data {	// cost, (spot, time, type)
	int spot, cost, time, type;
	bool operator<(const Data& r) const {
		if (cost != r.cost) return cost > r.cost;
		return time > r.time;
	}
};
priority_queue<Data> pq;

void init(int N)
{
	::N = N;
	for (int i = 1; i <= N; i++) {
		bike[i] = 0;
		adj[i].clear();
	}
}

void addRoad(int K, int a[], int b[], int d[])
{
	for (int i = 0; i < K; i++) {
		adj[a[i]].push_back({ b[i],d[i] });
		adj[b[i]].push_back({ a[i],d[i] });
	}
}

void addBikeRent(int mSpot)
{
	bike[mSpot] = 1;
}

int maxTime;
void push(int spot, int cost, int time, int type) {
	if (time > maxTime) return;					// 제한 시간 넘어가는 경우
	if (C[spot][time][type] <= cost) return;	// 이전 값보다 비용이 큰 경우
	pq.push({ spot, cost, time, type });
	C[spot][time][type] = cost;
}

int getMinMoney(int s, int e, int maxTime)
{
	::maxTime = maxTime;

	// 초기화
	pq = {};
	for (int i = 1; i <= N; i++)
		for (int j = 0; j <= maxTime; j++)
			C[i][j][0] = C[i][j][1] = C[i][j][2] = INF;

	// 시작 위치에서 걷는 상태로 시작 (다른 type도 등록해도 되지만 안해도 된다)
	pq.push({ s, 0, 0, WALK });
	C[s][0][WALK] = 0;

	while (pq.size()) {
		Data d = pq.top();
		int spot = d.spot, cost = d.cost, time = d.time, type = d.type;
		pq.pop();
		if (C[spot][time][type] != cost) continue;				// 최신 정보 아닌 경우(이미 확정된 경우)

		// (spot, time, type) 상태의 비용이 cost로 확정된 상황

		// 확정된 상태가 목표지점이고, BIKE가 아니거나 BIKE이면서 반납 가능한 경우 종료
		if (spot == e && !(type == BIKE && !bike[spot]))
			return cost;

		for (pii p : adj[spot]) {
			int nspot = p.first;
			int dist = p.second;

			if (type == WALK) {
				push(nspot, cost, time + dist * 17, WALK);								// walk->walk
				if (bike[spot]) push(nspot, cost + dist * 4, time + dist * 4, BIKE);	// walk->bike
				push(nspot, cost + dist * 19, time + dist + 7, TAXI);					// walk->taxi
			}

			if (type == BIKE) {
				push(nspot, cost + dist * 4, time + dist * 4, BIKE);					// bike->bike
				if (bike[spot]) {
					push(nspot, cost, time + dist * 17, WALK);							// bike->walk
					push(nspot, cost + dist * 19, time + dist + 7, TAXI);				// bike->taxi
				}
			}
			if (type == TAXI) {
				push(nspot, cost, time + dist * 17, WALK);								// taxi->walk
				if (bike[spot]) push(nspot, cost + dist * 4, time + dist * 4, BIKE);	// taxi->bike
				push(nspot, cost + dist * 19, time + dist, TAXI);						// taxi->taxi
			}
		}
	}
	return -1;
}