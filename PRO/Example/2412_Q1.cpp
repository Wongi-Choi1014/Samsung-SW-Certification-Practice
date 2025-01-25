//main.cpp

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int N, int mLimit);
extern void addRadio(int K, int mID[], int mFreq[], int mY[], int mX[]);
extern int getMinPower(int mID, int mCount);

#define CMD_INIT		0
#define CMD_ADDRADIO	1
#define CMD_GETPOWER	2

#define MAX_RADIO		100

static bool run()
{
	int Q, N, K, Limit;
	int id[MAX_RADIO], freq[MAX_RADIO], my[MAX_RADIO], mx[MAX_RADIO];
	int ret, ans;

	bool ok = false;

	scanf("%d", &Q);
	for (int q = 0; q < Q; q++)
	{
		int cmd;
		scanf("%d", &cmd);
		if (cmd == CMD_INIT)
		{
			scanf("%d %d", &N, &Limit);
			init(N, Limit);
			ok = true;
		}
		else if (cmd == CMD_ADDRADIO)
		{
			scanf("%d", &K);
			for (int i = 0; i < K; i++) scanf("%d %d %d %d", &id[i], &freq[i], &my[i], &mx[i]);
			addRadio(K, id, freq, my, mx);
		}
		else if (cmd == CMD_GETPOWER)
		{
			scanf("%d %d", &id[0], &freq[0]);
			ret = getMinPower(id[0], freq[0]);
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
	freopen("sample_input_2412_Q1.txt", "r", stdin);

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
#include <vector>
#include <cmath>
#include <algorithm>
#include <memory>
#include <queue>
using namespace std;


struct Radio {
    int mID;
    int mFreq;
    int mY;
    int mX;
	Radio() : mID(0), mFreq(0), mY(0), mX(0) {}
    Radio(int id, int freq, int y, int x) : mID(id), mFreq(freq), mY(y), mX(x) {}
};

struct Node {
    Radio radio;
    std::shared_ptr<Node> left, right;
    Node(Radio radio) : radio(radio), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(const std::pair<int, Radio> &a, const std::pair<int, Radio> &b) {
        return a.first < b.first;
    }
};
std::priority_queue<std::pair<int, Radio>, std::vector<std::pair<int, Radio>>, Compare>  pq_same_freq;
std::priority_queue<std::pair<int, Radio>, std::vector<std::pair<int, Radio>>, Compare> pq_all;


class KDTree {
public:
    KDTree() : root(nullptr) {}

    void build(const std::vector<Radio> &radios) {
        root = build(radios, 0);
    }

    void insert(const Radio &radio) {
        root = insert(root, radio, 0);
    }

    void nearestNeighbor(const Radio &target, int K, int same_freq) {
        nearest(root, target, 0, root->radio, K, same_freq);
    }

	void clear() {
        clearRec(root);
        root.reset();
    }

private:
    std::shared_ptr<Node> root;

    std::shared_ptr<Node> build(std::vector<Radio> radios, int depth) {
        if (radios.empty()) return nullptr;
        int axis = depth % 2;
        std::sort(radios.begin(), radios.end(), [axis](const Radio &a, const Radio &b) {
            return axis == 0 ? a.mX < b.mX : a.mY < b.mY;
        });
        int mid = radios.size() / 2;
        std::shared_ptr<Node> node = make_shared<Node>(radios[mid]);
        std::vector<Radio> leftRadios(radios.begin(), radios.begin() + mid);
        std::vector<Radio> rightRadios(radios.begin() + mid + 1, radios.end());
        node->left = build(leftRadios, depth + 1);
        node->right = build(rightRadios, depth + 1);
        return node;
    }

    std::shared_ptr<Node> insert(std::shared_ptr<Node> node, const Radio &radio, int depth) {
        if (!node) return make_shared<Node>(radio);
        int axis = depth % 2;
        if (axis == 0) {
            if (radio.mX < node->radio.mX) node->left = insert(node->left, radio, depth + 1);
            else node->right = insert(node->right, radio, depth + 1);
        } else {
            if (radio.mY < node->radio.mY) node->left = insert(node->left, radio, depth + 1);
            else node->right = insert(node->right, radio, depth + 1);
        }
        return node;
    }

    void nearest(std::shared_ptr<Node> node, const Radio &target, int depth, Radio best, int K, int same_freq) {
        if (!node) return;//best;
        //int distBest = distance(target, best);
        int distNode = distance(target, node->radio);
        //if (distNode < distBest) best = node->radio;

		if(node->radio.mFreq!= same_freq){
			if (pq_all.size() < K) {
				pq_all.push({distNode, node->radio});
			}
			else if (distNode < pq_all.top().first) {
				pq_all.pop();
				pq_all.push({distNode, node->radio});
			}
		}
		else if(distNode!=0){
			if (pq_same_freq.size() < K) {
            	pq_same_freq.push({distNode, node->radio});
			}
			else if (distNode < pq_same_freq.top().first) {
				pq_same_freq.pop();
				pq_same_freq.push({distNode, node->radio});
			}
		}
		
        int axis = depth % 2;
        std::shared_ptr<Node> next = (axis == 0 ? target.mX < node->radio.mX : target.mY < node->radio.mY) ? node->left : node->right;
        std::shared_ptr<Node> other = (next == node->left) ? node->right : node->left;
		
        //best = 
		nearest(next, target, depth + 1, best,K,same_freq);
		/*
		int node_validation = std::abs((axis == 0 ? target.mX - node->radio.mX : target.mY - node->radio.mY));
		int pq_all_validation = pq_all.empty() ? -1 : pq_all.top().first;
		int pq_same_freq_validation = pq_same_freq.empty() ? -1 : pq_same_freq.top().first;
		int pq_validation = pq_all_validation> pq_same_freq_validation ? pq_all_validation : pq_same_freq_validation;
        if ((pq_all.size()<K||pq_all.size()<K)|| node_validation < pq_validation) {
            //best = 
			nearest(other, target, depth + 1, best,K,same_freq);
        }
		*/
		
		if (other && std::abs((axis == 0 ? target.mX - node->radio.mX : target.mY - node->radio.mY)) < 999) {
            nearest(other, target, depth + 1, best,K,same_freq);
        }
		
		
        return;//best;
    }

    int distance(const Radio &a, const Radio &b) {
		//return sqrt(pow(a.mX - b.mX, 2) + pow(a.mY - b.mY, 2));
        return abs(a.mX - b.mX) + abs(a.mY - b.mY);
	}
	void clearRec(std::shared_ptr<Node> node) {
        if (!node) return;
        clearRec(node->left);
        clearRec(node->right);
        node.reset();
    }
};

int My_N;
int My_Limit;
vector<Radio> points;
KDTree tree;


Radio Radio_List[51000];

void init(int N, int mLimit)
{
	My_N = N;
	My_Limit = mLimit;
	points.clear();
	for (int i = 0; i < 51000; i++)
	{
		Radio_List[i] = Radio(0, 0, 0, 0);
	}
	//tree.build(points);
	tree.clear();
}

void addRadio(int K, int mID[], int mFreq[], int mY[], int mX[])
{
	for(int i = 0; i < K; i++)
	{
		Radio_List[mID[i]] = Radio(mID[i], mFreq[i], mY[i], mX[i]);
		points.push_back(Radio(mID[i], mFreq[i], mY[i], mX[i]));
		tree.insert(Radio(mID[i], mFreq[i], mY[i], mX[i]));
	}
}

int getMinPower(int mID, int mCount)
{
	Radio target(Radio_List[mID]);
	tree.nearestNeighbor(target, mCount, target.mFreq);
	std::priority_queue<int,vector<int>,greater<int>> result;
	int power;
	int result_sum=0;
	while (!pq_all.empty()) {
		power = 1000+ (abs(pq_all.top().second.mX - target.mX) + abs(pq_all.top().second.mY - target.mY))*10;
		result.push(power);
		pq_all.pop();
	}

	while (!pq_same_freq.empty()) {
		power = (abs(pq_same_freq.top().second.mX - target.mX) + abs(pq_same_freq.top().second.mY - target.mY))*10;
		result.push(power);
		pq_same_freq.pop();
	}
	for(int i = 0; i < mCount; i++)
	{
		result_sum += result.top();
		result.pop();
	}

	return result_sum;
}