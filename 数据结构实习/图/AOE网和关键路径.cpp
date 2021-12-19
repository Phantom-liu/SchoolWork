#include<bits/stdc++.h>
using namespace std;
int A[51][51], W[51][51]; //邻接点 邻接矩阵
int cd[51], rd[51]; //出度和入度
int start, ed;
int topo[51], cnt=0;
int ve[51], vl[51];  //事件（点）最早最晚时间
int ae[51], al[51];  //活动（边）最早最晚时间
int B[51][51];   //关键路径顶点的邻接点
int path[51], cd2[51];  //关键路径顶点 出度
int N, M;
void print(int,int);
/*
1 2 4
1 3 6
2 4 1
3 4 1
4 5 9
4 6 6
4 7 7
5 8 3
6 8 7
7 8 4
*/
void ini() {
	N = 8, M = 10;
	int E[15][3] = { {1,2,4},{1,3,6},{2,4,3},{3,4,1},{4,5,9},{4,6,6},{4,7,7},{5,8,3},{6,8,7},{7,8,4} };
	for (int i = 1; i <= M; i++) {
		int j = E[i - 1][0], k = E[i - 1][1], l = E[i - 1][2];
		cd[j]++;
		A[j][cd[j]] = k;
		rd[k]++;
		W[j][k] = l;
	}
	for (int i = 1; i <= N; i++) {
		if (rd[i] == 0)start = i;
		if (cd[i] == 0)ed = i;
	}
}
bool toposort()
{
	int num = 0;
	int q[51], head = 0, tail = 1;
	q[++head] = start;
	while (head <= tail) {
		int i = q[head++];
		num++;
		topo[cnt++] = i;
		for (int j = 1; j <= cd[i]; j++) {
			int k = A[i][j];
			rd[k]--;
			if (rd[k] == 0) q[++tail] = k;
			ve[k] = max(ve[k], ve[i] + W[i][k]);
		}
	}
	if (num == N)return true;
	else return false;
}
void critlpath()
{
	//求事件的ve vl
	if (toposort()) {
		for (int i = 1; i <= N; i++) vl[i] = ve[N];
		for (int l = N; l > 0; l--) {
			int k = topo[l];
			for (int j = cd[k]; j > 0; j--) {
				int i = A[k][j];
				vl[k] = min(vl[k], vl[i] - W[k][i]);
			}
		}
	}
	//下面求活动的ae al  j代表边的序号
	int j = 0;
	for (int i = 1; i <= N; i++) {
		for (int l = 1; l <= cd[i]; l++) {
			int k = A[i][l];
			ae[++j] = ve[i]; al[j] = vl[k] - W[i][k];
			if (ae[j] == al[j]) {
				B[i][++cd2[i]] = k;  //存储邻接点
			}
		}
	}
	// 跟踪结果
	printf("事件ve：");
	for (int i = 1; i <= N; i++)printf("%2d ", ve[i]);
	printf("\n事件vl：");
	for (int i = 1; i <= N; i++)printf("%2d ", vl[i]);
	printf("\n活动ae：");
	for (int i = 1; i <= M; i++)printf("%2d ", ae[i]);
	printf("\n活动al：");
	for (int i = 1; i <= M; i++)printf("%2d ", al[i]);
	printf("\n\n关键路径：\n");
	print(start, 1);
}
void print(int v, int deep) {
	path[deep] = v;
	if (v == ed) {
		for (int j = 1; j <= deep; j++) printf("%d ", path[j]);
		printf("\n");
	}
	else {
		for (int j = 1; j <= cd2[v]; j++)print(B[v][j], deep + 1);
	}
}
int main()
{
	ini();
	critlpath();
	return 0;
}