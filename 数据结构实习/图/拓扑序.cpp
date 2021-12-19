#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5;
vector<int> g[maxn];
int deg[maxn], vis[maxn];
queue<int> q;
int cnt;
bool toposort()
{
	int num = 0;
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		num++;
		for (auto z : g[now]) {
			if (vis[z])continue;
			deg[z]--;
			if (!deg[z]) {
				vis[z] = 1;
				q.push(z);
			}
		}
	}
	if (num == cnt)return true; 
	else return false;
}
int main()
{
	freopen("zz.txt", "r", stdin);
	cin >> cnt;
	int a, b;
	while (!q.empty())q.pop();
	memset(deg, 0, sizeof(deg));
	memset(vis, 0, sizeof(vis));
	while (scanf("%d %d",&a,&b) == 2) {
		g[a].push_back(b);
		deg[b]++;
	}
	cout << cnt;
	for (int i = 1; i <= cnt; i++) {
		if (deg[i] == 0) {
			vis[i] = 1;
			q.push(i);
		}
	}
	if (toposort())puts("correct!");
	else puts("wrong!");
	return 0;
}