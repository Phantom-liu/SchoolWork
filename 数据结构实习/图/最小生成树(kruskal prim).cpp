#include<bits/stdc++.h>
using namespace std;
struct Edge {
	int from, to, w;
	Edge* nxt;
	bool operator<(Edge e) {
		return w < e.w;
	}
};
Edge e[10005];
int father[10005];
int find(int x) {
	return father[x] == x ? x : find(father[x]);
}
void union1(int x, int y) {
	x = find(x);
	y = find(y);
	father[y] = x;
}
int kruskal(Edge* e,int m)
{
	sort(e, e + m);
	int ret = 0;
	for (int i = 0; i < m; i++)
	{
		if (find(e[i].from) == find(e[i].to))continue;
		ret += e[i].w;
		union1(e[i].from, e[i].to);
	}
	return ret;
}

//prim算法      
/* int edges[105][105];
int dis[105];
int vis[105];
void add_edge(int from, int to, int w) {
	edges[from][to] = min(edges[from][to], w);
	edges[to][from] = min(edges[to][from], w);
}
void ini() {
	memset(edges, 0x3f, sizeof edges);
	memset(dis, 0x3f, sizeof dis);
	memset(vis, 0, sizeof vis);
}
int prim(int n)
{
	vis[1] = 1;
	for (int i = 2; i <= n; i++) {
		dis[i] = edges[1][i];
	}
	int ret = 0;
	for (int i = 2; i <= n; i++)
	{
		int x = 1;
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && dis[j] < dis[x]) x = j;
		}
		ret += dis[x];
		vis[x] = 1;
		for (int j = 1; j <= n; j++) {
			if (!vis[j]) dis[j] = min(dis[j], edges[x][j]);
		}
		//若用邻接点(类似vector) 非稠密图时优化作用明显
		for(int j=1;j<=num[x];j++)
		{
			if (!vis[j]) dis[j] = min(dis[j], edges[x][j]);
		}
	}
	return ret;
} */