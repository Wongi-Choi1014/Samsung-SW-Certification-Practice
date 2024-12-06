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

#include <iostream>
#include <algorithm>

using namespace std;

int MAX_N;

int Road[110][110];//Road 연결 유무
int Station[110];//들렸다 갔는지 유무
int Station2[110];//들렸다 갔는지 유무
int Station_Return_BIKE[110];//들렸다 갔는지 유무
int Bike_Station[110];//대여소 유무

pair<int, int> money_time_walk[110][110];//Money,Time Pair
pair<int, int> money_time_bike[110][110];
pair<int, int> money_time_taxi[110][110];

bool find_solution = false;//정답 찾았는지 flag
int solution_money = 0;//정답
int solution_time = 0;//시간초과 확인
int solution_minimum_money = 0;
void DFS(int mStartSpot, int mEndSpot, int mMaxTime);
void DFS2(int mStartSpot, int mEndSpot, int mMaxTime);
void DFS_Return_BIKE(int mStartSpot, int mEndSpot, int mMaxTime);

bool Taxi_Status = false;//택시 탔는지 flag
bool Bike_Status = false;//자전거 탔는지 flag
int Return_Bike_Status = 0;//도착지에 자전거 Station 없을경우(0=해당없음,1=자전거 Return 필요, 2=Return 후 복귀

void init(int N)
{
	MAX_N = N;
	for (int i = 0; i < N+1; i++)
	{
		for (int j = 0; j < N+1; j++)
		{
			Road[i][j] = -1;
			money_time_walk[i][j] = {-1, -1};
			money_time_bike[i][j] = {-1, -1};
			money_time_taxi[i][j] = {-1, -1};
		}
		Station[i] = 0;
		Station2[i] = 0;
		Station_Return_BIKE[i] = 0;
		Bike_Station[i] = 0;
	}
	find_solution = false;
	solution_money = 0;//정답
	solution_time = 0;//시간초과 확인
	solution_minimum_money = 0;

	Taxi_Status = false;
	Bike_Status = false;
	Return_Bike_Status = 0;
}

void addRoad(int K, int mSpotA[], int mSpotB[], int mDis[])
{
	for (int i = 0; i < K; i++)
	{
		Road[mSpotA[i]][mSpotB[i]] = mDis[i];
		Road[mSpotB[i]][mSpotA[i]] = mDis[i];
		money_time_walk[mSpotA[i]][mSpotB[i]] = { mDis[i] * 0, mDis[i] * 17 };
		money_time_bike[mSpotA[i]][mSpotB[i]] = { mDis[i] * 4, mDis[i] * 4 };
		money_time_taxi[mSpotA[i]][mSpotB[i]] = { mDis[i] * 19, mDis[i] * 1 };

		money_time_walk[mSpotB[i]][mSpotA[i]] = { mDis[i] * 0, mDis[i] * 17 };
		money_time_bike[mSpotB[i]][mSpotA[i]] = { mDis[i] * 4, mDis[i] * 4 };
		money_time_taxi[mSpotB[i]][mSpotA[i]] = { mDis[i] * 19, mDis[i] * 1 };
	}
}

void addBikeRent(int mSpot)
{
	Bike_Station[mSpot] = 1;
}

int getMinMoney(int mStartSpot, int mEndSpot, int mMaxTime)
{
	find_solution = false;
	solution_money = 0;//정답
	solution_time = 0;//시간초과 확인
	solution_minimum_money = 0;

	Taxi_Status = false;
	Bike_Status = false;
	Return_Bike_Status = 0;

	Station[mStartSpot] = 1;
	DFS(mStartSpot, mEndSpot, mMaxTime);
	Station[mStartSpot] = 0;

	if (find_solution == true)
	{
		//if(solution_minimum_money>500 || solution_minimum_money<5)
		//	return -1;
		return solution_minimum_money;
	}
	return -1;
}

