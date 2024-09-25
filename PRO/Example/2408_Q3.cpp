#define MAX_SIZE	1000
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int Star_Map[MAX_SIZE][MAX_SIZE];//TC에서 받은 Star Raw Data
int Find_Map[MAX_SIZE][MAX_SIZE];//해당 좌표를 DFS에서 찾았는지
long long Star_Index_Map[MAX_SIZE][MAX_SIZE];//각 좌표에 맞게 Star Hash값 지정
int My_N = 0;
int star_count = 0;
bool end_point;
//int star_count_dfs = 0;
unordered_map<unsigned long long, vector<int>> Star;//Star Hash에 맞는 중앙값


void Set_Find_Map(int mRow, int mCol, unsigned long long hash_value)
{
	for (int r = mRow; r < mRow + 5; r++) {
		for (int c = mCol; c < mCol + 5; c++)
		{
			Find_Map[r][c] = 1;
			Star_Index_Map[r][c] = hash_value;
		}
	}
}
void Unset_Find_Map(int mRow, int mCol)
{
	for (int r = mRow; r < mRow + 5; r++) {
		for (int c = mCol; c < mCol + 5; c++)
		{
			Find_Map[r][c] = 0;
			Star_Index_Map[r][c] = 0;
		}
	}
}

bool Check_Corner_Region1(int mRow, int mCol)
{
	if (mRow >= (My_N - 4))
		return false;
	if (mCol < 0 || mCol >= My_N)
		return false;
	return true;
}

bool Is_Star_Piece(int mRow, int mCol, int &star_count_in_piece, unsigned long long hash_value[], int &cooldinate)
{

	bool Region1, Region2, Region3, Region4;
	//Region1은 이미 정의
	Region1 = true; Region2 = false; Region3 = false; Region4 = false;
	for (int r = mRow; r < mRow + 5; r++)
	{
		for (int c = mCol; c < mCol + 5; c++)
		{
            if(Find_Map[r][c])
                return false;
			if (Star_Map[r][c])
			{
				star_count_in_piece += 1;
				if (c == mCol)
					Region2 = true;
				else if (c == mCol + 4)
					Region4 = true;
				if (r == mRow + 4)
					Region3 = true;
			}
			//요거 나중에 체크필요함
			hash_value[0] = (hash_value[0] * 2) + Star_Map[r][c];
			hash_value[1] = (hash_value[1] * 2) + Star_Map[mRow + (c-mCol)][mCol + (4 - (r-mRow))];
			hash_value[2] = (hash_value[2] * 2) + Star_Map[mRow + (4 - (r-mRow))][mCol + (4 - (c - mCol))];
			hash_value[3] = (hash_value[3] * 2) + Star_Map[mRow + (4 - (c - mCol))][mCol + (r-mRow)];
		}
	}
	//좌표
	cooldinate = (mRow + 2) * 10000 + (mCol + 2);
	if (star_count_in_piece == 7 && Region1 && Region2 && Region3 &&Region4)
		return true;
	return false;
}

void push_hash(unsigned long long hash_value[], int cooldinate)
{
	if (Star.count(hash_value[0]))
	{
		for (int i = 0; i < 4; i++)
        {
            if(find(Star[hash_value[i]].begin(),
                    Star[hash_value[i]].end(),
                    cooldinate)==Star[hash_value[i]].end())
			    Star[hash_value[i]].push_back(cooldinate);
        }
	}
	else
	{
		vector<int> cooldinate_list_new{ cooldinate };
		for (int i = 0; i < 4; i++)
			Star[hash_value[i]] = cooldinate_list_new;
	}
}

void pop_hash(unsigned long long hash_value[], int cooldinate)
{
	if (Star.count(hash_value[0]))
	{
		for (int i = 0; i < 4; i++)
		{
			auto it = find(Star[hash_value[i]].begin(), Star[hash_value[i]].end(), cooldinate);
			if (it != Star[hash_value[i]].end())
				Star[hash_value[i]].erase(it);
		}
	}
}


