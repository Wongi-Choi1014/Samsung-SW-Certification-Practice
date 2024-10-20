#include <stdio.h>

#define N 100
#define INF 100000

int map[N + 1][N + 1];
int pre[N + 1];
int visit[N + 1];
int dist[N + 1];
int vertex;
int edge;
int start;
int end;

void dijkstra(void)
{
	int i;
	int j;
	int min;
	int v;

	dist[start] = 0;

	for (i = 1; i <= vertex; i++)
	{
		min = INF;

		for (j = 1; j <= vertex; j++)
		{
			if (visit[j] == 0 && min > dist[j])
			{
				min = dist[j];
				v = j;
			}
		}

		visit[v] = 1;
		
		printf("unhighlihgt");
		
		for (j = 1; j <= vertex; j++)
		{
			if (j == v) continue;
			if (map[v][j] == INF) continue;
			
			if (dist[j] > dist[v] + map[v][j])
			{
				dist[j] = dist[v] + map[v][j];
				if( pre[j] != -1)
					puts("unhighlight");
				pre[j] = v;
			}
			printf("unhighlight");
		}
		puts("unhighlight");
	}
}

int main(void)
{
	int test_case;
	int T;
	int i;
	int j;
	int from;
	int to;
	int value;
    freopen("input_Dijkstra.txt", "r", stdin);
    
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; test_case++)
	{
		scanf("%d %d %d", &vertex, &start, &end);
		for (int i = 1; i <= vertex; i++) {
			printf("setData");
		}
		scanf("%d", &edge);

		for (i = 1; i <= vertex; i++)
		{
			for (j = 1; j <= vertex; j++)
			{
				if (i != j)
				{
					map[i][j] = INF;
				}
			}
		}

		for (i = 1; i <= edge; i++) 
		{
			scanf("%d %d %d", &from, &to, &value);
			map[from][to] = value;
		}

		for (i = 1; i <= vertex; i++)
		{
			dist[i] = INF;
			visit[i] = 0;
			pre[j] = -1;
		}

		printf("#%d ", test_case);
		dijkstra();
		printf("%d \n", dist[end]);
	}
	return 0;
}