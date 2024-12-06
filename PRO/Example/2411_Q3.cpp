//main.cpp
//map begin iterator -- ops -> error

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int N);
extern int build(int mLength);
extern int demolish(int mAddr);

#define CMD_INIT 1
#define CMD_BUILD 2
#define CMD_DEMOLISH 3

static bool run()
{
    int query_num;
    scanf("%d", &query_num);

    int ans;
    bool ok = false;

    for (int q = 0; q < query_num; q++)
    {
        int query;
        scanf("%d", &query);
        if (query == CMD_INIT)
        {
            int N;
            scanf("%d", &N);
            init(N);
            ok = true;
        }
        else if (query == CMD_BUILD)
        {
            int mLength;
            scanf("%d", &mLength);
            int ret = build(mLength);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
        else if (query == CMD_DEMOLISH)
        {
            int mAddr;
            scanf("%d", &mAddr);
            int ret = demolish(mAddr);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
    }
    return ok;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("sample_input_2411_Q3.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);
    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}

//user.cpp

#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
map<int,int> Building; //key : addr, Value : length
map<int, set<int>, greater<int>> Empty_Space; //key : length, Value : addr array //reverse

map<int, int> Empty_Building; //key : addr, Value : length
int My_N;

void init(int N) {
	My_N = N;
	Building.clear();
    Empty_Building.clear();
	Empty_Space.clear();

	int Empty_mAddr = 0;
	int Empty_mLength = My_N;
	Empty_Space[Empty_mLength].insert(Empty_mAddr);
	Empty_Building[Empty_mAddr] = Empty_mLength;
	//is_empty_building = true;
}

int build(int mLength) {
	//bool is_empty_building=false;
	//int First_mAddr, First_mLength;
	//int Second_mAddr, Second_mLength;
	//int Empty_mAddr, Empty_mLength;

	int Target_mAddr=-1;
	int Target_mLength = -1;
	/*
	for (auto it = Building.begin(); it != Building.end(); it++)
	{
		//left Corner
		if (it == Building.begin())
		{
			Second_mAddr = (*it).first;
			Second_mLength = (*it).second;
			if(Second_mAddr>0)
			{
				Empty_mAddr = 0;
				Empty_mLength = Second_mAddr;
				if (Empty_Space[Empty_mLength].size() == 0)
					Empty_Space[Empty_mLength] = { Empty_mAddr };
				else
					Empty_Space[Empty_mLength].push_back(Empty_mAddr);
				Empty_Building[Empty_mAddr] = Empty_mLength;
			}
			continue;
		}

		First_mAddr = Second_mAddr;
		First_mLength = Second_mLength;

		Second_mAddr = (*it).first;
		Second_mLength = (*it).second;

		Empty_mAddr = First_mAddr + First_mLength;
		Empty_mLength = Second_mAddr - Empty_mAddr;
		if (Empty_mLength > 0)
		{
			if (Empty_Space[Empty_mLength].size() == 0)
				Empty_Space[Empty_mLength] = { Empty_mAddr };
			else
				Empty_Space[Empty_mLength].push_back(Empty_mAddr);
			Empty_Building[Empty_mAddr] = Empty_mLength;
		}
	}

	//right Corner
	Empty_mAddr = Second_mAddr + Second_mLength;
	Empty_mLength = My_N - Empty_mAddr;
	if (Empty_mLength > 0)
	{
		if (Empty_Space[Empty_mLength].size() == 0)
			Empty_Space[Empty_mLength] = { Empty_mAddr };
		else
			Empty_Space[Empty_mLength].push_back(Empty_mAddr);
		Empty_Building[Empty_mAddr] = Empty_mLength;
		//Empty_Space[Empty_mLength] = Empty_mAddr;
	}
	*/
	for (auto it = Empty_Space.begin(); it != Empty_Space.end(); it++)
	{
		if ((*it).first < mLength)
			break;
		if ((*it).first >= Target_mLength)
		{
			Target_mAddr = *(*it).second.begin();
			Target_mLength = (*it).first;
			if ((*it).second.size() == 1)
				Empty_Space.erase(Target_mLength);
			else
				(*it).second.erase((*it).second.begin());
			//Empty_Building.erase(Empty_mAddr);

			break;
		}
	}
    /*
	for (auto it = Empty_Building.begin(); it != Empty_Building.end(); it++)
	{
		//if ((*it).second < mLength)
		//	break;
		if ((*it).second > Target_mLength && (*it).second >= mLength)
		{
			Target_mAddr = (*it).first;
			Target_mLength = (*it).second;
			//if ((*it).fi.size() == 1)
			//	Empty_Space.erase(Target_mLength);
			//else
			//	(*it).second.erase((*it).second.begin());
			

			//break;
		}
	}
    */
    
	int Original_mAddr = Target_mAddr;
	int Original_mLength = Target_mLength;

	if (Target_mAddr != -1)
	{
		Empty_Building.erase(Target_mAddr);

		Target_mAddr = Target_mAddr + (Target_mLength - 1) / 2;
		int Target_Remain = (Target_mLength - 1) % 2;
		if (Target_Remain == 0)
			Target_mAddr = Target_mAddr - (mLength / 2);
		else
			Target_mAddr = Target_mAddr - (mLength / 2) - (mLength % 2) + 1;
		Building[Target_mAddr] = mLength;
		
		//first
		if (Target_mAddr - Original_mAddr > 0)
		{

			Empty_Space[Target_mAddr - Original_mAddr].insert(Original_mAddr);
			Empty_Building[Original_mAddr] = Target_mAddr - Original_mAddr;
		}
		//second
		if ((Original_mAddr+ Original_mLength)-(Target_mAddr + mLength)>0)
		{

			Empty_Space[(Original_mAddr + Original_mLength) - (Target_mAddr + mLength)].insert((Target_mAddr + mLength));
			Empty_Building[(Target_mAddr + mLength)] = (Original_mAddr + Original_mLength) - (Target_mAddr + mLength);
		}
	}

	return Target_mAddr;
}

int demolish(int mAddr) {
	int mLength = -1;
	if (Building.find(mAddr) != Building.end()) {
		mLength = Building[mAddr];
		Building.erase(mAddr);
		auto first_it = (Empty_Building.lower_bound(mAddr));
        if (first_it != Empty_Building.end()) //normal
            --first_it;
        else if (first_it == Empty_Building.begin()) //begin
            //--first_it;
            first_it = Empty_Building.end();
        else//end position
            --first_it;
            //first_it=Empty_Building.begin();
		auto second_it = Empty_Building.upper_bound(mAddr);

		int Empty_mAddr = mAddr;
		int Empty_mLength = mLength;
		bool skip = false;
		if (first_it == second_it)
			skip = true;
		//first
		if ((first_it!= Empty_Building.end()) && ((first_it->first + first_it->second) == mAddr))
		{
			if (Empty_Space[first_it->second].size() == 1)
				Empty_Space.erase(first_it->second);
			else
				Empty_Space[first_it->second].erase(first_it->first);
			Empty_Building.erase(first_it);

			Empty_mAddr = first_it->first;
			Empty_mLength += first_it->second;
		}

		//second
		if (skip==false&&(second_it != Empty_Building.end()) && ((mAddr + mLength) == second_it->first))
		{
			if (Empty_Space[second_it->second].size() == 1)
				Empty_Space.erase(second_it->second);
			else
				Empty_Space[second_it->second].erase(second_it->first);
			Empty_Building.erase(second_it);

			Empty_mLength += second_it->second;
		}
        
        Empty_Space[Empty_mLength].insert(Empty_mAddr);
		Empty_Building[Empty_mAddr] = Empty_mLength;
		return mLength;
	}
	return -1;
}