void DFS(int mRow, int mCol, int star_count_dfs)
{
	for (int r = mRow; r < My_N - 4; r++) {//Region1 기준
		for (int c = 0; c < My_N; c++)
		{
			if ((!Find_Map[r][c]) && Star_Map[r][c])
			{
				//Region1 영역 내 존재 Check
				for (int sub_c = c - 4; sub_c <= c; sub_c++)
				{
					if (Check_Corner_Region1(r, sub_c))
					{
						int star_count_in_piece = 0;
						unsigned long long hash_value[4]{0,0,0,0};
						int cooldinate=0;
						if (Is_Star_Piece(r, sub_c, star_count_in_piece, hash_value, cooldinate))
						{
							Set_Find_Map(r, sub_c, hash_value[0]);
							push_hash(hash_value, cooldinate);
                            star_count_dfs += star_count_in_piece;
                            if (star_count_dfs == star_count)
                            {
                                end_point = true;
                                return;
                            }
                            break;
							//DFS(r, 0, star_count_dfs + star_count_in_piece);
                            //if (end_point == true)
		                    //    return;
							//pop_hash(hash_value, cooldinate);
							//Unset_Find_Map(r, sub_c);
						}
					}
				}
			}
		}
	}
	return;
}

void init(int N, int mPlane[MAX_SIZE][MAX_SIZE])
{

	My_N = N;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++)
		{
			Star_Map[r][c] = mPlane[r][c];
			star_count += mPlane[r][c];
            Find_Map[r][c]=0;
            Star_Index_Map[r][c]=0;
		}
	}
    end_point = false;
    Star.clear();
	DFS(0, 0, 0);
}

int getCount(int mPiece[5][5])
{
	unsigned long long hash_value = 0;
	for (int r = 0; r < 5; r++)
		for (int c = 0; c < 5; c++)
			hash_value = (hash_value * 2) + mPiece[r][c];
    if (Star.count(hash_value))
    {
        //cout<<Star[hash_value].size()<<'\n';
	    return Star[hash_value].size();
    }
    //cout<<0<<'\n';
    return 0;
}

int getPosition(int mRow, int mCol)
{
	if (Star.count(Star_Index_Map[mRow][mCol]))
    {
        //cout<<Star[Star_Index_Map[mRow][mCol]][0]<<'\n';
		return Star[Star_Index_Map[mRow][mCol]][0];
    }

	return 0;
}

//main

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAX_SIZE	1000
extern void init(int N, int mPlane[MAX_SIZE][MAX_SIZE]);
extern int getCount(int mPiece[5][5]);
extern int getPosition(int mRow, int mCol);

#define CMD_INIT		0
#define CMD_CNT			1
#define CMD_POSITION	2

static int Map[MAX_SIZE][MAX_SIZE];
static int Piece[5][5];
static int Data[40000];

static void init_map(int N)
{
	int idx = 0;

	int x = 0;
	for (int i = 0; i < (N / 25); i++) {
		for (int y = 0; y < N; y++) {
			int data = Data[idx++];
			int bit = 1;
			for (int m = 0; m < 25; m++) {
				if ((data & bit) != 0) Map[y][x + m] = 1;
				else Map[y][x + m] = 0;
				bit <<= 1;
			}
		}
		x += 25;
	}

	int dcnt = N % 25;
	if (dcnt != 0) {
		for (int y = 0; y < N; y++) {
			int data = Data[idx++];
			int bit = 1;
			for (int m = 0; m < dcnt; m++) {
				if ((data & bit) != 0) Map[y][x + m] = 1;
				else Map[y][x + m] = 0;
				bit <<= 1;
			}
		}
	}
}

static void make_piece(int data)
{
	int bit = 1;
	for (int i = 0; i < 5; i++) {
		for (int k = 0; k < 5; k++) {
			if ((data & bit) != 0) Piece[i][k] = 1;
			else Piece[i][k] = 0;
			bit <<= 1;
		}
	}
}

static bool run()
{
	int Q, N, row, col, cnt;
	int ret, ans;

	bool ok = false;

	scanf("%d", &Q);
	for (int q = 0; q < Q; q++)
	{
		int cmd;
		scanf("%d", &cmd);
		if (cmd == CMD_INIT)
		{
			scanf("%d %d", &N, &cnt);
			for (int i = 0; i < cnt; i++) scanf("%d", &Data[i]);
			init_map(N);
			init(N, Map);
			ok = true;
		}
		else if (cmd == CMD_CNT)
		{
			scanf("%d", &Data[0]);
			make_piece(Data[0]);
			ret = getCount(Piece);
			scanf("%d", &ans);
			if (ans != ret) {
				ok = false;
			}
		}
		else if (cmd == CMD_POSITION)
		{
			scanf("%d %d", &row, &col);
			ret = getPosition(row, col);
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
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	freopen("sample_input_Q3.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}