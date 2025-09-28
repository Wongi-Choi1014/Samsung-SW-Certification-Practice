//main.cpp

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CATEGORY_NUM	3

#define CMD_INIT        100
#define CMD_SOW			200
#define CMD_WATER    	300
#define CMD_HARVEST    	400

extern void init(int N, int mGrowthTime[]);
extern int sow(int mTime, int mRow, int mCol, int mCategory);
extern int water(int mTime, int G, int mRow, int mCol, int mHeight, int mWidth);
extern int harvest(int mTime, int L, int mRow, int mCol, int mHeight, int mWidth);

static bool run()
{
	int Q, ret, ans;
	int N, mGrowthTime[CATEGORY_NUM], mTime, mCategory, L, G, mRow, mCol, mHeight, mWidth;

	scanf("%d", &Q);
	bool okay = false;

	for (int q = 0; q < Q; ++q)
	{
		int cmd;
		scanf("%d", &cmd);
		switch (cmd) {
		case CMD_INIT:
			scanf("%d %d %d %d", &N, &mGrowthTime[0], &mGrowthTime[1], &mGrowthTime[2]);
			init(N, mGrowthTime);
			okay = true;
			break;
		case CMD_SOW:
			scanf("%d %d %d %d %d", &mTime, &mRow, &mCol, &mCategory, &ans);
			ret = sow(mTime, mRow, mCol, mCategory);
			if (ans != ret)
				okay = false;
			break;
		case CMD_WATER:
			scanf("%d %d %d %d %d %d %d", &mTime, &G, &mRow, &mCol, &mHeight, &mWidth, &ans);
			ret = water(mTime, G, mRow, mCol, mHeight, mWidth);
			if (ans != ret)
				okay = false;
			break;
		case CMD_HARVEST:
			scanf("%d %d %d %d %d %d %d", &mTime, &L, &mRow, &mCol, &mHeight, &mWidth, &ans);
			ret = harvest(mTime, L, mRow, mCol, mHeight, mWidth);
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
	freopen("sample_input_2508_Q1.txt", "r", stdin);

	int TC, MARK;

	scanf("%d %d", &TC, &MARK);
	for (int tc = 1; tc <= TC; ++tc)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}

//User
//Land ¹è¿­ »¬Áö Current Time »¬Áö °í¹Î

#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility> 
#include <algorithm>
#include <math.h>
using namespace std;

struct Plant
{
	int Category=-1;
	int SowTime=-1;
	int GrowthTime=-1;
	int G_Size = -1;
	int Row=-1;
	int Col=-1;
	//bool erase = false;
};

unordered_map<int, unordered_map<int, vector<Plant>>> Current_Plant;
Plant Land[1005][1005];
//unordered_map<int, unordered_map<int, bool>> Land;
int My_N;
int CurrentTime=0;
int GrowthTime[3];


void init(int N, int mGrowthTime[]) {
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	//cout.tie(0);
	Current_Plant.clear();
	// for(int i=0;i<100;i++)
	// {
	// 	for(int j=0;j<100;j++)
	// 		Current_Plant[i][j].clear();
	// }
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			Land[i][j] = { -1,-1,-1,-1,-1,-1};
	}
	//Land.clear();

	My_N = N;
	CurrentTime = 0;
	for (int i = 0; i < 3; i++)
		GrowthTime[i] = mGrowthTime[i];
}

int sow(int mTime, int mRow, int mCol, int mCategory) {
	CurrentTime = mTime;

	Plant sow_plant;
	sow_plant.Category = mCategory;
	sow_plant.SowTime = mTime;
	sow_plant.GrowthTime = GrowthTime[mCategory];
	sow_plant.G_Size = 0;
	sow_plant.Row = mRow;
	sow_plant.Col = mCol;

	//if (Land.find(mRow) == Land.end() || Land[mRow].find(mCol) == Land[mRow].end() || Land[mRow][mCol] == true)
	if (Land[mRow][mCol].Category == -1)
	{
		//Land[mRow][mCol] = false;
		Land[mRow][mCol] = sow_plant;
		Current_Plant[mRow/(My_N/10)][mCol/(My_N/10)].push_back(sow_plant);
		return 1;
	}
	return 0;
}

int water(int mTime, int G, int mRow, int mCol, int mHeight, int mWidth) {
	CurrentTime = mTime;
	int water_count = 0;
	
	for(int i=mRow/(My_N/10);i<=(mRow+mHeight-1)/(My_N/10);i++)
	{
		for (int j = mCol/(My_N/10); j <= (mCol+mWidth-1)/(My_N/10); j++)
		{
			for(auto& it: Current_Plant[i][j])
			{
				if (it.Row >= mRow && it.Row < mRow + mHeight)
				{
					if (it.Col >= mCol && it.Col < mCol + mWidth)
					//if (it.Col >= mCol && it.Col < mCol + mWidth && it.erase== false)
					{
						it.G_Size += G;
						water_count++;
					}
				}
			}
			
			
		}
	}
	//for (int row = mRow; row < mRow + mHeight; row++) {
	//	for (int col = mCol; col < mCol + mWidth; col++)
	
	return water_count;
}

int harvest(int mTime, int L, int mRow, int mCol, int mHeight, int mWidth) {
	CurrentTime = mTime;
	int harvest_count = 0;
	vector<pair<pair<int,int>,pair<int,int>>> erase_arr;

	bool end_flag = false;
	//int cnt;
	for(int i=mRow/(My_N/10);i<=(mRow+mHeight-1)/(My_N/10);i++)
	{
		for (int j = mCol/(My_N/10); j <= (mCol+mWidth-1)/(My_N/10); j++)
		{
			if (end_flag == true)
				break;
			//cnt=0;
			for(auto& it: Current_Plant[i][j])
			{	
				if (it.Row >= mRow && it.Row < mRow + mHeight)
				{
					if (it.Col >= mCol && it.Col < mCol + mWidth)
					//if (it.Col >= mCol && it.Col < mCol + mWidth && it.erase== false)
					{
						int HarvestTime = mTime - it.SowTime;
						int G = it.G_Size;
						G += HarvestTime / it.GrowthTime;
						
						if (G < L)
						{
							end_flag = true;
							break;
						}
						else
						{
							erase_arr.push_back({{i,j},{it.Row,it.Col}});
							harvest_count++;
						}
					}
				}
				//cnt++;
			}
		}
	}
	if (end_flag == false)
	{
		for (const auto&it : erase_arr)
		{
			Current_Plant[it.first.first][it.first.second].erase(remove_if(
				Current_Plant[it.first.first][it.first.second].begin(),
				Current_Plant[it.first.first][it.first.second].end(),
                  [&](const Plant& p) { return p.Row == it.second.first && p.Col == it.second.second; }),
        		Current_Plant[it.first.first][it.first.second].end()
			);
			//Current_Plant[it.first.first][it.first.second][it.second].erase = true;
			Land[it.second.first][it.second.second] = { -1,-1,-1,-1,-1,-1};
			//Land[Current_Plant[it.first.first][it.first.second][it.second].Row][Current_Plant[it.first.first][it.first.second][it.second].Col] = { -1,-1,-1,-1,-1,-1};
			//Land[Current_Plant[it.first.first][it.first.second][it.second].Row][Current_Plant[it.first.first][it.first.second][it.second].Col] = true;
		}
		return harvest_count;
	}
	return 0;
}