void DFS(int mStartSpot, int mEndSpot, int mMaxTime)
{
	//결과 검증
	if (solution_time > mMaxTime)
		return;
	if (find_solution == true && solution_minimum_money < solution_money)
		return;
	if (mStartSpot == mEndSpot)
	{
		if (Bike_Status == true && Bike_Station[mEndSpot] == 0)
		{
			/*
			Station[mEndSpot] = 0;
			Return_Bike_Status = 1;
            Station_Return_BIKE[mEndSpot]=1;
            DFS_Return_BIKE(mStartSpot, mEndSpot, mMaxTime);
            Station[mEndSpot] = 1;
            Return_Bike_Status = 0;
            Station_Return_BIKE[mEndSpot]=0;
            return;*/
		}
		else{
			if (find_solution == false)
			{
				find_solution = true;
				solution_minimum_money = solution_money;
			}
			if(solution_minimum_money >solution_money)
				solution_minimum_money = solution_money;
			return;
		}
		
	}

	//DFS Search
	for (int i = 1; i < MAX_N + 1; i++)
	{
		//Bike 반납 필요 없음

        //Return_Bike_Status==1||
        //
		if (Station[i] != 1 && Road[mStartSpot][i]>-1)
		{
			
			//Station[i] = 1;
			//Walk
			Station[i] = 1;
			if (Bike_Status == true && Bike_Station[mStartSpot] == 1)
			{
				Bike_Status = false;
				solution_time += money_time_walk[mStartSpot][i].second;

				DFS(i, mEndSpot, mMaxTime);

				solution_time -= money_time_walk[mStartSpot][i].second;
				Bike_Status = true;
			}
			if(Bike_Status == false)
			{
				bool tmp_taxi = false;
				if (Taxi_Status == true)
				{
					Taxi_Status = false;
					tmp_taxi = true;
				}

				solution_time += money_time_walk[mStartSpot][i].second;

				DFS(i, mEndSpot, mMaxTime);

				solution_time -= money_time_walk[mStartSpot][i].second;

				if (tmp_taxi == true)
					Taxi_Status = true;
			}
				
			Station[i] = 0;
			//Bike
            //if(Return_Bike_Status ==0)
            //{
			if(Station_Return_BIKE[i]!=1)
			{
				Station_Return_BIKE[i] = 1;
				if (Bike_Status == true)
				{
					solution_money += money_time_bike[mStartSpot][i].first;
					solution_time += money_time_bike[mStartSpot][i].second;

					DFS(i, mEndSpot, mMaxTime);

					solution_money -= money_time_bike[mStartSpot][i].first;
					solution_time -= money_time_bike[mStartSpot][i].second;
				}
				if (Bike_Status == false && Bike_Station[mStartSpot] == 1)
				{
					bool tmp_taxi = false;
					if (Taxi_Status == true)
					{
						Taxi_Status = false;
						tmp_taxi = true;
					}
					Bike_Status = true;
					solution_money += money_time_bike[mStartSpot][i].first;
					solution_time += money_time_bike[mStartSpot][i].second;

					DFS(i, mEndSpot, mMaxTime);

					solution_money -= money_time_bike[mStartSpot][i].first;
					solution_time -= money_time_bike[mStartSpot][i].second;
					if (tmp_taxi == true)
						Taxi_Status = true;
					Bike_Status = false;
				}

				Station_Return_BIKE[i] = 0;
			}
            
			//Taxi
			Station[i] = 1;
			if (Bike_Status == true && Bike_Station[mStartSpot] == 1)
			{
				Bike_Status = false;
				Taxi_Status = true;

				solution_money += money_time_taxi[mStartSpot][i].first;
				solution_time += (money_time_taxi[mStartSpot][i].second+7);

				DFS(i, mEndSpot, mMaxTime);

				solution_money -= money_time_taxi[mStartSpot][i].first;
				solution_time -= (money_time_taxi[mStartSpot][i].second + 7);

				Bike_Status = true;
				Taxi_Status = false;
			}
			if(Taxi_Status==true)
			{
				solution_money += money_time_taxi[mStartSpot][i].first;
				solution_time += money_time_taxi[mStartSpot][i].second;

				DFS(i, mEndSpot, mMaxTime);

				solution_money -= money_time_taxi[mStartSpot][i].first;
				solution_time -= money_time_taxi[mStartSpot][i].second;
			}

			if(Taxi_Status==false && Bike_Status == false)
			{
				Taxi_Status = true;
				solution_money += money_time_taxi[mStartSpot][i].first;
				solution_time += (money_time_taxi[mStartSpot][i].second + 7);

				DFS(i, mEndSpot, mMaxTime);

				solution_money -= money_time_taxi[mStartSpot][i].first;
				solution_time -= (money_time_taxi[mStartSpot][i].second + 7);
				Taxi_Status = false;
			}

			Station[i] = 0;
		}
	}
}

void DFS_Return_BIKE(int mStartSpot, int mEndSpot, int mMaxTime)
{
	//결과 검증
	if (solution_time > mMaxTime)
		return;
	if (find_solution == true && solution_minimum_money < solution_money)
		return;
    /*
	if (mStartSpot == mEndSpot)
	{
        return;
        
		if (Bike_Status == true && Bike_Station[mEndSpot] == 0)
		{
			Station[mEndSpot] = 0;
			Return_Bike_Status = 1;
		}
		else {
			if (find_solution == false)
			{
				find_solution = true;
				solution_minimum_money = solution_money;
			}
			if(solution_minimum_money >solution_money)
				solution_minimum_money = solution_money;
			return;
		}
	}
    //*/
	//DFS Search
	for (int i = 1; i < MAX_N + 1; i++)
	{
		//Bike 반납 필요 없음
        //Station[i] != 1 && 
		if (Road[mStartSpot][i]>-1 && Station_Return_BIKE[i] !=1)
		{
            if (Bike_Station[i] == 1)
			{
				solution_money += money_time_bike[mStartSpot][i].first;
				solution_time += money_time_bike[mStartSpot][i].second;
                Station2[i] = 1;

				DFS2(i, mEndSpot, mMaxTime);

				solution_money -= money_time_bike[mStartSpot][i].first;
				solution_time -= money_time_bike[mStartSpot][i].second;
                Station2[i] = 0;
			}
			solution_money += money_time_bike[mStartSpot][i].first;
			solution_time += money_time_bike[mStartSpot][i].second;
			Station_Return_BIKE[i]=1;

			DFS_Return_BIKE(i, mEndSpot, mMaxTime);

			solution_money -= money_time_bike[mStartSpot][i].first;
			solution_time -= money_time_bike[mStartSpot][i].second;
			Station_Return_BIKE[i]=0;
		}
	}
}

