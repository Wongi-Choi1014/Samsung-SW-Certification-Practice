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
#include <map>
#include <vector>
#include <utility> 
#include <algorithm>
using namespace std;

struct Plant
{
	int Category=-1;
	int SowTime=-1;
	int GrowthTime=-1;
	int G_Size = -1;
};

map<int, map<int, Plant>> Current_Plant[32][32];
Plant Land[1005][1005];
int My_N;
int CurrentTime=0;
int GrowthTime[3];


void init(int N, int mGrowthTime[]) {
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	//cout.tie(0);
	
	for(int i=0;i<32;i++)
	{
		for(int j=0;j<32;j++)
			Current_Plant[i][j].clear();
	}
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			Land[i][j] = { -1,-1,-1,-1 };
	}

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

	if (Land[mRow][mCol].Category == -1)
	{
		Land[mRow][mCol] = sow_plant;
		Current_Plant[mRow/32][mCol/32][mRow][mCol] = sow_plant;
		return 1;
	}
	return 0;
}

int water(int mTime, int G, int mRow, int mCol, int mHeight, int mWidth) {
	CurrentTime = mTime;
	int water_count = 0;
	
	for(int i=mRow/32;i<=(mRow+mHeight)/32;i++)
	{
		for (int j = mCol/32; j <= (mCol+mWidth)/32; j++)
		{
			for (auto plant_x = Current_Plant[i][j].upper_bound(mRow - 1); plant_x != Current_Plant[i][j].upper_bound(mRow + mHeight - 1);) {
				for (auto plant_xy = plant_x->second.upper_bound(mCol - 1); plant_xy != plant_x->second.upper_bound(mCol + mWidth - 1);)
				{
					if (plant_x->first >= mRow && plant_x->first < mRow + mHeight)
					{
						if (plant_xy->first >= mCol && plant_xy->first < mCol + mWidth)
						{
							plant_xy->second.G_Size = plant_xy->second.G_Size + G;
							water_count++;
						}
					}
					++plant_xy;
				}
				++plant_x;
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
	for(int i=mRow/32;i<=(mRow+mHeight)/32;i++)
	{
		for (int j = mCol/32; j <= (mCol+mWidth)/32; j++)
		{
			for (auto plant_x = Current_Plant[i][j].upper_bound(mRow - 1); plant_x != Current_Plant[i][j].upper_bound(mRow + mHeight - 1);) {
				if (end_flag == true)
					break;
				for (auto plant_xy = plant_x->second.upper_bound(mCol - 1); plant_xy != plant_x->second.upper_bound(mCol + mWidth-1);)
				{
					if (plant_x->first >= mRow && plant_x->first < mRow + mHeight)
					{
						if (plant_xy->first >= mCol && plant_xy->first < mCol + mWidth)
						{
							int HarvestTime = mTime - plant_xy->second.SowTime;
							int G = plant_xy->second.G_Size;
							G += HarvestTime / plant_xy->second.GrowthTime;
							
							if (G < L)
							{
								end_flag = true;
								++plant_xy;
								break;
							}
							else
							{
								erase_arr.push_back({{i,j},{plant_x->first,plant_xy->first}});
								harvest_count++;
							}
						}
					}
					++plant_xy;
				}
				++plant_x;
			}
		}
	}
	if (end_flag == false)
	{
		for (const auto&it : erase_arr)
		{
			Current_Plant[it.first.first][it.first.second][it.second.first].erase(it.second.second);
			Land[it.second.first][it.second.second] = { -1,-1,-1,-1 };
		}
		return harvest_count;
	}
	return 0;
}