void DFS2(int mStartSpot, int mEndSpot, int mMaxTime)
{
	//결과 검증
	if (solution_time > mMaxTime)
		return;
	if (find_solution == true && solution_minimum_money < solution_money)
		return;
	if (mStartSpot == mEndSpot)
	{
		if (Bike_Status == true && Bike_Station[mEndSpot] == 0)
		{
            return;
		}
		if (find_solution == false)
		{
			find_solution = true;
			solution_minimum_money = solution_money;
		}
		if(solution_minimum_money >solution_money)
			solution_minimum_money = solution_money;
		return;
	}

	//DFS Search
	for (int i = 1; i < MAX_N + 1; i++)
	{
		//Bike 반납 필요 없음

        //Return_Bike_Status==1||
        //
		if (Station2[i] != 1 && Road[mStartSpot][i]>-1)
		{
			
			Station2[i] = 1;
			//Walk

			if (Bike_Status == true && Bike_Station[mStartSpot] == 1)
			{
				Bike_Status = false;
				solution_time += money_time_walk[mStartSpot][i].second;

				DFS2(i, mEndSpot, mMaxTime);

				solution_time -= money_time_walk[mStartSpot][i].second;
				Bike_Status = true;
			}
			if(Bike_Status == false)
			{
				bool tmp_taxi = false;
				if (Taxi_Status == true)
				{
					Taxi_Status = false;
					tmp_taxi = true;
				}

				solution_time += money_time_walk[mStartSpot][i].second;

				DFS2(i, mEndSpot, mMaxTime);

				solution_time -= money_time_walk[mStartSpot][i].second;

				if (tmp_taxi == true)
					Taxi_Status = true;
			}
				
			/*
			//Bike
            //if(Return_Bike_Status ==0)
            //{
            if (Bike_Status == true)
            {
                solution_money += money_time_bike[mStartSpot][i].first;
                solution_time += money_time_bike[mStartSpot][i].second;

                DFS2(i, mEndSpot, mMaxTime);

                solution_money -= money_time_bike[mStartSpot][i].first;
                solution_time -= money_time_bike[mStartSpot][i].second;
            }
            if (Bike_Status == false && Bike_Station[mStartSpot] == 1)
            {
                bool tmp_taxi = false;
                if (Taxi_Status == true)
                {
                    Taxi_Status = false;
                    tmp_taxi = true;
                }
                Bike_Status = true;
                solution_money += money_time_bike[mStartSpot][i].first;
                solution_time += money_time_bike[mStartSpot][i].second;

                DFS2(i, mEndSpot, mMaxTime);

                solution_money -= money_time_bike[mStartSpot][i].first;
                solution_time -= money_time_bike[mStartSpot][i].second;
                if (tmp_taxi == true)
                    Taxi_Status = true;
                Bike_Status = false;
            }
            //}*/
			//Taxi
			if (Bike_Status == true && Bike_Station[mStartSpot] == 1)
			{
				Bike_Status = false;
				Taxi_Status = true;

				solution_money += money_time_taxi[mStartSpot][i].first;
				solution_time += (money_time_taxi[mStartSpot][i].second+7);

				DFS2(i, mEndSpot, mMaxTime);

				solution_money -= money_time_taxi[mStartSpot][i].first;
				solution_time -= (money_time_taxi[mStartSpot][i].second + 7);

				Bike_Status = true;
				Taxi_Status = false;
			}
			if(Taxi_Status==true)
			{
				solution_money += money_time_taxi[mStartSpot][i].first;
				solution_time += money_time_taxi[mStartSpot][i].second;

				DFS2(i, mEndSpot, mMaxTime);

				solution_money -= money_time_taxi[mStartSpot][i].first;
				solution_time -= money_time_taxi[mStartSpot][i].second;
			}

			if(Taxi_Status==false && Bike_Status == false)
			{
				Taxi_Status = true;
				solution_money += money_time_taxi[mStartSpot][i].first;
				solution_time += (money_time_taxi[mStartSpot][i].second + 7);

				DFS2(i, mEndSpot, mMaxTime);

				solution_money -= money_time_taxi[mStartSpot][i].first;
				solution_time -= (money_time_taxi[mStartSpot][i].second + 7);
				Taxi_Status = false;
			}

			Station2[i] = 0;
		}
	}
}